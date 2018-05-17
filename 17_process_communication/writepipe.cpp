#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

int main(void)
{
    const char *fifo_name = "my_fifo";
    int ret,res,pipe_fd,data_fd,bytes_sent=0;
    char buffer[PIPE_BUF + 1];

    if(ret=access(fifo_name,F_OK) == -1)
    {
        printf("mkfifo\n");
        res = mkfifo(fifo_name,0666);
        if(res == -1)
        {
            perror("mkfifo error\n");
            return 1;
        }
    }else if(ret == 0)
    {
        printf("access ret:0; my_fifo is exit.\n");
    }
    printf("Process %d opening FIFO O_WRONLY\n", getpid());
    pipe_fd = open(fifo_name,O_WRONLY);
    data_fd = open("data.txt",O_RDONLY);
    printf("Process %d result %d\n", getpid(), pipe_fd);
    if(pipe_fd == -1)
    {
        perror("open pipe error\n");
        return 1;
    }
    int bytes_read = 0;
    bytes_read = read(data_fd,buffer,PIPE_BUF);
    buffer[bytes_read] = '\0';
    if(bytes_read == -1)
    {
        perror("read error\n");
        return 1;
    }
    while(bytes_read > 0)
    {
        res = write(pipe_fd,buffer,bytes_read);
        if(res == -1)
        {
            perror("write error\n");
            return 1;
        }
        bytes_sent += res;
        bytes_read = read(data_fd,buffer,PIPE_BUF);
        if(bytes_read == -1)
        {
            perror("read error\n");
            return 1;
        }
        buffer[bytes_read] = '\0';
    }
    
    close(pipe_fd);
    close(data_fd);

    printf("Process %d finished\n", getpid());  
    return 0;
}
