#include <stdio.h>
//通过man文档可以查看到stat函数组头文件
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

//open函数的参数头文件
#include <fcntl.h>

int main(int argc,char *argv[])
{
	struct stat groupstat;
	int fd,ret;
	
	if(argc <2){
		printf("\nPlease input file path\n");
		return 1;
	}

//stat函数测试	
	ret = stat(argv[1],&groupstat);
	if(ret){
		printf("Please make sure file path\n");
		return 1;
	}
	printf("stat function test , %s of st_ino inode is %ld\n",argv[1],groupstat.st_ino);
	
//fstat函数测试
	fd = open(argv[1],O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd<0)
	{
		printf("Please make sure file path\n");
		return 1;
	}
	ret = fstat(fd,&groupstat);
	if(ret){
		printf("Please make sure file path\n");
		return 1;
	}
	printf("fstat function test , %s of st_ino inode is %ld\n",argv[1],groupstat.st_ino);
	
//lstat函数测试	
	ret = lstat(argv[1],&groupstat);
	if(ret){
		printf("Please make sure file path\n");
		return 1;
	}
	printf("lstat function test , %s of st_ino inode is %ld\n",argv[1],groupstat.st_ino);

	return 0;
}