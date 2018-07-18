#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "shmdata.h"
#include <string.h>

int main(void)
{
    int shmid,running = 1;
    void *shm = NULL;
    struct shared_use_st *shared = NULL;
    char buffer[BUFSIZ + 1];

    shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT);
    if(shmid == -1)
    {
        fprintf(stderr,"shmget failed\n");
        return -1;
    }
    shm = shmat(shmid,(void*)0,0);
    if(shm == (void*)-1)
    {
        fprintf(stderr,"shmat failed\n");
        return -1;
    }
    printf("memory attached at %p\n",shm);

    shared = (struct shared_use_st*)shm;

    while(running)
    {
        while(shared->written == 1)
        {
            sleep(1);
            printf("wait...");
        }
        printf("\nenter some text:");
        fgets(buffer,BUFSIZ,stdin);
        strncpy(shared->text,buffer,TEXT_SZ);
        shared->written = 1;
        if(strncpy(buffer,"end",3) == 0)
        {
            running = 0;
        }

    }
    if(shmdt(shm) == -1)
    {
        fprintf(stderr,"shmdt failed\n");
        return -1;
    }
    sleep(2);
    return 0;
}


