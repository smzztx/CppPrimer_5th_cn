#include "StrBlob_ex21.h"
#include <iostream>

int main()
{
	const StrBlob b1 = {"a", "an", "the"};
	ConstStrBlobPtr p1(b1);

	std::cout << p1.deref() << std::endl;
	p1.incr();
	std::cout << p1.deref() << std::endl;
	p1.incr();
	std::cout << p1.deref() << std::endl;
	p1.incr();
	// std::cout << p1.deref() << std::endl;

	return 0;
}