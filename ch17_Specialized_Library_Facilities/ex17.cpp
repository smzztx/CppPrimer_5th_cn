#include <iostream>
#include <regex>
#include <string>

int main()
{
	std::string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
	std::regex r(pattern, std::regex::icase);
	std::smatch results;
	std::string s("freind receipt theif receive");

	for(std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
	{
		std::cout << it->str() << std::endl;
	}

	return 0;
}