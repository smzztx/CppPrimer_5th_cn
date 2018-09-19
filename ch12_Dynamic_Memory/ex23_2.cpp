#include <string>
#include <iostream>
#include <cstring>

int main()
{
	std::string a = "aaa";
	std::string b = "bbb";
	std::string *ps = new std::string;

	*ps = a + b;
	std::cout << *ps << std::endl;
	delete ps;

	return 0;
}