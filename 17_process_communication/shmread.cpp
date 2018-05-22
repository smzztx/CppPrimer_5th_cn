#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include "shmdata.h"
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

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
    shm = shmat(shmid,0,0);
    if(shm == (void*)-1)
    {
        fprintf(stderr,"shmat failed\n");
        return -1;
    }
    printf("memory attached at %p\n",shm);
    shared = (struct shared_use_st*)shm;
    shared->written = 0;
    while (running)
    {
        if(shared->written != 0)
        {
            printf("you wrote:%s\n",shared->text);
            sleep(rand()%3);
            shared->written = 0;
            if(strncmp(shared->text,"end",3) == 0)
            {
                running = 0;
            }
        }
        else
        {
            sleep(1);
        }
    }
    if(shmdt(shm) == -1)
    {
        fprintf(stderr,"shmdt failed\n");
        return -1;
    }
    if(shmctl(shmid,IPC_RMID,0) == -1)
    {
        fprintf(stderr,"shmctl(IPC_RMID) failed\n");
        return -1;
    }
    return 0;
    
}