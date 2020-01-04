#include <stdio.h> 
#include <stdlib.h>    // EXIT_SUCCESS
#include <string.h>    // strlen
#include <sys/types.h> // O_*
#include <fcntl.h>     // open
#include <unistd.h>    // STD*_FILENO

int main(int argc, char* argv[]) 
{ 
	printf("STDIN_FILENO  = %d\n", STDIN_FILENO);  // 0
	printf("STDOUT_FILENO = %d\n", STDOUT_FILENO); // 1
	printf("STDERR_FILENO = %d\n", STDERR_FILENO); // 2
	
	//duplicate a file descriptor
	//uses the lowest-numbered unused descriptor for the new descriptor.
	//the old and new file descriptors may be used interchangeably
	int new_out = dup(STDOUT_FILENO); // 3
	printf("new_out = %d\n", new_out);

	write(STDIN_FILENO, "hello1\n", sizeof("hello1\n"));
	write(new_out,      "hello2\n", sizeof("hello2\n"));
	
	exit(EXIT_SUCCESS);	
}