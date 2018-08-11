#include <iostream>

int absolute(int n)
{
	return (n > 0) ? n : -n;
}

int main()
{
	std::cout << absolute(5) << std::endl;

	return 0;
}