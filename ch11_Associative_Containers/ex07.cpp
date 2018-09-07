#include <map>
#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::map<std::string, std::vector<std::string>> familys;
	std::string last_name, first_name;

	std::cin >> last_name;
	while(std::cin >> first_name)
	{
		familys[last_name].push_back(first_name);
	}

	for(const auto f : familys)
	{
		std::cout << f.first << std::endl;
		for(const auto s : f.second)
			std::cout << s << " ";
		std::cout << std::endl;
	}

	return 0;
}