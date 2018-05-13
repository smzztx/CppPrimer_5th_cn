#include <unistd.h>
#include <iostream>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

using namespace std;

int main(int argc,char *argv[])
{
	pid_t pid;
	int ret_pipe,pipefd[2]={0};
	char buf;
	int rc,c;

	ret_pipe = pipe(pipefd);
	if(ret_pipe == -1)
	{
		cout<<"pipe error"<<endl;
	}

	pid = fork();


	if(pid == -1)
	{
		cout<<"fork error"<<endl;
		return 1;
	}else if(pid == 0)
	{
		cout<<"child process"<<endl;
		close(pipefd[1]);		//close write
		// while((rc=read(pipefd[0],&c,1)) > 0)
		// {
		// 	putchar(c);
		// 	//cout<<"child c: "<<c<<endl;
		// }
		while (read(pipefd[0], &buf, 1) > 0)
			write(STDOUT_FILENO, &buf, 1);

		write(STDOUT_FILENO, "\n", 1);
		close(pipefd[0]);
		_exit(EXIT_SUCCESS);

		return 0;
	}else
	{
		cout<<"father process"<<endl;
		cout<<"child process is:"<<pid<<endl;
		close(pipefd[0]);		//close read
		// while((c=getchar()) > 0)
		// {
		// 	rc = write(pipefd[1],&c,1);
		// 	if(rc == -1)
		// 	{
		// 		cout<<"parent: write"<<endl;
		// 		close(pipefd[1]);
		// 		return 1;
		// 	}
		// }
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);          /* Reader will see EOF */
		wait(NULL);                /* Wait for child */
		exit(EXIT_SUCCESS);

		// close(pipefd[1]);
	}
	
	return 0;
}
