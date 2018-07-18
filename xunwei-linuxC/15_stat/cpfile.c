#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//argv[1] is oldpath ; argv[2] is newpath
#define LENTH 1024
int main(int argc,char *argv[])
{
	int fds,fdt;
	char buffer[LENTH];
	char *fileold,*filenew;
	
	fileold = argv[1];
	filenew = argv[2];
	
	if(argc <3){
		printf("\nPlease input file path\n");
		return 1;
	}

	//打开oldpath		
	fds = open(fileold,O_RDWR);
	if(fds<0)
	{
		printf("Please make sure file path\n");
		return 1;
	}
	
	//打开newpath,如果没有则创建目标文件
	fdt = open(filenew,O_WRONLY|O_CREAT);
	if(fdt<0)
	{
		printf("Please make sure file path\n");
		return 1;
	}

	//读和写操作
	while(read(fds,buffer,LENTH)){
		write(fdt,buffer,strlen(buffer));
	}
	
	//关闭文件
	close(fds);
	close(fdt);
	
	printf("cp to finished!\n");
	printf("cp %s to %s success!\n",fileold,filenew);
	return 0;
}
