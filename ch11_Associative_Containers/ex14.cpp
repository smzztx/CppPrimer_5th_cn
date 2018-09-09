#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <utility>

int main()
{
	std::map<std::string, std::vector<std::pair<std::string, std::string>>> familys;
	std::string last_name, first_name, birthday;

	std::cin >> last_name;
	while(std::cin >> first_name >> birthday)
	{
		familys[last_name].emplace_back(first_name, birthday);
	}

	for(const auto f : familys)
	{
		std::cout << f.first << std::endl;
		for(const auto p : f.second)
			std::cout << p.first << " " << p.second << std::endl;
		std::cout << std::endl;
	}

	return 0;
}