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
	
	//close(STDOUT_FILENO); // 1 - out
	//dup(f_stdout);  // duplicate f_stdout and returns new descriptor 1 (out)
	dup2(f_stdout, STDOUT_FILENO);
	
	//close(STDERR_FILENO); // 2 - err
	//dup(f_stderr); // duplicate f_stderr and returns new descriptor 2 (err)
	dup2(f_stderr, STDERR_FILENO);
	
	//0 -> in
	//1 -> out - f_stdout
	//2 -> err - f_stderr
	//x -> f_stdout
	//y -> f_stderr
	
	printf("Normal message 1\n");
	fprintf(stdout, "Normal message 2\n");
	fprintf(stderr, "Error message 1\n");
	
	close(f_stdout);
	close(f_stderr);
	
	exit(EXIT_SUCCESS);
}