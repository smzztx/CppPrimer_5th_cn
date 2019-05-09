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

unsigned random_func(unsigned i, unsigned min, unsigned max)
{
	static std::default_random_engine e(i);
	static std::uniform_int_distribution<unsigned> u(min, max);
	return u(e);
}

int main()
{
	
	std::cout << random_func() << std::endl;	//default 1
	std::cout << random_func(2) << std::endl;
	for(int i = 0; i < 10; ++i)
		std::cout << random_func(1, 0, 10) << std::endl;

	return 0;
}