#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
	char *arg[] = {"ls","-a",NULL};
	
	if(fork() == 0){
		//in child1
		printf("fork1 is OK;execl\n");
		
		if(execl("/bin/ls","ls","-a",NULL) == -1){
			perror("execl error");
			exit(1);
		}
	}

	usleep(20000);
	if(fork() == 0){
		//in child2
		printf("fork2 is OK;execv\n");
		
		if(execv("/bin/ls",arg) == -1){
			perror("execv error");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0){
		//in child3
		printf("fork3 is OK;execlp\n");
		
		if(execlp("ls","ls","-a",NULL) == -1){
			perror("execlp error");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0){
		//in child4
		printf("fork4 is OK;execvp\n");
		
		if(execvp("ls",arg) == -1){
			perror("execvp error");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0){
		//in child5
		printf("fork5 is OK;execle\n");
		
		if(execle("/bin/ls","ls","-a",NULL,NULL) == -1){
			perror("execle error");
			exit(1);
		}
	}
	
	usleep(20000);
	if(fork() == 0){
		//in child6
		printf("fork6 is OK;execve\n");
		
		if(execve("/bin/ls",arg,NULL) == -1){
			perror("execve error");
			exit(1);
		}
	}

	usleep(20000);
	return 0;
}