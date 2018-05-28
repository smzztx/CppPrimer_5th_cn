#include <stdio.h>
#include <sys/types.h>  /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc,char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        printf("usage:ip|n");
        return -1;
    }
    sockfd = socket(PF_INET,SOCK_DGRAM,0);

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(50001);
    servaddr.sin_addr.s_addr = inet_addr(argv[1]);

    char sendline[100];
    sprintf(sendline,"hello world");
    sendto(sockfd,sendline,strlen(sendline),0,(struct sockaddr *)&servaddr,sizeof(servaddr));

    close(sockfd);
    return 0;
}
