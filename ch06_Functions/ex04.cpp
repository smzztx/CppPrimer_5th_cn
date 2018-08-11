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
	int n;
	std::cin >> n;
	std::cout << fact(n) << std::endl;

	return 0;
}