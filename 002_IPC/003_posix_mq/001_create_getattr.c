#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <mqueue.h> // mq_*

int main(int argc, char *argv[])
{
	mqd_t mqd;
	struct mq_attr attr;
	
	mqd = mq_open("/my_msq", O_RDWR | O_CREAT);
	printf("mqd = %d\n", mqd);
	mq_getattr(mqd, &attr);
	
	printf("Flags of queue:              %ld\n", attr.mq_flags); //0 or 0_NONBLOCK
	printf("Maximum messages on queue:   %ld\n", attr.mq_maxmsg);
	printf("Maximum message size:        %ld\n", attr.mq_msgsize);
	printf("Messages currently on queue: %ld\n", attr.mq_curmsgs);
	
	mq_close(mqd);
	mq_unlink("/my_msq");	
	exit(EXIT_SUCCESS);
}