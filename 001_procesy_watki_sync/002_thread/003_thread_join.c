#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

void* thread_fun(void *arg)
{
	printf("New thread\n");
	sleep(5);
	printf("New thread ends\n");
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_id;
	
	if(0 == pthread_create(&thread_id, NULL, &thread_fun, NULL)) 
	{
		printf("Main threads waits...\n");
		if(0 == pthread_join(thread_id, NULL)) 
			printf("Main threads ends\n");
		else
			printf("pthread_join error\n"); 
	}
	else 
	{
		printf("thread_create error\n");
	}	
	
	exit(EXIT_SUCCESS);
}
