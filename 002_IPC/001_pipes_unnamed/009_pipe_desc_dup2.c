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
		
		printf("STDIN_FILENO  = %d\n", STDIN_FILENO);
		printf("STDOUT_FILENO = %d\n", STDOUT_FILENO);
		printf("STDERR_FILENO = %d\n", STDERR_FILENO);
		printf("pipes_id[0]   = %d\n", pipes_id[0]);
		printf("pipes_id[1]   = %d\n", pipes_id[1]);	
	
		pid = fork();
		if(pid == -1) 
		{	
			exit(EXIT_FAILURE);
		} 
		else if (pid == 0) 
		{ //child
			close(pipes_id[0]); // close read
			
			//data_processed = write(pipes_id[1], "hello", strlen("hello"));
			//printf("child wrote %d bytes\n", data_processed);
			dup2(pipes_id[1], STDOUT_FILENO); //close 1-out, duplicate pipes_id[1] write and new 1-out
			printf("hello_world");

			close(pipes_id[1]);
			exit(EXIT_SUCCESS);			
		} 
		else 
		{ //parent
			close(pipes_id[1]);	// close write
			
			//data_processed = read(pipes_id[0], buffer, BUFSIZ);
			//printf("parent read %d bytes: %s\n", data_processed, buffer);
			dup2(pipes_id[0], STDIN_FILENO); //close 0-in, duplicate pipes_id[0] read and new 0-in
			scanf("%s", buffer);
			printf("parent : %s\n", buffer);	
			
			close(pipes_id[0]);
			exit(EXIT_SUCCESS);
		}
	}
}