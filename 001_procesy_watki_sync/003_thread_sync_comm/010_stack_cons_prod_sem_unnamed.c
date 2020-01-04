#include <stdio.h>
#include <unistd.h>
#include <pthread.h>   // pthread
#include <semaphore.h> // semaphore

#define ELEMS_NUM 10

int buff[ELEMS_NUM];
int buff_index;

pthread_mutex_t buff_mutex;

// nienazwane semafory
sem_t sem_full;
sem_t sem_empty;

int push_front(int val)
{
	if(buff_index < ELEMS_NUM) {
		buff[buff_index++] = val;
		return 0;
	} else {
		return -1;
	}
}

int pop_front()
{
	if(buff_index > 0)
		return buff[--buff_index];
	else {
		return -1;
	}
}

void* producer(void* arg)
{
	int result;
	int val = 0;
		
	while(1) {
		sem_wait(&sem_empty);
			// potrzeba mutexu, poniewaz mamy N-wspoldzielonych zasobow
			pthread_mutex_lock(&buff_mutex); 
				result = push_front(val);
				printf("producer : %d | result = %d\n", val++, result);
			pthread_mutex_unlock(&buff_mutex);
		sem_post(&sem_full);
	}
}

void* consumer(void* arg)
{
	int temp;
	while(1) {
		sem_wait(&sem_full);
			// potrzeba mutexu, poniewaz mamy N-wspoldzielonych zasobow
			pthread_mutex_lock(&buff_mutex);		
				temp = pop_front();
				printf("consumer : %d\n", temp);
			pthread_mutex_unlock(&buff_mutex);
		sem_post(&sem_empty);
	}
}

int main(int argc, char* argv[])
{
	pthread_t thread_write, thread_read;
	pthread_mutex_init(&buff_mutex, NULL);

	// inicjalizacja semafora
	sem_init(&sem_full,  0, 0); 
	sem_init(&sem_empty, 0, ELEMS_NUM);	
	
	pthread_create(&thread_write, NULL, producer, NULL);
	pthread_create(&thread_read, NULL, consumer, NULL);

	pthread_join(thread_write, NULL);
	pthread_join(thread_read, NULL);
	
	// zniszczenie semafora
	sem_destroy(&sem_full);
	sem_destroy(&sem_empty);
	
	pthread_mutex_destroy(&buff_mutex);

	return 0;
}
