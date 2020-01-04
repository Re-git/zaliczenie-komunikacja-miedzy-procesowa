#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <sys/mman.h> // PROT_*, MAP_SHARED 
#include <fcntl.h>    // O_* constants
#include <unistd.h>   // ftruncate, close
#include <string.h>   // strcpy

typedef struct person_t {
    char name[20];
    char surname[20];
    int age;
} person_t;

int main(int argc, char *argv[])
{
	person_t * shm_ptr = NULL;
	int        shm_fd  = shm_open("/my_shm", O_CREAT | O_EXCL | O_RDWR, 0600);
	
	// size is zero, resize
	ftruncate(shm_fd, sizeof(person_t));
	
	// map a POSIX shared memory object to the calling process's virtual address space 
	shm_ptr = mmap(NULL, 	              // kernel chooses the address at which to create the mapping
				  sizeof(person_t),       // length of the mapping
				  PROT_READ | PROT_WRITE, // memory protection of the mapping
				  MAP_SHARED,             // update to the mapping is visible to other processes
				  shm_fd, 				  // SHM descriptor from shm_open() 
				  0);
				  
	strcpy(shm_ptr->name, "Jan");
	strcpy(shm_ptr->surname, "Nowak");
	shm_ptr->age = 45;

	printf("%s | %s | %d\n", shm_ptr->name, shm_ptr->surname, shm_ptr->age);
	
	close(shm_fd);
	shm_unlink("/my_shm");
	exit(EXIT_SUCCESS);
}