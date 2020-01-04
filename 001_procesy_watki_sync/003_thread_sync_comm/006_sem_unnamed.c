#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>    // EXIT_SUCCESS
#include <pthread.h>   // pthread
#include <semaphore.h> // semaphore
#include <string.h>    // strcpy(), strcpy()

#define BUF_SIZE 100

char buff[BUF_SIZE];

// nienazwane semafory
sem_t sem_full;
sem_t sem_empty;

void* fun_write(void *arg)
{
	int index = 0;

	while(1) {
		for(int i = 0 ; i < 2 ; i++) {
			sem_wait(&sem_empty);
				// nie trzeba mutexu poniewaz jest tylko jeden dzielony zasob
				if(i % 2) {
					memcpy(buff, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", BUF_SIZE);
				} else {
					memcpy(buff, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", BUF_SIZE);
				}
				index++;
				printf("WRITE index = %d\n", index);

			sem_post(&sem_full);
		}
	}
	pthread_exit(NULL);
}

void* fun_read(void* arg)
{
	char buff_local[BUF_SIZE];
	int index = 0;

	while(1) {
		sem_wait(&sem_full);
			// nie trzeba mutexu poniewaz jest tylko jeden dzielony zasob
			memcpy(buff_local, buff, BUF_SIZE);
			index++;
			printf("READ index = %d | %s\n", index, buff_local);

		sem_post(&sem_empty);

	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_write, thread_read;

	// inicjalizacja semafora
	sem_init(
			 &sem_full, // adres semafora
							// sem_t *sem
		      0,        // ma byc uzyty pomiedzy watkami
							// int pshared
			  0			// poczatkowa wartosc
							// unsigned int value
			 );

	// inicjalizacja semafora
	sem_init(&sem_empty, 0, 1);

	pthread_create(&thread_write, NULL, fun_write, NULL);
	pthread_create(&thread_read,  NULL, fun_read,  NULL);

	pthread_join(thread_write, NULL);
	pthread_join(thread_read,  NULL);

	// zniszczenie semafora
	sem_destroy(&sem_full);
	sem_destroy(&sem_empty);

	exit(EXIT_SUCCESS);
}
