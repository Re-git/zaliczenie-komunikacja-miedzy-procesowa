#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <mqueue.h> // mq_*
#include <fcntl.h>  // O*

int main(int argc, char *argv[])
{
	mqd_t mqd;
	struct mq_attr attr =  {
		.mq_flags   = O_NONBLOCK,
		.mq_maxmsg  = 5,
		.mq_msgsize = 64,
		.mq_curmsgs = 0
	};
	struct mq_attr new_attr;
	
	mqd = mq_open("/my_msq", O_RDWR | O_CREAT | O_NONBLOCK, 0666, &attr);
	printf("mqd = %d\n", mqd);
	mq_getattr(mqd, &new_attr);
	
	printf("Flags of queue:              %ld\n", new_attr.mq_flags); 
	printf("Maximum messages on queue:   %ld\n", new_attr.mq_maxmsg);
	printf("Maximum message size:        %ld\n", new_attr.mq_msgsize);
	printf("Messages currently on queue: %ld\n", new_attr.mq_curmsgs);
	
	mq_close(mqd);
	mq_unlink("/my_msq");
	exit(EXIT_SUCCESS);
}