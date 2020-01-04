#include <stdio.h>
#include <string.h>    // strlen
#include <stdlib.h>    // EXIT_SUCCESS
#include <unistd.h>    // read,write
#include <sys/types.h> // open
#include <sys/stat.h>  // mkfifo
#include <fcntl.h>     // open flags

int main(int argc, char* argv[])
{ 
	int   fd; 
	char  msg[10];
	char  readbuf[255];
	
	if(argc < 2) {
		printf("incorrect usage\n");
		exit(EXIT_FAILURE);
	}
	
	if(0 == strcmp(argv[1], "1")) {
		printf("READ\n");
		
		mkfifo("/tmp/example_fifo", 0666);
		fd = open("/tmp/example_fifo", O_RDONLY);
		
		for(int i = 0 ; i < 5 ; i++) {
			read(fd, readbuf, sizeof(readbuf));
			printf("read -  %s", readbuf);
		}
		
		unlink("/tmp/example_fifo"); // delete fifo
		close(fd);
		exit(EXIT_SUCCESS);
		
	} else if(0 == strcmp(argv[1], "2")) {
		printf("WRITE\n");
		
	    fd = open("/tmp/example_fifo", O_WRONLY);
		
		for(int i = 0 ; i < 5 ; i++) {
			sleep(5);
			sprintf(msg, "msg_id %d\n", i);
			printf("write - %s", msg);
			write(fd, msg, strlen(msg)+1);
		}
		
		close(fd);
		exit(EXIT_SUCCESS);
		
	} else {
		exit(EXIT_FAILURE);
	}
}
