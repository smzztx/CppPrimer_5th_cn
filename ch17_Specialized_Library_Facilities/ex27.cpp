#include <iostream>
#include <string>
#include <regex>

bool valid(const std::smatch &m)
{
	if(m[3].matched)
		return true;
	else
		return !m[2].matched;
}

//111112222
//11111-2222
//11111
//11111-
int main()
{
	std::string mail = "(\\d{5})([-])?(\\d{4})?";
	std::regex r(mail);
	std::smatch m;
	std::string s;
	std::string fmt = "$1-$3";

	while(std::getline(std::cin, s))
	{
		std::cout << std::regex_replace(s, r, fmt) << std::endl;
	}

	return 0;
}