#include <stdio.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <mqueue.h>  // mq_*
#include <fcntl.h>   // O*
#include <string.h>  // strlen
#include <unistd.h>  // sleep

int main(int argc, char *argv[])
{  
	char buf[64]; 
	mqd_t mqfd = mq_open("/my_msq", O_WRONLY);
	printf("mqfd = %d\n", mqfd);
	
	for(int i = 0 ; i < 10 ; i++) 
	{
		sprintf(buf, "msg id = %d", i);
		printf("Sending: %s | prio = %d\n", buf, i);
		mq_send(mqfd, buf, strlen(buf) + 1, i);
	}

	mq_close(mqfd);
	mq_unlink("/my_msq");
	exit(EXIT_SUCCESS);
}
