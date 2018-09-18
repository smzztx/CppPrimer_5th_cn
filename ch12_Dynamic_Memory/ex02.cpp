#include "StrBlob_ex02.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	const StrBlob b2 = {"a", "b", "c"};

	std::cout << b1.back() << std::endl;
	std::cout << b2.back() << std::endl;

	return 0;
}