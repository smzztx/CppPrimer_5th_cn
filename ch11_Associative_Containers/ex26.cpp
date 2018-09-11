#include <map>
#include <iostream>
#include <string>

int main()
{
	std::map<int, std::string> m1({{1, "aaa"}});
	std::map<int, std::string>::key_type i1 = 1;
	std::map<int, std::string>::mapped_type s1;

	s1 = m1[i1];
	std::cout << i1 << " " << s1 << std::endl;

	return 0;
}