#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/shm.h>  
#include "shmdata.h"  
  
int main(void)  
{  
    int running = 1;  
    void *shm = NULL;  
    struct shared_use_st *shared = NULL;  
    char buffer[BUFSIZ + 1];//���ڱ���������ı�  
    int shmid;  
    //���������ڴ�  
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);  
    if(shmid == -1)  
    {  
        fprintf(stderr, "shmget failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //�������ڴ����ӵ���ǰ���̵ĵ�ַ�ռ�  
    shm = shmat(shmid, (void*)0, 0);  
    if(shm == (void*)-1)  
    {  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }  
    printf("Memory attached at %p\n", shm);  
    //���ù����ڴ�  
    shared = (struct shared_use_st*)shm;  
    while(running)//�����ڴ���д����  
    {  
        //���ݻ�û�б���ȡ����ȴ����ݱ���ȡ,���������ڴ���д���ı�  
        while(shared->written == 1)  
        {  
            sleep(1);  
            printf("Waiting...\n");  
        }  
        //�����ڴ���д������  
        printf("Enter some text: ");  
        fgets(buffer, BUFSIZ, stdin);  
        strncpy(shared->text, buffer, TEXT_SZ);  
        //д�����ݣ�����writtenʹ�����ڴ�οɶ�  
        shared->written = 1;  
        //������end���˳�ѭ��������  
        if(strncmp(buffer, "end", 3) == 0)  
            running = 0;  
    }  
    //�ѹ����ڴ�ӵ�ǰ�����з���  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    sleep(2);  
    exit(EXIT_SUCCESS);  
}
