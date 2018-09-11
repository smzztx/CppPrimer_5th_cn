#include <map>
#include <string>
#include <iostream>

int main()
{
	std::multimap<std::string, std::string> m1 = {{"aa", "abc"}, {"aa", "bcd"}, {"aa", "cde"}};

	m1.erase(m1.find("aa"));

	for (const auto &p : m1)
		std::cout << p.first << " " << p.second << std::endl;

	return 0;
}