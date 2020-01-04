#include <stdio.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <mqueue.h>  // mq_*
#include <fcntl.h>   // O*
#include <string.h>  // strlen
#include <unistd.h>  // sleep

typedef struct person_t {
  char name[20];
  char surname[20];
  int age;
} person_t;

int main(int argc, char *argv[])
{  
	person_t msg_person = { 
		.name    = "Jan", 
		.surname = "Nowak", 
		.age = 0 
	};
	mqd_t mqfd = mq_open("/my_msq", O_WRONLY);
	printf("mqfd = %d\n", mqfd);
	
	sleep(5);
	for(int i = 0 ; i < 10 ; i++) 
	{
		msg_person.age = i;
		printf("Sending : name = %s | surname = %s | age = %d\n", msg_person.name, msg_person.surname, msg_person.age);
		mq_send(mqfd, (char*)&msg_person, sizeof(person_t), 0);
		sleep(2);
	}

	mq_close(mqfd);
	mq_unlink("/my_msq");
	exit(EXIT_SUCCESS);
}
