#include <stdio.h>
#include <string.h>    // strlen
#include <stdlib.h>    // EXIT_SUCCESS
#include <unistd.h>    // read,write
#include <sys/types.h> // open
#include <sys/stat.h>  // mkfifo
#include <sys/wait.h>  // waitpid
#include <fcntl.h>     // open flags

int main(int argc, char* argv[])
{ 
	int  fd;
	int  pid;
	int  status;
	char readbuf[255];
	
	pid = fork();
	if(pid == -1) {
		printf("incorrect usage\n");
		exit(EXIT_FAILURE);
	} else if (pid == 0) 
	{ //child
		printf("child WRITE\n");
		
		sleep(5);
	    fd = open("/tmp/example_fifo", O_WRONLY);
		write(fd, "Hello world", strlen("Hello world"));
		close(fd);
		exit(EXIT_SUCCESS);
			
	} else 
	{ //parent
		printf("parent READ\n");
		
		mkfifo("/tmp/example_fifo", 0666);
		
		fd = open("/tmp/example_fifo", O_RDONLY);
		
		read(fd, readbuf, sizeof(readbuf));
		printf("parent read -  %s\n", readbuf);
		
		wait(&status);
		close(fd);
		unlink("/tmp/example_fifo"); // delete fifo
		exit(EXIT_SUCCESS);
	}
}
