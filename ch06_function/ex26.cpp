#include <iostream>

int main(int argc, char const *argv[])
{
	std::string s;

	for(int i = 0; i != argc; ++i)
		s += std::string(argv[i]) + " ";
	std::cout << s << std::endl;

	return 0;
}