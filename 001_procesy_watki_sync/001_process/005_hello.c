#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <unistd.h> // getpid(), getppid()
 
int main(int argc, char* argv[])
{
	printf("hello z innego programu pid = %d\n", getpid());

	exit(EXIT_SUCCESS);
}
