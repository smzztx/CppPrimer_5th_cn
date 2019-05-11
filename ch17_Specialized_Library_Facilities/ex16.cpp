#include <iostream>
#include <regex>
#include <string>

int main()
{
	std::string pattern("[^c]ei");
	std::regex r(pattern);
	std::smatch results;

	std::string s;
	while(std::cin >> s)
	{
		if(std::regex_search(s, results, r))
		{
			std::cout << s <<  ": correct" << std::endl;
			for (size_t i = 0; i < results.size(); ++i) 
				std::cout << i << ": " << results[i] << '\n';
		}
		else
		{
			std::cout << s <<  ": error" << std::endl;
		}
	}

	return 0;
}