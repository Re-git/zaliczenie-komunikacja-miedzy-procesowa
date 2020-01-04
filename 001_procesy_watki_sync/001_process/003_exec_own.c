#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <unistd.h> // getpid(), getppid()
 
int main(int argc, char* argv[])
{
	printf("moj_prog = %d, uruchamiamy inny program\n", getpid());
	
	//to do => correct path
	execl("/home/psydrive/Desktop/parallel_final/temp", "temp",  NULL); //no argumnets

	printf("moj_prog = %d, konczymy prace\n", getpid());

	exit(EXIT_SUCCESS);
}
