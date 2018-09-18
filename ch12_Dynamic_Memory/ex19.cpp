#include "StrBlob_ex19.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	StrBlobPtr p1(b1);

	std::cout << p1.deref() << std::endl;
	p1.incr();
	std::cout << p1.deref() << std::endl;
	p1.incr();
	std::cout << p1.deref() << std::endl;
	p1.incr();
	// std::cout << p1.deref() << std::endl;

	return 0;
}