#include <stdio.h>
#include <unistd.h>
#include <pthread.h>  // pthread

#define ELEMS_NUM 10

int buff[ELEMS_NUM];
int buff_index;
pthread_mutex_t buff_mutex;
pthread_cond_t buff_cond_full, buff_cond_empty;

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
		pthread_mutex_lock(&buff_mutex);

			while(buff_index == ELEMS_NUM) // spurious wakeup
				pthread_cond_wait(&buff_cond_empty, &buff_mutex);
			
			result = push_front(val);
			printf("producer : %d | result = %d\n", val++, result);
			
			//poinformuj tylko konsumenta, jezeli pierwsze dane zostaly dodane
			if(buff_index == 1)
				pthread_cond_signal(&buff_cond_full);

		pthread_mutex_unlock(&buff_mutex);
	}
}

void* consumer(void* arg)
{
	int temp;
	
	while(1) {
		pthread_mutex_lock(&buff_mutex);

			while(buff_index == 0) // spurious wakeup
				pthread_cond_wait(&buff_cond_full, &buff_mutex);
			
			temp = pop_front();
			printf("consumer : %d\n", temp);

			//poinforumj konsumenta, ze jest miejsce do dodania 
			if(buff_index == ELEMS_NUM - 1)
				pthread_cond_signal(&buff_cond_empty);
			
		pthread_mutex_unlock(&buff_mutex);
	}
}

int main(int argc, char* argv[])
{
	pthread_t thread_write, thread_read;
	
	// inicjalizacja mutexu 
	pthread_mutex_init(&buff_mutex, NULL);
	
	// inicjalizacja zmiennej warunku
	pthread_cond_init(&buff_cond_empty, NULL);
	pthread_cond_init(&buff_cond_full,  NULL);
	
	pthread_create(&thread_write, NULL, producer, NULL);
	pthread_create(&thread_read, NULL, consumer, NULL);
	
	pthread_join(thread_write, NULL);
	pthread_join(thread_read,  NULL);
	
	// zniszczenie mutexu
	pthread_mutex_destroy(&buff_mutex);
	
	// zniszczenie zmiennej warunku	
	pthread_cond_destroy(&buff_cond_empty);
	pthread_cond_destroy(&buff_cond_full);

	return 0;
}
