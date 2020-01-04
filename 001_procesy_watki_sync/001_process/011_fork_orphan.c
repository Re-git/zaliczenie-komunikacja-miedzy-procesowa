#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <unistd.h>   // getpid(), getppid()
#include <sys/wait.h> // wait(), waitpid()

int main(int argc, char* argv[])
{
	pid_t child_pid = fork();

	if(child_pid == -1)
	{
		printf("error\n");
	}
	else if(child_pid == 0)
	{
		printf("child pid  = %d\n", getpid());
		printf("child ppid = %d\n", getppid());
		sleep(20);
		printf("child pid  = %d\n", getpid());
		printf("child ppid = %d\n", getppid());
		exit(EXIT_SUCCESS);
	}
	else
	{
		printf("parent pid  = %d\n", getpid());
		printf("parent ppid = %d\n", getppid());
		sleep(10);
		printf("parent ends\n");
		exit(EXIT_SUCCESS);
	}
}
