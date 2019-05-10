#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::fstream fs("../ch08_The_IO_Library/data");
	char tmp[200];
	fs.getline(tmp, 2, '\n');
	std::cout << tmp << std::endl;
	std::cout << fs.gcount() << std::endl;

	fs.getline(tmp, 2, '\n');
	std::cout << tmp << std::endl;
	std::cout << fs.gcount() << std::endl;
	std::cout << std::boolalpha << (fs.rdstate() == std::ios_base::failbit) << std::endl;
	// std::cout << std::ios_base::goodbit << std::endl;
	// std::cout << std::ios_base::badbit << std::endl;
	// std::cout << std::ios_base::failbit << std::endl;
	// std::cout << std::ios_base::eofbit << std::endl;
	//https://en.cppreference.com/w/cpp/io/ios_base/iostate

	return 0;
}