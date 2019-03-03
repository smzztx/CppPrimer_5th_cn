#include <iostream>

class Sales_data{ };

template<typename T>
int compare(const T &lhs, const T &rhs)
{
	if(lhs < rhs) return -1;
	if(rhs < lhs) return 1;
	return 0;
}

int main()
{
	std::cout << compare(Sales_data(), Sales_data()) << std::endl;

	return 0;
}