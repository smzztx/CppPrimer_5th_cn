#include <stdio.h>
/*getcwd��getwd��get_current_dir_name
������ͷ�ļ�*/
#define __USE_GNU
#include <unistd.h>

#define LENTH 255
int main()
{
	char pwd[LENTH];
	char *wd;
//getcwd��������		
	if(!getcwd(pwd,LENTH)){
		perror("getcwd");
		return 1;
	}
	printf("\ngetcwd pwd is %s\n",pwd);
	
//getwd��������
	wd = getwd(pwd);
	if(!wd){
		perror("getcwd");
		return 1;
	}
	printf("\ngetwd pwd is %s\n",wd);
	
//get_current_dir_name��������	
	wd = get_current_dir_name();
	if(!wd){
		perror("getcwd");
		return 1;
	}
	printf("\nget_current pwd is %s\n",wd);
	
	return 0;
}