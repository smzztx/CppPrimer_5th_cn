#include <iostream>
#include <string>
#include <sstream>

std::istream &iofunction(std::istream &is)
{
	std::string s;
	while(is >> s)
		std::cout << s << std::endl;
	is.clear();
	return is;
}

int main()
{
	std::istringstream istrs("aa\nbb\ncc dd");
	iofunction(istrs);

	std::string s1;
	while(std::cin >> s1)
		std::cout << s1 << std::endl;

	return 0;
}