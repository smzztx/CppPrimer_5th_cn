#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    int msgid;

    //get a System V message queue identifier
    msgid = msgget((key_t)1234,0666|IPC_CREAT);
    perror("perror");
    write(STDERR_FILENO, "write error message", 1);
    fprintf(stderr,"fprintf stderr");
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
}

