#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

//using std::cout;
//using std::endl;
using namespace std;

int main()
{
	time_t timep;
	struct tm *tblock;
	struct timeval tpstart,tpend;
	float timeuse; 
	sleep(1);
	time(&timep);
	cout<<timep<<endl;
	cout<<asctime(gmtime(&timep))<<endl;
	cout<<"sleep(1)"<<"\t"<<"11"<<endl;
	gettimeofday(&tpstart,nullptr); //记录开始时间
	usleep(1000000);
	gettimeofday(&tpend,NULL); //记录结束时间
	timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec; //计算差值
	timeuse /= 1000000;
	cout<<"timeuse:"<<timeuse<<endl;
	timep = time(NULL);
	cout<<timep<<endl;
	tblock = localtime(&timep);
	cout<<tblock<<endl;
	cout<<"usleep(1000000)"<<endl;

	return 0;
}


