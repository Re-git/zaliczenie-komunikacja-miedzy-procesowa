#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <sys/stat.h> // mkfifo

int main()
{ 
	// one descriptor : read / write
	int res = mkfifo("/tmp/example_fifo", 0777); 
	
	if (res == 0) 
		printf("FIFO created\n"); 

	exit(EXIT_SUCCESS); 
}

//one terminal
//cat < /tmp/example_fifo

//second terminal
//echo "hello" > tmp/example_fifo