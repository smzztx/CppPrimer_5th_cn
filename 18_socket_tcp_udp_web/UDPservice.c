#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	int n;
	char recvline[1024] = {0};

	int sockfd;
	struct sockaddr_in servaddr;

	/* ����һ��UDP���ӵ�socket */
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);

	/* ����servaddr���� */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);	
	servaddr.sin_port = htons(50001);

	/* ��servaddr��������socket�� */
	bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

	/* ���տͻ��˷��͵����� */
	recvfrom(sockfd, recvline, 1024, 0, NULL, NULL);

	printf("%s\n", recvline);

	/* �ر�socket���� */
	close(sockfd);
}