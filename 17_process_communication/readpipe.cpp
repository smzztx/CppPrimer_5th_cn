#include <limits.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void)
{
    const char *fifo_name = "my_fifo";
    char buffer[PIPE_BUF + 1];
    int pipe_fd,data_fd,res=0,bytes_write=0,bytes_read=0;

    //clear buffer,fill memory with a constant byte
    memset(buffer,'\0',sizeof(buffer));
    printf("Process %d opening FIFO O_RDONLY\n", getpid());
    pipe_fd = open(fifo_name,O_RDONLY);
    data_fd = open("DataFormFIFO.txt",O_WRONLY|O_CREAT,0644);
    printf("Process %d result %d\n",getpid(), pipe_fd);

    if(pipe_fd == -1)
    {
        perror("pipe_fd open error");
        return 1;
    }

    do
    {
        res = read(pipe_fd,buffer,PIPE_BUF);
        bytes_write = write(data_fd,buffer,res);
        bytes_read += res;
    }while(res > 0);
    close(pipe_fd);
    close(data_fd);
    printf("Process %d finished, %d bytes read\n", getpid(), bytes_read);

    return 0;
}