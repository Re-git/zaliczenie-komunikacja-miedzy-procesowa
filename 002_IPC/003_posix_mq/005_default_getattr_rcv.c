#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS, malloc
#include <mqueue.h> // mq_*
#include <fcntl.h>  // O*

int main(int argc, char *argv[])
{  
	void *buf;
    struct mq_attr attr;
	
	mqd_t mqfd = mq_open("/my_msq", O_CREAT | O_EXCL | O_RDONLY, 0666, NULL);
	mq_getattr(mqfd, &attr);
	
	printf("mqfd = %d | attr.mq_msgsize = %ld\n", mqfd, attr.mq_msgsize);
	buf = malloc(attr.mq_msgsize);
	
	for(int i = 0 ; i < 10 ; i++) 
	{
		//The msg_len argument specifies the size of the buffer pointed to by
		//msg_ptr; this must be greater than or equal to the mq_msgsize attribute of the queue
		mq_receive(mqfd, buf, attr.mq_msgsize, NULL);
		printf("Received : %s\n", (char*)buf);
	}

	mq_close(mqfd);
	mq_unlink("/my_msq");
	exit(EXIT_SUCCESS);
}
