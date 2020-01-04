#include <stdio.h> 
#include <stdlib.h> // EXIT_SUCCESS
#include <string.h> // strlen
#include <unistd.h> // pipe, read, write

int main(int argc, char* argv[]) 
{ 
	int data_processed;
	int pipes_id[2]; 
		//pipes_id[0] - read
		//pipes_id[1] - write
	char buffer[32];
	
	if (pipe(pipes_id) == 0) {
		data_processed = write(pipes_id[1], "hello", strlen("hello"));
		printf("Wrote %d bytes\n", data_processed);
		
		data_processed = read(pipes_id[0], buffer, BUFSIZ);
		printf("Read %d bytes: %s\n", data_processed, buffer);
	}

	close(pipes_id[0]);
	close(pipes_id[1]);
	exit(EXIT_SUCCESS);
}