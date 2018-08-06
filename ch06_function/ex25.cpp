#include <iostream>

int main(int argc, char const *argv[])
{
	const std::string s1 = argv[1], s2 = argv[2];

	std::cout << s1 + s2 << std::endl;

	return 0;
}