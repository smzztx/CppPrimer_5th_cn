#include <stdio.h>
//rmdir函数头文件
#include <unistd.h>

int main(int argc,char *argv[])
{
	int ret;
		
//检测参数	
	if(argc <2){
		printf("\nPlease input file path\n");
		return 1;
	}
//使用rmdir函数删除目录
	ret = rmdir(argv[1]);
	if(ret<0){
		printf("rmdir %s failed!\n",argv[1]);
		return 1;
	}
	printf("rmdir %s suceces！\n",argv[1]);
	
	return 0;
}