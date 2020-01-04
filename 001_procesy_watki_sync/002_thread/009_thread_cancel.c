#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

void* thread_fun(void *arg)
{
	// PTHREAD_CANCEL_ENABLE  - The thread is cancelable
	// PTHREAD_CANCEL_DISABLE - The thread is not cancelable	 
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,      NULL);
	
	// PTHREAD_CANCEL_DEFERRED     - A cancellation request is deferred until the thread next calls 
	// 		a function that is a cancellation point
	// PTHREAD_CANCEL_ASYNCHRONOUS - The thread can be canceled at any time.
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	
	printf("thread_fun before sleep\n");
	sleep(10);
	printf("thread_fun before sleep\n");
	
	pthread_exit(NULL);
}

//ps -eLf | grep a.out
int main(int argc, char* argv[])
{
	pthread_t thread_id;
	void * res;

	pthread_create(&thread_id, NULL, thread_fun, NULL);
	
	sleep(5);
	printf("Glowny thread - Wysylanie pthread_cancel\n");
	
	// wyslanie "cancelation request" 
	pthread_cancel(thread_id);
	
	// czekanie, az watek sie zakonczy
	pthread_join(thread_id, &res);
	
	if (res == PTHREAD_CANCELED)
		printf("Glowny thread - PTHREAD_CANCELED odebrany\n");

	exit(EXIT_SUCCESS);
}
