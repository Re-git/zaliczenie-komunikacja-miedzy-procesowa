#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <unistd.h> // getpid(), getppid()

int main(int argc, char* argv[])
{
	pid_t pid = fork();
	if(pid == 0)
	{
		printf("child pid = %d\n",getpid());
		printf("child parent pid = %d\n", getppid());
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0)
	{
		printf("parent pid = %d\n",getpid());
		printf("parent parent pid = %d\n",getppid());
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("error");
	}
}
