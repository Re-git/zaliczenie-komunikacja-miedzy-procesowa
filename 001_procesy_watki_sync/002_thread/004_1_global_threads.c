#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

int my_global = 10;

void* thread_fun(void *arg)
{
	my_global++;
	printf("thread_fun my_global = %d\n", my_global);
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_id;
	
	if(0 == pthread_create(&thread_id, NULL, &thread_fun, NULL)) 
	{
		printf("Main threads waits...\n");
		if(0 == pthread_join(thread_id, NULL)) {
			printf("Main threads my_global = %d\n", my_global);
		} else {
			printf("pthread_join error\n"); 
		}
	}
	else 
	{
		printf("thread_create error\n");
	}	
	
	exit(EXIT_SUCCESS);
}
