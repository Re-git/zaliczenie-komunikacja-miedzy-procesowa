#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <unistd.h>   // getpid(), getppid()
#include <sys/wait.h> // wait(), waitpid()

int main(int argc, char* argv[])
{
	int status, ret;  
	
	for(int i = 0 ; i < 10 ; i++)
	{
		int pid = fork();

		if(pid == 0)
		{
			printf("child %d\n", getpid());
			sleep(10+i);
			printf("child %d - konczymy prace\n", getpid());
			exit(EXIT_SUCCESS);
		}
	}

	sleep(1);	
	for(int i = 0 ; i < 10 ; i++)
	{
		printf("parent - czekamy na zakonczenie child\n");
		ret = wait(&status);			
		printf("parent - po wait ret = %d | status = %d\n", ret, status);
	}

	printf("parent - w koncu koniec\n");
	exit(EXIT_SUCCESS);
}
