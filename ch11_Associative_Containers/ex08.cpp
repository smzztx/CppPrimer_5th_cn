#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<std::string> vs;
	std::string s;
	std::cin >> s;
	vs.push_back(s);
	while(std::cin >> s)
	{
		if(std::find(vs.begin(), vs.end(), s) == vs.end())
			vs.push_back(s);
	}

	for(const auto &s : vs)
		std::cout << s << " ";
	std::cout << std::endl;

	return 0;
}