#include "String_ex16.h"
#include <vector>
#include <iostream>

int main()
{
	std::vector<String> v;
	v.push_back("aaa");
	v.push_back("bbb");
	std::cout << v[1] << std::endl;

	return 0;
}