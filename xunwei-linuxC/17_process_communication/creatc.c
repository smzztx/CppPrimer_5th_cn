#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void filecopy(FILE *,char *);

int main(void)
{
	FILE *fp1;
	long int i = 100000;
	char buf[] = "I want to study Linux!\n";
	char *file1 = "data.txt";
	
	printf("begin!\n");
	
	if((fp1 = fopen(file1,"a+")) == NULL ){
			printf("can't open %s\n",file1);
	}
	while(i--)
	filecopy(fp1,buf);

	fclose(fp1);
	
	printf("over!\n");
	
	return 0;
}

void filecopy(FILE *ifp,char *buf)
{
	char c;
	int i,j;
	j = 0;
	i = strlen(buf)-1;	
	while(i--){
		putc(buf[j],ifp);
		j++;
	}
	putc('\n',ifp);
}
