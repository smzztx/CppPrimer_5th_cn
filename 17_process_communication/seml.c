#include <unistd.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/sem.h>  
  
union semun  
{  
    int val;  
    struct semid_ds *buf;  
    unsigned short *arry;  
};  
  
static int sem_id = 0;  
  
static int set_semvalue();  
static void del_semvalue();  
static int semaphore_p();  
static int semaphore_v();  
  
int main(int argc, char *argv[])  
{  
    char message = 'X';  
    int i = 0;  
  
    //�����ź���  
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);  
  
    if(argc > 1)  
    {  
        //�����һ�α����ã���ʼ���ź���  
        if(!set_semvalue())  
        {  
            fprintf(stderr, "Failed to initialize semaphore\n");  
            exit(EXIT_FAILURE);  
        }  
        //����Ҫ�������Ļ�е���Ϣ����������ĵ�һ���ַ�  
        message = argv[1][0];  
        sleep(2);  
    }  
    for(i = 0; i < 10; ++i)  
    {  
        //�����ٽ���  
        if(!semaphore_p())  
            exit(EXIT_FAILURE);  
        //����Ļ���������  
        printf("%c", message);  
        //����������Ȼ���������ʱ��  
        fflush(stdout);  
        sleep(rand() % 3);  
        //�뿪�ٽ���ǰ��һ������Ļ�������  
        printf("%c", message);  
        fflush(stdout);  
        //�뿪�ٽ������������ʱ������ѭ��  
        if(!semaphore_v())  
            exit(EXIT_FAILURE);  
        sleep(rand() % 2);  
    }  
  
    sleep(10);  
    printf("\n%d - finished\n", getpid());  
  
    if(argc > 1)  
    {  
        //��������ǵ�һ�α����ã������˳�ǰɾ���ź���  
        sleep(3);  
        del_semvalue();  
    }  
    exit(EXIT_SUCCESS);  
}  
  
static int set_semvalue()  
{  
    //���ڳ�ʼ���ź�������ʹ���ź���ǰ����������  
    union semun sem_union;  
  
    sem_union.val = 1;  
    if(semctl(sem_id, 0, SETVAL, sem_union) == -1)  
        return 0;  
    return 1;  
}  
  
static void del_semvalue()  
{  
    //ɾ���ź���  
    union semun sem_union;  
  
    if(semctl(sem_id, 0, IPC_RMID, sem_union) == -1)  
        fprintf(stderr, "Failed to delete semaphore\n");  
}  
  
static int semaphore_p()  
{  
    //���ź�������1���������ȴ�P��sv��  
    struct sembuf sem_b;  
   sem_b.sem_num = 0;  
    sem_b.sem_op = -1;//P()  
    sem_b.sem_flg = SEM_UNDO;  
    if(semop(sem_id, &sem_b, 1) == -1)  
    {  
        fprintf(stderr, "semaphore_p failed\n");  
        return 0;  
    }  
    return 1;  
}  
  
static int semaphore_v()  
{  
    //����һ���ͷŲ�������ʹ�ź�����Ϊ���ã��������ź�V��sv��  
    struct sembuf sem_b;  
    sem_b.sem_num = 0;  
    sem_b.sem_op = 1;//V()  
    sem_b.sem_flg = SEM_UNDO;  
    if(semop(sem_id, &sem_b, 1) == -1)  
    {  
        fprintf(stderr, "semaphore_v failed\n");  
        return 0;  
    }  
    return 1;  
}
