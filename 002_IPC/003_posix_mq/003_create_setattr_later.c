#include <stdio.h>
#include <stdlib.h> // EXIT_SUCCESS
#include <mqueue.h> // mq_*
#include <fcntl.h>  // O*

int main(int argc, char *argv[])
{
	mqd_t mqd;
	struct mq_attr cur_attr;
	struct mq_attr new_attr;
	
	mqd = mq_open("/my_msq", O_RDWR | O_CREAT);
	printf("mqd = %d\n", mqd);
	mq_getattr(mqd, &cur_attr);
	
	printf("Current attributes:\n");
	printf("Flags of queue:              %ld\n", cur_attr.mq_flags); 
	printf("Maximum messages on queue:   %ld\n", cur_attr.mq_maxmsg);
	printf("Maximum message size:        %ld\n", cur_attr.mq_msgsize);
	printf("Messages currently on queue: %ld\n", cur_attr.mq_curmsgs);
	
	new_attr.mq_flags   = O_NONBLOCK; // tylko to można zmienić później !!!!
	new_attr.mq_maxmsg  = 5;  // zmiana nie bedzie wzieta pod uwage
	new_attr.mq_msgsize = 64; // zmiana nie bedzie wzieta pod uwage
	new_attr.mq_curmsgs = 0;  // zmiana nie bedzie wzieta pod uwage
	
	mq_setattr(mqd, &new_attr, &cur_attr);
	mq_getattr(mqd, &new_attr);
	printf("Current attributes:\n");
	printf("Flags of queue:              %ld\n", new_attr.mq_flags); 
	printf("Maximum messages on queue:   %ld\n", new_attr.mq_maxmsg);
	printf("Maximum message size:        %ld\n", new_attr.mq_msgsize);
	printf("Messages currently on queue: %ld\n", new_attr.mq_curmsgs);
	
	mq_close(mqd);
	mq_unlink("/my_msq");
	exit(EXIT_SUCCESS);
}