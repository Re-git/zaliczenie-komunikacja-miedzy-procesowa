#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <sys/mman.h> // PROT_*, MAP_SHARED 
#include <fcntl.h>    // O_* constants
#include <unistd.h>   // ftruncate, close

int main(int argc, char *argv[])
{
	int * shm_ptr = NULL;
	int   shm_fd  = shm_open("/my_shm", O_CREAT | O_EXCL | O_RDWR, 0600);
	
	// size is zero, resize
	ftruncate(shm_fd, sizeof(int));
	
	// map a POSIX shared memory object to the calling process's virtual address space 
	shm_ptr = mmap(NULL, 	              // kernel chooses the address at which to create the mapping
				  sizeof(int),            // length of the mapping
				  PROT_READ | PROT_WRITE, // memory protection of the mapping
				  MAP_SHARED,             // update to the mapping is visible to other processes
				  shm_fd, 				  // SHM descriptor from shm_open() 
				  0);

	*shm_ptr = 0xdeadbeef;
	printf("shm_ptr = %p | *shm_ptr = 0x%x\n", shm_ptr, *shm_ptr);
	
	close(shm_fd);
	shm_unlink("/my_shm");
	exit(EXIT_SUCCESS);
}