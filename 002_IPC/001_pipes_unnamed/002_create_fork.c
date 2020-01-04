#include <stdio.h> 
#include <stdlib.h> // EXIT_SUCCESS
#include <string.h> // strlen
#include <unistd.h> // pipe, read, write

int main(int argc, char* argv[]) 
{ 
	int data_processed;
	int pid;
	int pipes_id[2]; 
		//pipes_id[0] - read
		//pipes_id[1] - write
	char buffer[32];
	
	if (pipe(pipes_id) == 0) {
		
		pid = fork();
		if(pid == -1) {		
		} else if (pid == 0) 
		{ //child
			close(pipes_id[0]); // close read
			data_processed = write(pipes_id[1], "hello", strlen("hello"));
			printf("child wrote %d bytes\n", data_processed);
			close(pipes_id[1]);			
		} else 
		{ //parent
			close(pipes_id[1]);	// close write	
			data_processed = read(pipes_id[0], buffer, BUFSIZ);
			printf("parent read %d bytes: %s\n", data_processed, buffer);
			close(pipes_id[0]);
		}
	}
	
	exit(EXIT_SUCCESS);
}