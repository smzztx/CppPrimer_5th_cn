#include <iostream>

int main()
{
	std::cout << "/*";
	std::cout << "*/";
	std::cout << /* "*/" */";	//add "
	std::cout << /* "*/" /* "/*" */;

	return 0;
}