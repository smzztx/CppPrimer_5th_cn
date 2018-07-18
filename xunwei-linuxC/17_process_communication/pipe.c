#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

//进程读函数
void read_data(int *);
//进程写函数 
void write_data(int *);


int main(int argc,char *argv[])
{
	int pipes[2],rc;
	pid_t pid;
		
	rc = pipe(pipes);	//创建管道                 
	if(rc == -1){
		perror("\npipes\n");
		exit(1);
	}
		
	pid = fork();	//创建进程 

	switch(pid){
		case -1:
			perror("\nfork\n");
			exit(1);
		case 0:
			read_data(pipes);	//相同的pipes
		default:
			write_data(pipes);	//相同的pipes
	}	
	return 0;
}

//进程读函数
void read_data(int pipes[])
{
	int c,rc;
	
	//由于此函数只负责读，因此将写描述关闭(资源宝贵)
	close(pipes[1]);
	
	//阻塞，等待从管道读取数据
	//int 转为 unsiged char 输出到终端
	while( (rc = read(pipes[0],&c,1)) > 0 ){  		
		putchar(c);       		                       
	}

	exit(0);
}

//进程写函数
void write_data(int pipes[])
{
	int c,rc;

	//关闭读描述字
	close(pipes[0]);                          

	while( (c=getchar()) > 0 ){
		rc = write( pipes[1], &c, 1);	//写入管道
		if( rc == -1 ){
			perror("Parent: write");
			close(pipes[1]);
			exit(1);
		}
	}

	close( pipes[1] );
	exit(0);
}
