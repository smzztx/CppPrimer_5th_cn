#include <map>
#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::multimap<std::string, std::vector<std::string>> familys;
	std::string last_name, first_name;
	std::vector<std::string> vs;

	std::cin >> last_name;
	while(std::cin >> first_name)
	{
		vs.push_back(first_name);
		// familys[last_name].push_back(first_name);
	}
	familys.insert({last_name, vs});

	for(const auto f : familys)
	{
		std::cout << f.first << std::endl;
		for(const auto s : f.second)
			std::cout << s << " ";
		std::cout << std::endl;
	}

	return 0;
}