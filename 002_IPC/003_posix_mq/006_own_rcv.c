#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <mqueue.h> // mq_*
#include <fcntl.h>  // O*

int main(int argc, char *argv[])
{  
	char buf[64]; 
	struct mq_attr attr =  {
		.mq_flags   = O_NONBLOCK,
		.mq_maxmsg  = 5,
		.mq_msgsize = 64,
		.mq_curmsgs = 0
	};
	mqd_t mqfd = mq_open("/my_msq", O_CREAT | O_EXCL | O_RDONLY, 0666, &attr);
	printf("mqfd = %d\n", mqfd);
	
	for(int i = 0 ; i < 10 ; i++) 
	{
		//The msg_len argument specifies the size of the buffer pointed to by
		//msg_ptr; this must be greater than or equal to the mq_msgsize attribute of the queue
		mq_receive(mqfd, buf, 64, NULL);
		printf("Received : %s\n", buf);
	}

	mq_close(mqfd);
	mq_unlink("/my_msq");
	exit(EXIT_SUCCESS);
}
