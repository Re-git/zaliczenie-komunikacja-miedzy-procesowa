#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

void* thread_fun(void *arg)
{
	printf("thread arg 1 = %d\n", *(int*)(arg));
	*(int*)(arg) = 10;
	printf("thread arg 1 = %d\n", *(int*)(arg));
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_id;
	int temp = 5;

	pthread_create(&thread_id, NULL, thread_fun, &temp);
	pthread_join(thread_id, NULL);

	printf("main thread temp = %d\n", temp);	
	exit(EXIT_SUCCESS);
}
