#include <iostream>
#include <string>
#include <regex>

//tx 908.555.1500 (908)5551500
int main()
{
	std::string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})*";
	std::regex r(phone);
	std::smatch m;
	std::string s;
	std::string fmt = "$2.$5.$7";

	while(std::getline(std::cin, s))
	{
		std::smatch result;
		std::regex_search(s,result,r);
		if(!result.empty())
		{
			std::cout << result.prefix() << result.format(fmt) << std::endl;
		}
		else
		{
			std::cout << "Sorry, No match." << std::endl;
		}
	}

	return 0;
}