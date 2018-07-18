#include<unistd.h>
#include<stdio.h>
#include<signal.h>

void handler()
{
	printf("hello\n");
}

int main(void)
{
	int i;
	signal(SIGALRM,	handler);
	alarm(5);
	
	for(i=1;i<7;i++){
		printf("sleep %d....\n",i);
		sleep(1);
	}
	
	return 0;
}