#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

#define THREADS_NUM 10

void* thread_fun(void *arg)
{
	printf("thread begin arg = %d\n", *(int*)(arg));
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_id[THREADS_NUM];
	int i;

	for(i = 0 ; i < THREADS_NUM ; i++)
		pthread_create(&thread_id[i], NULL, &thread_fun, &i);

	for(i = 0 ; i < THREADS_NUM ; i++)
		pthread_join(thread_id[i], NULL);
	
	printf("Main thread end\n");	
	exit(EXIT_SUCCESS);
}
