#include <iostream>
#include <stdexcept>

int main()
{
	int i1,i2;
	std::cin >> i1 >> i2;
	if(i2 == 0)
	{
		throw std::runtime_error("divisor can't be 0");
	}
	std::cout << i1/i2 << std::endl;

	return 0; 
}