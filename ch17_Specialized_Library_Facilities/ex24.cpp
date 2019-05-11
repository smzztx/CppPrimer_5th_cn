#include <iostream>
#include <string>
#include <regex>

//908.555.1500
//(908)5551500
//(908.555.1500
int main()
{
	std::string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
	std::regex r(phone);
	std::smatch m;
	std::string s;
	std::string fmt = "$2.$5.$7";

	while(std::getline(std::cin, s))
	{
		std::cout << std::regex_replace(s, r, fmt) << std::endl;
	}

	return 0;
}