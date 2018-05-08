#include <stdio.h>
/*getcwd、getwd和get_current_dir_name
函数的头文件*/
#define __USE_GNU
#include <unistd.h>

#define LENTH 255
int main()
{
	char pwd[LENTH];
	char *wd;
//getcwd函数测试		
	if(!getcwd(pwd,LENTH)){
		perror("getcwd");
		return 1;
	}
	printf("\ngetcwd pwd is %s\n",pwd);
	
//getwd函数测试
	wd = getwd(pwd);
	if(!wd){
		perror("getcwd");
		return 1;
	}
	printf("\ngetwd pwd is %s\n",wd);
	
//get_current_dir_name函数测试	
	wd = get_current_dir_name();
	if(!wd){
		perror("getcwd");
		return 1;
	}
	printf("\nget_current pwd is %s\n",wd);
	
	return 0;
}