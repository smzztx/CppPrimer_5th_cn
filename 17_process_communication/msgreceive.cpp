#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

struct msg_st
{  
    long int msg_type;  
    char text[BUFSIZ];  
};

int main(void)
{
    int running = 1,msgid;
    struct msg_st data;
    long int msgtype = 0;

    msgid = msgget((key_t)1234,0666|IPC_CREAT);
    if(msgid == -1)
    {
        fprintf(stderr,"msgget failed with error: %d\n",errno);
        return 1;
    }
    while(running)
    {
        if(msgrcv(msgid,(void*)&data,BUFSIZ,msgtype,0) == -1)
        {
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);
            return 1;
        }
        printf("you wrote: %s\n",data.text);
        if(strncmp(data.text,"end",3) == 0)
        {
            running =0;
        }
    }
    if(msgctl(msgid,IPC_RMID,0) == -1)
    {
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        return 1;
    }
    return 0;
}