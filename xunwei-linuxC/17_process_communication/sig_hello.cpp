#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

sighandler_t handler()
{
    printf("hello linux\n");
}

int main(void)
{
    int i;

    signal(SIGALRM,(sighandler_t)handler);
    
    alarm(5);

    for(i=1;i<7;i++)
    {
        printf("sleep %d ......\n",i);
        sleep(1);
    }
    return 0;
}