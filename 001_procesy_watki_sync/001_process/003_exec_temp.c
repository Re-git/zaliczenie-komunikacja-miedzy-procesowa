#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <unistd.h> // getpid(), getppid()
 
int main(int argc, char* argv[])
{
	printf("hello from temp, pid = %d\n", getpid());

	exit(EXIT_SUCCESS);
}
