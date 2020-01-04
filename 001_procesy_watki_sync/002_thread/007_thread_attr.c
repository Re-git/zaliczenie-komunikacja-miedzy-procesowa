#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

void* thread_fun(void *arg)
{
	printf("thread fun\n");
	sleep(5);
	printf("thread fun - end\n");	
	//When a detached thread terminates, its resources are
    //automatically released back to the system without the need for
    //another thread to join with the terminated thread.
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_id;
	pthread_attr_t thread_attr;

	// inicjalizacje pthread_attr_t domyslymi wartosciami
	pthread_attr_init(&thread_attr);

	// ustawienie watku w tryb "detached"
	pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
	
	// stworzenie watku
	pthread_create(&thread_id, &thread_attr, &thread_fun, NULL);
	
	// proba czekana na watek
	pthread_join(thread_id, NULL);
	printf("Main thread - nie blokujemy\n");
	sleep(10);
	printf("Main thread - konczymy\n");
	
	// usuniecie pthread_attr_t
	pthread_attr_destroy(&thread_attr);

	exit(EXIT_SUCCESS);
}
