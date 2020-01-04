#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <unistd.h> // getpid(), getppid()
 
int main(int argc, char* argv[])
{
	printf("moj_prog = %d, uruchamiamy inny program\n", getpid());
	system("./hello");
	printf("moj_prog = %d, konczymy prace\n", getpid());

	exit(EXIT_SUCCESS);
}
