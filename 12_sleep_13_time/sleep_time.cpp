#include <iostream>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <chrono>

//using std::cout;
//using std::endl;
using namespace std;

int main()
{
	using namespace std::chrono;
	time_t timep;
	struct tm *tblock;
	struct timeval tpstart,tpend;
	float timeuse; 
	//auto last_time = high_resolution_clock::from_time_t(0);
	auto last_time = high_resolution_clock::now();
	sleep(1);
	auto cur_time = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(cur_time - last_time).count();
	cout<<"duration:"<<duration<<endl;

	time(&timep);
	cout<<timep<<endl;
	cout<<ctime(&timep)<<endl;
	cout<<asctime(gmtime(&timep))<<endl;

	cout<<"sleep(1)"<<"\t"<<"11"<<endl;
	gettimeofday(&tpstart,nullptr); //记录开始时间
	auto l_time = system_clock::now();
	usleep(1000000);
	gettimeofday(&tpend,NULL); //记录结束时间
	timeuse = 1000000*(tpend.tv_sec-tpstart.tv_sec)+tpend.tv_usec-tpstart.tv_usec; //计算差值
	timeuse /= 1000000;
	cout<<"timeuse:"<<timeuse<<endl;
	timep = time(NULL);
	cout<<timep<<endl;

	tblock = localtime(&timep);
	cout<<asctime(tblock)<<endl;
	cout<<ctime(&timep)<<endl;

	auto c_time = system_clock::now();
	auto d = duration_cast<microseconds>(c_time - l_time).count();
	cout<<"duration:"<<d<<endl;

	cout<<"usleep(1000000)"<<endl;

	return 0;
}


