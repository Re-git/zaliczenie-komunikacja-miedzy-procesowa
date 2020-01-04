#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread
#include <string.h>  // strcpy(), strcpy()

#define BUF_SIZE 100

char buff[BUF_SIZE];
int is_full = 0;
pthread_mutex_t my_mutex;
pthread_cond_t buff_cond_full, buff_cond_empty;

void* fun_write(void *arg)
{
	int index = 0;

	while(1) {
		for(int i = 0 ; i < 2 ; i++) {
			pthread_mutex_lock(&my_mutex);

				// jezeli nie ma miejsca do zapisu czekaj
				while(is_full == 1) // spurious wakeup
					pthread_cond_wait(&buff_cond_empty, &my_mutex);

				if(i % 2) {
					memcpy(buff, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", BUF_SIZE);
				} else {
					memcpy(buff, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", BUF_SIZE);
				}
				index++;
				printf("WRITE index = %d\n", index);

				// oznacz, ze nie ma juz miejsca do zapisu i poinformuj o tym watek odczytujacy
				is_full = 1;
				pthread_cond_signal(&buff_cond_full);

			pthread_mutex_unlock(&my_mutex);
		}
	}
	pthread_exit(NULL);
}

void* fun_read(void* arg)
{
	char buff_local[BUF_SIZE];
	int index = 0;

	 while(1) {
		pthread_mutex_lock(&my_mutex);

			// jezeli nie ma danych czekaj
			while(is_full == 0) // spurious wakeup
				pthread_cond_wait(&buff_cond_full, &my_mutex);

			memcpy(buff_local, buff, BUF_SIZE);
			index++;
			printf("READ index = %d | %s\n", index, buff_local);

			// oznacz, ze nie ma juz danych do odczytu i poinformuj watek zapisujacy
			is_full = 0;
			pthread_cond_signal(&buff_cond_empty);

		pthread_mutex_unlock(&my_mutex);
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_write, thread_read;

	// inicjalizacja mutexu
	pthread_mutex_init(&my_mutex, NULL);

	// inicjalizacja zmiennej warunku
	pthread_cond_init(&buff_cond_empty, NULL);
	pthread_cond_init(&buff_cond_full,  NULL);

	pthread_create(&thread_write, NULL, fun_write, NULL);
	pthread_create(&thread_read,  NULL, fun_read,  NULL);

	pthread_join(thread_write, NULL);
	pthread_join(thread_write, NULL);

	// zniszczenie mutexu
	pthread_mutex_destroy(&my_mutex);

	// zniszczenie zmiennej warunku
	pthread_cond_destroy(&buff_cond_empty);
	pthread_cond_destroy(&buff_cond_full);

	exit(EXIT_SUCCESS);
}
