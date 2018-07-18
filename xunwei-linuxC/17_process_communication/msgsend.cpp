#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define MAX_TEXT 512  
struct msg_st  
{  
    long int msg_type;  
    char text[MAX_TEXT];  
};

int main(void)
{
    int msgid,running = 1;
    char buffer[BUFSIZ];
    struct msg_st data;

    //get a System V message queue identifier
    msgid = msgget((key_t)1234,0666|IPC_CREAT);
    perror("perror\n");
    write(STDERR_FILENO, "write error message\n", 1);
    fprintf(stderr,"fprintf stderr\n");
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        return 1;
    }
    while(running)
    {
        printf("enter some text: ");
        fgets(buffer,BUFSIZ,stdin);
        data.msg_type = 1;
        strcpy(data.text,buffer);

        if(msgsnd(msgid,(void*)&data,MAX_TEXT,0) == -1)
        {
            fprintf(stderr,"msgsnd failed\n");
            return 1;
        }

        if(strncmp(buffer,"end",3) == 0)
        {
            running = 0;
        }
        sleep(1);
    }
    return 0;
}


