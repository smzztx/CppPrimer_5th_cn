#include <stdio.h>
#include <unistd.h>

main()
{
	pid_t pid;
	int i=100;
	
	pid = fork();
	//���ó���
	if(pid == -1){
		printf("fork failed\n");
		return 1;
	}
	//���ظ��������ӽ��̺ţ�����ֵ����0
	else if(pid){
		i++;
		printf("\nThe father i = %d\n",i);
		printf("The father return value is %d\n",pid);
		printf("The father pid is %d\n",getpid());
		printf("The father ppid is %d\n",getppid());
		while(1);
	}
	//�����ӽ���0������ֵ����0���ظ��ӽ���
	else{
		i++;
		printf("\nThe child i = %d\n",i);
		printf("The child return value is %d\n",pid);
		printf("The child pid is %d\n",getpid());
		printf("The child ppid is %d\n",getppid());
		while(1);
	}
	return 0;
}