#include <map>
#include <string>
#include <iostream>

int main()
{
	std::map<int, std::string> m = {{1,"aa"}};
	std::map<int, std::string>::iterator m_iter = m.begin();

	m_iter->second = "bb";
	std::cout << m_iter->second <<std::endl;

	return 0;
}