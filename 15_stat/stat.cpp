#include <sys/types.h>
#include <sys/stat.h>
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
		cout<<"please make sure the file path"<<endl;
		return 1;
	}

	ret = stat(argv[1],&groupstat);
	if(ret)
	{	
		cout<<"please make sure the file path"<<endl;
		return 1;
	}
	cout<<"stat function test,"<<argv[1]<<" of st_ino inode is "<<groupstat.st_ino<<endl;

	return 0;
}


