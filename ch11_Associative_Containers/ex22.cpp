#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

int main()
{
	std::map<std::string, std::vector<int>> m1;
	std::pair<std::string, std::vector<int>> p1({"aaa", {1,2,3,4}});
	std::pair<std::map<std::string, std::vector<int>>::iterator, bool> ret = m1.insert(p1);
	// std::pair<std::map<std::string, std::vector<int>>::iterator, bool> ret = m1.insert({"aaa", {1,2,3,4}});

	return 0;
}