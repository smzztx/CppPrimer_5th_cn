#include <stdio.h>
//unlink函数头文件
#include <unistd.h>

int main(int argc,char *argv[])
{
	int ret;
	
	if(argc <2){
		printf("\nPlease input file path\n");
		return 1;
	}

//测试unlink函数
	ret = unlink(argv[1]);
	if(ret)
	{
		printf("unlink failed");
		return 1;
	}
	printf("unlink %s is success!\n",argv[1]);
	
	return 0;
}