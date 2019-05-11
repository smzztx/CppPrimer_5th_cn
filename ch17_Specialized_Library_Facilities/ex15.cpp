#include <iostream>
#include <regex>
#include <string>

int main()
{
	/*https://en.wikipedia.org/wiki/I_before_E_except_after_C
	**ie in believe, fierce, collie, die, friend
	**ei after c in receive, ceiling, receipt, ceilidh
	*/
	// std::string pattern("[[:alpha:]]*(cei|[^c]ie)[[:alpha:]]*");
	std::string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
	std::regex r(pattern);
	std::smatch results;
	std::cout << "input a word: ";

	std::string s;
	while(std::cin >> s)
	{
		if(std::regex_search(s, results, r))
			std::cout << s <<  ": error" << std::endl;
		else
			std::cout << s <<  ": correct" << std::endl;
	}

	return 0;
}