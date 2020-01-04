#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <unistd.h>   // getpid(), getppid()
#include <sys/wait.h> // wait(), waitpid()

int main(int argc, char* argv[])
{
	int pid = fork();
	int status;
     
	if(pid == -1)
	{
		printf("error\n");
	}
	else if(pid == 0)
	{
		printf("child %d\n", getpid());
		sleep(10);
		printf("child %d | konczymy prace\n", getpid());
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("parent %d | czekamy na zakonczenie child\n", getpid());
		waitpid(pid, &status, 0);
		printf("parent %d | po wait\n", getpid());
		exit(EXIT_SUCCESS);
	}	
}
