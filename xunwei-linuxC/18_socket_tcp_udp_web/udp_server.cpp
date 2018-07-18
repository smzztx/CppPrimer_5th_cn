#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>


int main(int argc,char **argv)
{
    int n;
    char recvline[1024] = {0};
    int sockfd;
    struct sockaddr_in servaddr;

    sockfd = socket(PF_INET,SOCK_DGRAM,0);
    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(50001);

    bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    recvfrom(sockfd,recvline,1024,0,NULL,NULL);
    printf("%s\n",recvline);
    close(sockfd);
}