#include <iostream>
#include <chrono>
#include <unistd.h>

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	sleep(1);
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << "in seconds time:";
	std::chrono::duration<double,std::ratio<1,1>> duration_s(end-start);
	std::cout << duration_s.count() << " seconds" << std::endl;

	return 0;
}