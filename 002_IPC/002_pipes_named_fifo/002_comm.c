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
	char  readbuf[255];
	
	if(argc < 2) {
		printf("incorrect usage\n");
		exit(EXIT_FAILURE);
	}
	
	if(0 == strcmp(argv[1], "1")) {
		printf("READ\n");
		
		mkfifo("/tmp/example_fifo", 0666);
		
		printf("before open\n");
		fd = open("/tmp/example_fifo", O_RDONLY);
		printf("after open\n");
		
		read(fd, readbuf, sizeof(readbuf));
		printf("read -  %s", readbuf);
		
		close(fd);
		unlink("/tmp/example_fifo"); // delete fifo
		exit(EXIT_SUCCESS);
		
	} else if(0 == strcmp(argv[1], "2")) {
		printf("WRITE\n");
		
	    fd = open("/tmp/example_fifo", O_WRONLY);
		write(fd, "Hello world", strlen("Hello world"));
		close(fd);
		exit(EXIT_SUCCESS);
		
	} else {
		exit(EXIT_FAILURE);
	}
}
