#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc,char *argv[])
{
    int cfd,recbyte,sin_size;
    char buffer[1024] = {0};

    struct sockaddr_in s_add,c_add;
    unsigned int portnum = 0x8888;

    if(argc != 2)
    {
        printf("usage:echo ip\n");
        return -1;
    }

    cfd = socket(AF_INET,SOCK_STREAM,0);
    if(-1 == cfd)
    {
        printf("socket failed\n");
        return -1;
    }
    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family = AF_INET;
    s_add.sin_addr.s_addr = inet_addr(argv[1]);
    s_add.sin_port = htons(portnum);

    if(-1 == connect(cfd,(struct sockaddr *)(&s_add),sizeof(struct sockaddr)))
    {
        printf("connect failed\n");
        return -1;
    }

    while(1)
    {
        if(-1 == (recbyte = read(cfd,buffer,1024)))
        {
            printf("read failed\n");
            return -1;
        }
        printf("read ok\r\nREC:\r\n");
        buffer[recbyte]='\0';
        printf("%s\r\n",buffer);
    }
    close(cfd);
    return 0;
}

