#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(void)
{
    int sfp,nfp,num;
    socklen_t sin_size;
    struct sockaddr_in s_add,c_add;
    unsigned short portnum = 0x8888;
    char buffer[100] = {0};

    sfp = socket(AF_INET,SOCK_STREAM,0);

    if(sfp == -1)
    {
        printf("socket failed\n");
        return -1;
    }

    bzero(&s_add,sizeof(struct sockaddr_in));
    s_add.sin_family = AF_INET;
    s_add.sin_addr.s_addr = htonl(INADDR_ANY);
    s_add.sin_port = htons(portnum);
    if(-1 == bind(sfp,(struct sockaddr *)(&s_add),sizeof(struct sockaddr)))
    {
        printf("bind failed\n");
        return -1;
    }
    if(-1 == listen(sfp,5))
    {
        printf("listen failed\n");
        return -1;
    }

    sin_size = sizeof(struct sockaddr_in);
    nfp = accept(sfp,(struct sockaddr *)(&c_add),&sin_size);
    if(-1 == nfp)
    {
        printf("accept failed\n");
        return -1;
    }
    printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n", 
		        ntohl(c_add.sin_addr.s_addr), ntohs(c_add.sin_port));
    while(1)
    {
        memset(buffer,0,100);
        sprintf(buffer, "hello,welcome to my server(%d) \r\n", num++);
        send(nfp, buffer, strlen(buffer), 0);
        usleep(500000);
    }
    close(nfp);
	close(sfp);
}


