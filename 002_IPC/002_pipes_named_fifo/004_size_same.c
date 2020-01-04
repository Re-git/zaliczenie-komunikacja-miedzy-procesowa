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
	char  buff_write[10];
	char  buff_read[10];
	
	if(argc < 2) {
		printf("incorrect usage\n");
		exit(EXIT_FAILURE);
	}
	
	if(0 == strcmp(argv[1], "1")) {
		printf("READ\n");
		
		mkfifo("/tmp/example_fifo", 0666);
		fd = open("/tmp/example_fifo", O_RDONLY);
		
		for(int i = 0 ; i < 10 ; i++) {
			read(fd, buff_read, sizeof(buff_read));
			printf("read -  %s\n", buff_read);
		}
		
		close(fd);
		unlink("/tmp/example_fifo"); // delete fifo
		exit(EXIT_SUCCESS);
		
	} else if(0 == strcmp(argv[1], "2")) {
		printf("WRITE\n");
		
	    fd = open("/tmp/example_fifo", O_WRONLY);
		
		for(int i = 0 ; i < 10 ; i++) {
			sleep(2);
			sprintf(buff_write, "%s", "123456789");
			printf("write - %s\n", buff_write);
			write(fd, buff_write, sizeof(buff_write));
		}
		
		close(fd);
		exit(EXIT_SUCCESS);
		
	} else {
		exit(EXIT_FAILURE);
	}
}
