#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

using namespace std;

int main(int argc,char *argv[])
{
	struct stat groupstat;
	int fd,ret;

	cout<<argc<<" and "<<argv[1]<<endl;
	if(argc < 2)
	{
		cout<<"1:please make sure the file path"<<endl;
		return 1;
	}

	ret = stat(argv[1],&groupstat);
	if(ret)
	{	
		cout<<"2:please make sure the file path"<<endl;
		return 1;
	}
	cout<<"stat function test,"<<argv[1]<<" of st_ino inode is "<<groupstat.st_ino<<endl;

//fstat
	fd = open(argv[1],O_RDWR|O_NOCTTY|O_NDELAY);
	if(fd<0)
	{
		cout<<"3:please make sure the file path"<<endl;
		return 1;
	}
	ret = fstat(fd,&groupstat);
	if(ret)
	{	
		cout<<"4:please make sure the file path"<<endl;
		return 1;
	}
	cout<<"fstat function test,"<<argv[1]<<" of st_ino inode is "<<groupstat.st_ino<<endl;

//lstat
	ret = lstat(argv[1],&groupstat);
	if(ret)
	{	
		cout<<"5:please make sure the file path"<<endl;
		return 1;
	}
	cout<<"lstat function test,"<<argv[1]<<" of st_ino inode is "<<groupstat.st_ino<<endl;
	

	return 0;
}


