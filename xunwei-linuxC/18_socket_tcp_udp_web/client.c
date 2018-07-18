#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main(int argc, char **argv)
{
	int cfd;
	int recbyte;
	int sin_size;
	char buffer[1024] = {0};

	struct sockaddr_in s_add, c_add;
	unsigned short portnum = 0x8888;

	printf("Hello,welcome to client!\r\n");

	if(argc != 2)
	{
			printf("usage: echo ip\n");
			return -1;
	}

	cfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == cfd)
	{
			printf("socket fail ! \r\n");
			return -1;
	}

	printf("socket ok !\r\n");

	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr= inet_addr(argv[1]);
	s_add.sin_port=htons(portnum);
	printf("s_addr = %#x ,port : %#x\r\n",s_add.sin_addr.s_addr,s_add.sin_port);

	if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
			printf("connect fail !\r\n");
			return -1;
	}

	printf("connect ok !\r\n");

	while(1)
	{
			if(-1 == (recbyte = read(cfd, buffer, 1024)))
			{
					printf("read data fail !\r\n");
					return -1;
			}

			printf("read ok\r\nREC:\r\n");
			buffer[recbyte]='\0';
			printf("%s\r\n",buffer);
	}

	close(cfd);

	return 0;

}