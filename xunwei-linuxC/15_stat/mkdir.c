#include <stdio.h>
//mkdir函数头文件
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
	int ret;
		
//检测参数	
	if(argc <2){
		printf("\nPlease input file path\n");
		return 1;
	}
//使用mkdir函数新建目录
	ret = mkdir(argv[1],0777);
	if(ret<0){
		printf("mkdir %s failed!\n",argv[1]);
		return 1;
	}
	printf("mkdir %s suceces！\n",argv[1]);
	
	return 0;
}