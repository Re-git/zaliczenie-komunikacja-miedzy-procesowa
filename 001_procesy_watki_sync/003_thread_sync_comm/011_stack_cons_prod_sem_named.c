#include <stdio.h>
#include <unistd.h>
#include <pthread.h>   // pthread
#include <semaphore.h> // semaphore
#include <fcntl.h>     // O_* constants

#define ELEMS_NUM 10

int buff[ELEMS_NUM];
int buff_index;

pthread_mutex_t buff_mutex;

// nienazwane semafory
sem_t * sem_full  = NULL;
sem_t * sem_empty = NULL;

int push_front(int val)
{
	if(buff_index < ELEMS_NUM) {
		buff[buff_index++] = val;
		return 0;
	} else 
		return -1;
}

int pop_front()
{
	if(buff_index > 0)
		return buff[--buff_index];
	else
		return -1;
}

void* producer(void* arg)
{
	int result;
	int val = 0;
		
	while(1) {
		sem_wait(sem_empty);
			// potrzeba mutexu, poniewaz mamy N-wspoldzielonych zasobow
			pthread_mutex_lock(&buff_mutex); 
				result = push_front(val);
				printf("producer : %d | result = %d\n", val++, result);
			pthread_mutex_unlock(&buff_mutex);
		sem_post(sem_full);
	}
}

void* consumer(void* arg)
{
	int temp;
	
	while(1) {
		sem_wait(sem_full);
			// potrzeba mutexu, poniewaz mamy N-wspoldzielonych zasobow
			pthread_mutex_lock(&buff_mutex); 		
				temp = pop_front();
				printf("consumer : %d\n", temp);
			pthread_mutex_unlock(&buff_mutex);
		sem_post(sem_empty);
	}
}

// sprawdzic czy juz nie ma stworzonych semaforow w /dev/shm/
int main(int argc, char* argv[])
{
	pthread_t thread_write, thread_read;
	pthread_mutex_init(&buff_mutex, NULL);
	
	// inicjalizacja semafora
	sem_full  = sem_open("/my_sem_full",  O_CREAT | O_EXCL | O_RDWR, 0600, 0); 
	sem_empty = sem_open("/my_sem_empty", O_CREAT | O_EXCL | O_RDWR, 0600, ELEMS_NUM);

	pthread_create(&thread_write, NULL, producer, NULL);
	pthread_create(&thread_read,  NULL, consumer, NULL);

	pthread_join(thread_write, NULL);
	pthread_join(thread_read,  NULL);
	
	// zamkniecie semaforow
	sem_close(sem_full);
	sem_close(sem_empty);
	
	// usuniecie semaforow
	sem_unlink("/my_sem_full");
	sem_unlink("/my_sem_empty");
	
	pthread_mutex_destroy(&buff_mutex);

	return 0;
}
