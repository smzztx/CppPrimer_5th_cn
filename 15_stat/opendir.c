#include <stdio.h>
//opendir和closedir函数头文件
#include <dirent.h>
#include <sys/types.h>

int main(int argc,char *argv[])
{
	int ret;
	DIR *dir;
	
//检测参数	
	if(argc <2){
		printf("\nPlease input file path\n");
		return 1;
	}
//使用opendir函数打开目录
	dir = opendir(argv[1]);
	if(dir==NULL){
		printf("opendir %s failed!\n",argv[1]);
		return 1;
	}
	printf("opendir %s suceces！\n",argv[1]);
//使用closedir函数关闭目录
	closedir(dir);
	
	return 0;
}