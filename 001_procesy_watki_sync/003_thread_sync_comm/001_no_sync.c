#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread
#include <string.h>  // strcpy(), strcpy()

#define BUF_SIZE 100
char buff[BUF_SIZE];

void* fun_write(void *arg)
{
	while(1) {
		for(int i = 0 ; i < 2 ; i++) {
			if(i % 2) {
				memcpy(buff, "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", BUF_SIZE);
			} else {
				memcpy(buff, "bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb", BUF_SIZE);
			}
		}
	}
	pthread_exit(NULL);
}

void* fun_read(void* arg)
{
	char buff_local[BUF_SIZE];

  while(1) {
		memcpy(buff_local, buff, BUF_SIZE);
		printf("%s\n", buff_local);
	}
	pthread_exit(NULL);
}

int main(int argc, char* argv[])
{
	pthread_t thread_write, thread_read;

	pthread_create(&thread_write, NULL, fun_write, NULL);
	pthread_create(&thread_read,  NULL, fun_read,  NULL);

	pthread_join(thread_write, NULL);
	pthread_join(thread_read,  NULL);

	exit(EXIT_SUCCESS);
}
