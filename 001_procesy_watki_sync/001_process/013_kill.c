#include <stdio.h>
#include <stdlib.h>   // EXIT_SUCCESS
#include <unistd.h>   // getpid(), getppid()
#include <sys/wait.h> // wait(), waitpid()
#include <signal.h>   // kill

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
		sleep(5);
		printf("child after sleep pid  = %d\n", getpid());
	}
	else
	{
		printf("parent pid  = %d\n", getpid());
		
		if(!kill(child_pid, SIGKILL))
			printf("child killed ok\n");	
		else
			printf("child error\n");
		
		sleep(10);
		exit(EXIT_SUCCESS);
	}
}
