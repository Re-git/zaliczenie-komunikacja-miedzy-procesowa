#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>    // EXIT_SUCCESS
#include <pthread.h>   // pthread
#include <semaphore.h> // semaphore
#include <fcntl.h>     // O_* constants
#include <string.h>    // strcpy(), strcpy()

#define BUF_SIZE 100

char buff[BUF_SIZE];

// nienazwane semafory
sem_t * sem_full  = NULL;
sem_t * sem_empty = NULL;

void* fun_write(void *arg)
{
	int index = 0;

	while(1) {
		for(int i = 0 ; i < 2 ; i++) {
			sem_wait(sem_empty);
				// nie trzeba mutexu poniewaz jest tylko jeden dzielony zasob
				if(i % 2) {
					memcpy(buff, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", BUF_SIZE);
				} else {
					memcpy(buff, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", BUF_SIZE);
				}
				index++;
				printf("WRITE index = %d\n", index);

			sem_post(sem_full);
		}
	}
	pthread_exit(NULL);
}

void* fun_read(void* arg)
{
	char buff_local[BUF_SIZE];
	int index = 0;

	while(1) {
		sem_wait(sem_full);
			// nie trzeba mutexu poniewaz jest tylko jeden dzielony zasob
			memcpy(buff_local, buff, BUF_SIZE);
			index++;
			printf("READ index = %d | %s\n", index, buff_local);

		sem_post(sem_empty);

	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_write, thread_read;

	// inicjalizacja semafora
	sem_full  = sem_open("/my_sem_full",  O_CREAT | O_EXCL | O_RDWR, 0600, 0);

	// inicjalizacja semafora
	sem_empty = sem_open("/my_sem_empty", O_CREAT | O_EXCL | O_RDWR, 0600, 1);

	pthread_create(&thread_write, NULL, fun_write, NULL);
	pthread_create(&thread_read,  NULL, fun_read, NULL);

	pthread_join(thread_write, NULL);
	pthread_join(thread_read,  NULL);

	// zamkniecie semaforow
	sem_close(sem_full);
	sem_close(sem_empty);

	// usuniecie semaforow
	sem_unlink("/my_sem_full");
	sem_unlink("/my_sem_empty");

	exit(EXIT_SUCCESS);
}
