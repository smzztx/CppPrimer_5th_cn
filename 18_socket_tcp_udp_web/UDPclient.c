#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in servaddr;

	if(argc != 2)
	{
			printf("usgae: ./client [ip]\n");

			return -1;
	}

	/* ����һ��UDP��socket���� */
	sockfd = socket(PF_INET, SOCK_DGRAM, 0);

	/* ����servaddr���� */
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(50001);
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

	char sendline[100];
	sprintf(sendline, "Hello, world!");

	/*  �������� */
	sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

	/* �ر�socket���� */
	close(sockfd);

	return 1;
}