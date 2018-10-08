#include "HasPtr_ex30.h"
#include <iostream>

int main()
{
	HasPtr hp1("aaa"),hp2("bbb");
	swap(hp1,hp2);
	std::cout << "main" << std::endl;

	return 0;
}