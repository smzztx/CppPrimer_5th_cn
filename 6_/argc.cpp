#include <stdio.h>
#include <stdlib.h>
int main(int argc,char* argv[])
{
	int i,j;//ascii to integer
	i = atoi(argv[1]);//atoi, atol, atoll, atoq - convert a string to an integer
	j = atoi(argv[2]);
	printf("the program name is %s\n",argv[0]);
	printf("the command line has %d argument\n",argc);
	printf("%d,%d\n",i,j);
	return 0;
}

