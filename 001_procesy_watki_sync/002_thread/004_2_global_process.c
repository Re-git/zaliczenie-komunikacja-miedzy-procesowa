#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <unistd.h>   // getpid(), getppid()
#include <sys/wait.h> // wait(), waitpid()

int my_global = 10;

int main(int argc, char* argv[])
{
	int pid = fork();
	int status, ret;

	if(pid == -1)
	{
		printf("error\n");
	}
	else if(pid == 0)
	{
		my_global++;
		printf("child %d | my_global = %d\n", getpid(), my_global);
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("parent %d | czekamy na zakonczenie child\n", getpid());
		ret = wait(&status);
		printf("parent %d |  po wait ret = %d | status = %d | my_global = %d\n", getpid(), ret, status, my_global);
		exit(EXIT_SUCCESS);
	}
}
