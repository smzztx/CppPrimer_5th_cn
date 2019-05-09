#include <iostream>
#include <regex>
#include <string>

int main()
{
	//https://en.wikipedia.org/wiki/I_before_E_except_after_C
	std::string pattern("[[:alpha:]]*(cie|[^c]ei)[[:alpha:]]*");
	std::regex r(pattern);
	std::smatch results;

	std::string s;
	while(std::cin >> s)
	{
		if(std::regex_search(s, results, r))
			std::cout << s <<  ": correct" << std::endl;
		else
			std::cout << s <<  ": error" << std::endl;
	}

	

	return 0;
}