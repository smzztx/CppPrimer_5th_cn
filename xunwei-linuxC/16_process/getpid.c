#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
	pid_t idp,id;
	
	idp = getppid();
	printf("ppid = %d\n",idp);
	
	id = getpid();
	printf("pid = %d\n",id);
}