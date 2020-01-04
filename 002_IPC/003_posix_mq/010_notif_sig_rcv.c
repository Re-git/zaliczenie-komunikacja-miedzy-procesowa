#include <stdio.h>
#include <stdlib.h>  // EXIT_SUCCESS
#include <mqueue.h>  // mq_*
#include <fcntl.h>   // O*
#include <unistd.h>  // sleep
#include <pthread.h> // pthread
#include <signal.h>  // sigaction

mqd_t mqfd;

void message_callback(int signum, siginfo_t* info, void* context)
{
	char buf[64];
    if(signum == SIGUSR1) {
        if(info->si_code == SI_MESGQ) {
			while(1) {
				mq_receive(mqfd, buf, 64, NULL);
				printf("Received : %s | %ld\n", buf, pthread_self());	   
			}
        }
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
	struct sigevent  sig_evn;
	struct sigaction sig_act;
	
	mqfd = mq_open("/my_msq", O_CREAT | O_EXCL | O_RDONLY, 0666, &attr);
	printf("mqfd = %d | %ld\n", mqfd, pthread_self());
	
	//setting sigevent
	sig_evn.sigev_notify  = SIGEV_SIGNAL;
    sig_evn.sigev_signo   = SIGUSR1;	
	mq_notify(mqfd, &sig_evn);

	//seting sigaction
	sig_act.sa_flags     = SA_SIGINFO;
    sig_act.sa_sigaction = message_callback;
	sigemptyset(&(sig_act.sa_mask));
    sigaction(SIGUSR1, &sig_act, NULL);
	
	sleep(30); 
	
	mq_close(mqfd);
	mq_unlink("/my_msq");
	exit(EXIT_SUCCESS);
}
