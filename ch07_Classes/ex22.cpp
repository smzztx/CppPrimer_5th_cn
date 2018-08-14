//test Person_ex15.h
#include <string>
#include <iostream>
#include "Person_ex15.h"

int main()
{
	Person person1;
	print(std::cout, person1) << std::endl;

	Person person2("tx", "hangzhou");
	print(std::cout, person2) << std::endl;
	std::cout << person2.get_name() << " " << person2.get_address() << std::endl;

	Person person3("tx");
	print(std::cout, person3) << std::endl;

	Person person4(std::cin);
	print(std::cout, person4) << std::endl;

	return 0;
}