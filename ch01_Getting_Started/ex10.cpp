#include <iostream>

int main()
{
	int i = 10 ,sum = 0;

	while(i >= 0)
	{
		sum += i;
		--i;
	}
	std::cout << sum << std::endl;

	return 0;
}