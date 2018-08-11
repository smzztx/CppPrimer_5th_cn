#include <iostream>
#include <vector>
#include <cassert>

// #define NDEBUG	//this is not work for assert(), we should use $ g++ -o ex47 ex47.cpp -D NDEBUG -std=c++11

void read_vi(std::vector<int>::const_iterator iterator_begin, std::vector<int>::const_iterator iterator_end)
{
	#ifndef NDEBUG
		std::cerr << iterator_end - iterator_begin << __func__ << " " << __FILE__ << " " 
		<< __LINE__ << " " << __TIME__ << " " << __DATE__ << std::endl;
	#endif
	assert(0);

	if(iterator_begin != iterator_end)
	{
		std::cout << *iterator_begin << " ";
		return read_vi(++iterator_begin, iterator_end);
	}else
	{
		std::cout << std::endl;
		return;
	}
}

int main()
{
	std::vector<int> v{1,2,3,4,5};

	read_vi(v.begin(), v.end());

	return 0;
}