#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <unistd.h> // getpid(), getppid()

int main(int argc, char* argv[])
{
	printf("pid = %d\n", getpid());
	printf("ppid = %d\n", getppid());

	exit(EXIT_SUCCESS);
}
