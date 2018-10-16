#include <time.h>
#include <iostream>
#include <unistd.h>

int main()
{
	clock_t start,finish;
	start = clock();
	std::cout << start << std::endl;
	sleep(1);
	finish = clock();
	std::cout << (finish - start) << std::endl;

	return 0;
}