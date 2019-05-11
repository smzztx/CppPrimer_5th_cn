#include <iostream>
#include <regex>

int main()
{
	try
	{
		std::regex r1("[[:anum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}

	try
	{
		std::regex r1("[[:alnum:]+\\.(cpp|cxx|cc)$", std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}	

	try
	{
		std::regex r1("[[:alnum:]]+\\.cpp|cxx|cc)$", std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}

	return 0;
}