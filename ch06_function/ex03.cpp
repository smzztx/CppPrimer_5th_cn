#include <iostream>

int fact(int n)
{
	int ret = 1;
	for(int i = 1;i <= n;++i)
	{
		ret *= i;
	}
	return ret;
}

int main()
{
	std::cout << fact(5) << std::endl;

	return 0;
}