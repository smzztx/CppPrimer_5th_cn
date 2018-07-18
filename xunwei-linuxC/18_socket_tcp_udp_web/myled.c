#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *data;

	int leds[2] = {0, 0};

	long m, n;

	int exit=0,i,fd;

	printf("Content-Type:text/html;charset=gb2312\n\n");

	printf("<html>\n"); 
	printf("<body>\n");
	printf("<title>iTOP-4412</title> ");
	printf("<h3>iTOP-4412</h3> ");

	data = getenv("QUERY_STRING");
	printf("<p>receive data:%s</p>",data);
	
	while(*data != '\0')
	{
		if(*data=='=')
		switch(*(data+1))
		{
			case '1':leds[0]=1;break;
			case '2':leds[1]=1;break;
			default:exit=1;break;
		}
		if(exit == 1)
			break;
		data++;
	}

	fd=open("/dev/leds",0);

	for(i=0;i<2;i++)
	{
		if(leds[i]==1)
			printf("<p>%d\t</p>",i+1);
		ioctl(fd,leds[i],i);
	}

	printf("</body>\n");
	printf("</html>\n");

	return 0;
}