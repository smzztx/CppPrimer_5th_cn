#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//chdir和fchdir函数头文件
#include <unistd.h>

#define LENTH 255

int main(int argc,char *argv[])
{
	int ret;
	char pwd[LENTH];

//检测参数	
	if(argc <3){
		printf("\nPlease input file path\n");
		return 1;
	}
	
//getcwd函数获取当前目录		
	if(!getcwd(pwd,LENTH)){
		perror("getcwd");
		return 1;
	}
	printf("\ngetcwd pwd is %s\n",pwd);
	
//使用chdir函数转入其他目录
	ret = chdir(argv[1]);
	if(ret){
		printf("Please make sure file path\n");
		return 1;
	}
	printf("chdir %s is success！\n",argv[1]);
	
//转入其他目录，完成操作
//使用rmdir函数删除目录
	ret = rmdir(argv[2]);
	if(ret<0){
		printf("rmdir %s failed!\n",argv[2]);
		return 1;
	}
	printf("rmdir %s is success！\n",argv[2]);
	
//再次使用chdir回到pwd保存的目录
	ret = chdir(pwd);
	if(ret){
		printf("Please make sure file path\n");
		return 1;
	}
	printf("chdir %s is success！\n",pwd);

	return 0;
}