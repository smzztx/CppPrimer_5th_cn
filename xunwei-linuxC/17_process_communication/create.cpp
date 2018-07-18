#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

using namespace std;
int main(void)
{
    int fd,ret;
    char buf[] = "I want to study Linux!\n";

    fd = open("data.txt",O_RDWR|O_CREAT,0666);

    if(fd == -1)
    {
        // cout<<"open error"<<endl;
        perror("open error");
        
        return 1;
    }
    for(int i = 0;i<10000;i++)
    {
        ret = write(fd,buf,strlen(buf));
        if(ret == -1)
        {
            perror("write error");
        }
    }

    ret = close(fd);
    if(ret == -1)
    {
        perror("close error");
        // cout<<"close error"<<endl;
    }
    return 0;
}