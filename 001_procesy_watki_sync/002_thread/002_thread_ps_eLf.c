#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

#define THREADS_NUM 10
int temp;

void* thread_fun(void *arg)
{
	int local = temp++;
	printf("New thread id = %d | ends within %d\n", local, 10 + local*2);
	sleep(10 + local*2);
	printf("New thread id end = %d\n", local);

	pthread_exit(NULL);
}

// nowa konsola : ps -eLf | grep a.out
int main(int argc, char* argv[]) 
{
	pthread_t thread_id[THREADS_NUM];
	
	for(int i = 0 ; i < THREADS_NUM ; i++)
		pthread_create(&thread_id[i], NULL, &thread_fun, NULL);

	for(int i = 0 ; i < THREADS_NUM ; i++)
		pthread_join(thread_id[i], NULL);
	
	printf("Main thread end\n");	
	exit(EXIT_SUCCESS);
}
