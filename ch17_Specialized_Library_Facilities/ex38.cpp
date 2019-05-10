#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::fstream fs("../ch08_The_IO_Library/data");
	char tmp[200];

	// while(fs.getline(tmp, 200, ' '))
	// 	std::cout << tmp << std::endl;
	fs.getline(tmp, 200, ' ');
	std::cout << tmp << std::endl;
	std::cout << fs.gcount() << std::endl;
	std::cout <<fs.rdstate() << std::endl;
	fs.getline(tmp, 200, ' ');
	std::cout <<fs.rdstate() << std::endl;

	return 0;
}