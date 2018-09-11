#include <map>
#include <string>
#include <iostream>
#include <set>

int main()
{
	std::multimap<std::string, std::string> m1 = {{"bb", "lalala"}, {"aa", "bcd"}, {"aa", "abc"}, {"aa", "cde"}};

	std::map<std::string, std::multiset<std::string>> order_m1;
	for(const auto p : m1)
		order_m1[p.first].insert(p.second);

	for (const auto &p : order_m1)
	{
		std::cout << p.first << std::endl;
		for(const auto s : p.second)
			std::cout << s << " ";
		std::cout << std::endl;
	}

	return 0;
}