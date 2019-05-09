#include <random>
#include <iostream>

unsigned random_func()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}

unsigned random_func(unsigned i)
{
	static std::default_random_engine e(i);
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}

int main()
{
	
	std::cout << random_func() << std::endl;	//default 1
	std::cout << random_func(2) << std::endl;

	return 0;
}