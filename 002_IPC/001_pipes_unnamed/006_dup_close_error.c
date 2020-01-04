#include <stdio.h> 
#include <stdlib.h>    // EXIT_SUCCESS
#include <string.h>    // strlen
#include <sys/types.h> // O_*
#include <fcntl.h>     // open
#include <unistd.h>    // STD*_FILENO

int main(int argc, char* argv[]) 
{ 
	printf("STDIN_FILENO = %d\n",  STDIN_FILENO);
	printf("STDOUT_FILENO = %d\n", STDOUT_FILENO);
	printf("STDERR_FILENO = %d\n", STDERR_FILENO);
	
	//create and open file
	int f_stdout = open("./f_stdout", O_CREAT | O_RDWR, S_IRUSR);
	//create and open file
	int f_stderr = open("./f_stderr", O_CREAT | O_RDWR, S_IRUSR);
	//write(f_stdout, "hello", strlen("hello"));
	//write(f_stderr, "hello", strlen("hello"));
	
	//duplicate a file descriptor
	//uses the lowest-numbered unused descriptor for the new descriptor
	//the old and new file descriptors may be used interchangeably
	
	close(STDIN_FILENO);  // 0 - in
	close(STDOUT_FILENO); // 1 - out
	close(STDERR_FILENO); // 2 - err

	dup(f_stdout); // new 0 - in
	dup(f_stderr); // new 1 - out
	
	//0 -> in  - f_stdout
	//1 -> out - f_stderr
	//2 -> err(closed)
	//x -> f_stdout
	//y -> f_stderr
	
	printf("Normal message 1\n"); //2 - f_stderr
	fprintf(stdout, "Normal message 2\n"); //2 - f_stderr
	fprintf(stderr, "Error message 1\n"); //closed
	
	//close(f_stdout);
	//close(f_stderr);
	
	exit(EXIT_SUCCESS);
}