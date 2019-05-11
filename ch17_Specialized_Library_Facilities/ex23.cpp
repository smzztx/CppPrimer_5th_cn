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

	while(std::getline(std::cin, s))
	{
		for(std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
			if(valid(*it))
				std::cout << "valid: " << it->str() << std::endl;
			else
				std::cout << "not valid: " << it->str() << std::endl;
	}

	return 0;
}