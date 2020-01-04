#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <pthread.h> // pthread

typedef struct Sum {
	int a;
	int b;
	int result;
} Sum;

void* fun_1(void* arg)
{
	Sum* p = (Sum*)arg;
	p->result = p->a + p->b;
	pthread_exit(NULL);
}

void* fun_2(void* arg)
{
	Sum* p = (Sum*)arg;
	p->result = p->a + p->b;
	return (p);
}

void* fun_3(void* arg)
{
	Sum* p = (Sum*)arg;
	p->result = p->a + p->b;
	pthread_exit(p);
}

int main(int argc, char* argv[])
{
	pthread_t thread1, thread2, thread3;
	Sum first  = {2,3};	
	Sum second = {2,3};
	Sum third  = {2,3};
	Sum* status1;
	Sum* status2;	

	pthread_create(&thread1, NULL, fun_1, &first);	
	pthread_create(&thread2, NULL, fun_2, &second);
	pthread_create(&thread3, NULL, fun_3, &third);

	pthread_join(thread1, NULL);	
	pthread_join(thread2, (void**)&status1); // void **retval
	pthread_join(thread3, (void**)&status2); // void **retval

	printf("thread 1 first  : %d + %d = %d\n", first.a, first.b, first.result);	
	printf("thread 2 second : %d + %d = %d\n", second.a, second.b, status1->result);
	printf("thread 3 third  : %d + %d = %d\n", third.a, third.b, status2->result);		

	exit(EXIT_SUCCESS);
}
