#include <stdio.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <mqueue.h>  // mq_*
#include <fcntl.h>   // O*
#include <unistd.h>  // sleep
#include <pthread.h> // pthread

void tfunc(union sigval sv)
{
	char buf[64];
	mqd_t mqdes = *((mqd_t *) sv.sival_ptr);
    while(1) {
		mq_receive(mqdes, buf, 64, NULL);
		printf("Received : %s | %ld\n", buf, pthread_self());
	}
}

int main(int argc, char *argv[])
{  
	char buf[64]; 
	struct mq_attr attr =  {
		.mq_flags   = O_NONBLOCK,
		.mq_maxmsg  = 10,
		.mq_msgsize = 64,
		.mq_curmsgs = 0
	};
	struct sigevent sig_evn;
	
	mqd_t mqfd = mq_open("/my_msq", O_CREAT | O_EXCL | O_RDONLY, 0666, &attr);
	printf("mqfd = %d | %ld\n", mqfd, pthread_self());
	
	sig_evn.sigev_notify 		    = SIGEV_THREAD;
    sig_evn.sigev_notify_function   = tfunc;
    sig_evn.sigev_notify_attributes = NULL;
    sig_evn.sigev_value.sival_ptr   = &mqfd;
	
	mq_notify(mqfd, &sig_evn);
	
	sleep(30); 
	
	mq_close(mqfd);
	mq_unlink("/my_msq");
	exit(EXIT_SUCCESS);
}
