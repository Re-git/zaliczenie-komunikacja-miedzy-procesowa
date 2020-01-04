#include <stdio.h>
#include <stdlib.h>    // EXIT_SUCCESS
#include <sys/mman.h>  // PROT_*, MAP_SHARED 
#include <fcntl.h>     // O_* constants
#include <unistd.h>    // ftruncate, close
#include <sys/wait.h>  // wait
#include <string.h>    // strcpy
#include <semaphore.h> // semaphore

typedef struct person_t {
    char name[20];
    char surname[20];
    int age;
} person_t;

int main(int argc, char *argv[])
{
	person_t * shm_ptr   = NULL;
	int        shm_fd    = shm_open("/my_shm"      , O_CREAT | O_EXCL | O_RDWR, 0600);
	sem_t    * sem_full  = sem_open("/my_sem_full" , O_CREAT | O_EXCL | O_RDWR, 0600, 0); 
	sem_t    * sem_empty = sem_open("/my_sem_empty", O_CREAT | O_EXCL | O_RDWR, 0600, 1); //writer gets first turn !!!
	
	// size is zero, resize
	ftruncate(shm_fd, sizeof(person_t));
	
	// map a POSIX shared memory object to the calling process's virtual address space 
	shm_ptr = mmap(NULL, 	              // kernel chooses the address at which to create the mapping
				  sizeof(person_t),       // length of the mapping
				  PROT_READ | PROT_WRITE, // memory protection of the mapping
				  MAP_SHARED,             // update to the mapping is visible to other processes
				  shm_fd, 				  // SHM descriptor from shm_open() 
				  0);
	
	sleep(10);
	
	for(int i = 0 ; i < 10; i++) {
		printf("writer %d\n", i);		
		sem_wait(sem_empty); 
			if(i % 2) {
				strcpy(shm_ptr->name, "Jan");
				strcpy(shm_ptr->surname, "Nowak");
				shm_ptr->age = 45;
			} else {
				strcpy(shm_ptr->name, "Adam");
				strcpy(shm_ptr->surname, "Kowalski");
				shm_ptr->age = 23;
			}				
		sem_post(sem_full);

		sleep(2);
	}

	sleep(10);
	
	sem_close(sem_empty);
	sem_close(sem_full);
	close(shm_fd);
	sem_unlink("/my_sem_full");
	sem_unlink("/my_sem_empty");
	shm_unlink("/my_shm");
	exit(EXIT_SUCCESS);
}