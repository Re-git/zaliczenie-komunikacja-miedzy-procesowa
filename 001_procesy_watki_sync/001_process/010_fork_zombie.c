#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <unistd.h>   // getpid(), getppid()
#include <sys/wait.h> // wait(), waitpid()

//nowy terminal + ps aux | grep Z

int main(int argc, char* argv[])
{
	int pid = fork();

	if (pid == 0) { 
		//child
		sleep(10);
       	exit(EXIT_SUCCESS);
	}
     
	//parent
   	getchar();
}
