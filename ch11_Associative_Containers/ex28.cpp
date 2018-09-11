#include <map>
#include <vector>
#include <string>
#include <iostream>

int main()
{
	std::map<std::string, std::vector<int>> m1 = {{"aa", {1,2,3,4,5}}};
	std::map<std::string, std::vector<int>>::iterator m_iter = m1.find("aa");

	return 0;
}