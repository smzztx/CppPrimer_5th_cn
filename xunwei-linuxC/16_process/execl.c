#include<stdio.h> 
#include<string.h>
#include<stdlib.h>
#include <unistd.h>

//exec函数族
int main(void)
{
	if(execl("/mnt/udisk/helloexec","helloexec","execl",NULL) == -1){
		perror("execl error");
		exit(1);
	}
	//程序已经跳转走，如果正常execl不反回错误，下面的代码不会执行！
	printf("execl error！\n");
	return 0;
}