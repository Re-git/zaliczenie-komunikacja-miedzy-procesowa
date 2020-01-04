#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

void* thread_fun(void *arg)
{
	printf("New thread id = %li\n", pthread_self());
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_id;
	int res;
	
	res = pthread_create(
						  &thread_id,  // pthread_t *thread
									      // id nowego watku
						  NULL, 	   // const pthread_attr_t *attr, 
											// atrybuty watku, NULL - domyslne
						  &thread_fun, // void *(*start_routine) (void *) 
											// funkcja w ktorej watek bedzie dzialal
						  NULL         // void *arg
											// argument przekazany do funkcji w ktorej watek bedzie dzialal
						);

	if(0 == res) {
		printf("Main thread id = %li | new thread = %li\n", pthread_self(), thread_id);
	} else {
		printf("Thread creation error\n");
	}
		
	sleep(5);
	exit(EXIT_SUCCESS);
}
