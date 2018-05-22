#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int sfp, nfp, num = 0;
	struct sockaddr_in s_add,c_add;
	int sin_size;
	unsigned short portnum=0x8888;

	char buffer[100] = {0};

	printf("Hello,welcome to my server !\r\n");

	sfp = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == sfp)
	{
			printf("socket fail ! \r\n");
			return -1;
	}

	printf("socket ok !\r\n");

	bzero(&s_add,sizeof(struct sockaddr_in));
	s_add.sin_family=AF_INET;
	s_add.sin_addr.s_addr=htonl(INADDR_ANY);
	s_add.sin_port=htons(portnum);

	if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))
	{
			printf("bind fail !\r\n");
			return -1;
	}

	printf("bind ok !\r\n");

	if(-1 == listen(sfp,5))
	{
			printf("listen fail !\r\n");
			return -1;
	}

	printf("listen ok\r\n");



			sin_size = sizeof(struct sockaddr_in);

			nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);
			if(-1 == nfp)
			{
					printf("accept fail !\r\n");
					return -1;
			}

			printf("accept ok!\r\nServer start get connect from %#x : %#x\r\n", 
									ntohl(c_add.sin_addr.s_addr), ntohs(c_add.sin_port));
			while(1)
			{
					memset(buffer, 0, 100);
					sprintf(buffer, "hello,welcome to my server(%d) \r\n", num++);
					send(nfp, buffer, strlen(buffer), 0);
					usleep(500000);
			}


			close(nfp);


	close(sfp);

	return 0;
}