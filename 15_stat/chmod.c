#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	int fd,ret;
	
	if(argc <3){
		printf("\nPlease input file path\n");
		return 1;
	}
	
//chmod函数测试	
	ret = chmod(argv[1],0777);
	if(ret<0){
		printf("Please make sure file path\n");
		return 1;
	}
	printf("chmod %s 0777 is success!\n",argv[1]);

//fchmod函数测试		
	fd = open(argv[2],O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd<0)
	{
		printf("Please make sure file path\n");
		return 1;
	}
	ret = fchmod(fd,0555);
	if(ret<0){
		printf("Please make sure file path\n");
		return 1;
	}
	printf("fchmod %s 0555 is success!\n",argv[1]);
	
	return 0;
}
