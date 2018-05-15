#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

int main(void)
{
    const char *fifo_name = "my_fifo";
    int res,pipe_fd,data_fd,bytes_sent=0;
    char buffer[PIPE_BUF + 1];

    if(access(fifo_name,0))
    {
        res = mkfifo(fifo_name,0666);
        if(res == -1)
        {
            perror("mkfifo error");
            return 1;
        }
    }
    pipe_fd = open(fifo_name,O_WRONLY);
    data_fd = open("data.txt",O_RDONLY);
    if(pipe_fd == -1)
    {
        perror("open pipe error");
        return 1;
    }
    int bytes_read = 0;
    bytes_read = read(data_fd,buffer,PIPE_BUF);
    buffer[bytes_read] = '\0';
    while(bytes_read == -1)
    {
        perror("read error");
        return 1;
    }
    res = write(pipe_fd,buffer,bytes_read);
    if(res == -1)
    {
        perror("write error");
        return 1;
    }
    bytes_sent += res;
    bytes_read = read(data_fd,buffer,PIPE_BUF);
    buffer[bytes_read] = '\0';
    close(pipe_fd);
    close(data_fd);

    printf("Process %d finished\n", getpid());  
    return 0;
}