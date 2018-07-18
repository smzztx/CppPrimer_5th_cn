#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <unistd.h>

void handler(int sig)
{
    printf("Handler the signal %d\n",sig);
}


int main(void)
{
    sigset_t sigset,ign;
    struct sigaction act;

    sigemptyset(&sigset);
    sigemptyset(&ign);

    sigaddset(&sigset,SIGINT);//add signal Ctrl+C

    //set handler
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT,&act,0);

    printf("wait the signal SIGINT...\n");
    pause();//wait for signal

    sigprocmask(SIG_SETMASK,&sigset,0);
    printf("Please press Ctrl+c in 10 seconds...\n");
    sleep(10);

    sigpending(&ign);

    if(sigismember(&ign, SIGINT))
    {
        printf("The SIGINT signal has ignored\n");
    }

    sigdelset(&sigset,SIGINT);
    printf("wait the signal SIGINT...\n");

    sigsuspend(&sigset);

    printf("the app will exit in 5 seconds\n");
    sleep(5);
    return 0;
        
}

