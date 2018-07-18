#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 100

main()
{
	int fd;
	const char *test1 = "test/test1";
	const char *test2 = "test/test2";
	const char *test3 = "test/test3";
	ssize_t length_w,length_r=MAX_SIZE,ret;
	char buffer_write[] = "hello c++";
	char buffer_read[MAX_SIZE];

	if((fd=open(test1,O_RDWR,0777))<0)
	{
		printf("open %s failed!\n",test1);
	}
	printf("%s fd is %d\n",test1,fd);

	if((fd=open(test2,O_RDWR|O_CREAT,0777))<0)
	{
		printf("open %s failed!\n",test2);
	}
	printf("%s fd is %d\n",test2,fd);
	length_w = write(fd,buffer_write,strlen(buffer_write));
	if(length_w == -1)
	{
		perror("write\n");
	}else
	{
		printf("write ok\n");
	}
	if(ret = read(fd,buffer_read,length_r))
	{
		perror("read");
	}else
	{
		printf("files content is %s \n",buffer_read);
	}
	close(fd);
	
	fd = creat(test3,0777);
	if(fd == -1)
	{
		printf("open %s failed!\n",test3);
	}
	else
	{
		printf("create %s is succeed\n",test3);
	}

}


