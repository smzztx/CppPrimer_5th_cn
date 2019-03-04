#include <iostream>
#include <string>

template<typename T, unsigned size>
constexpr unsigned getSize(const T(&)[size])
{
    return size;
}

int main()
{
	char ac[] = "aabbccdd";

	std::cout << getSize(ac) << std::endl;

	return 0;
}