#include <utility>
#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::vector<std::pair<std::string, int>> vp;
	int i;
	std::string s;

	while(std::cin >> s >> i)
	{
		// vp.push_back(std::pair<std::string, int>(s, i));
		// std::pair<std::string, int> p(s, i); vp.push_back(p);
		// vp.push_back({s, i});
		// vp.push_back(make_pair(s, i));
		// std::pair<std::string, int> p = {s, i}; vp.push_back(p);
		vp.emplace_back(s, i);
	}

	for(const auto &p : vp)
		std::cout << p.first << " " << p.second << std::endl;	

	return 0;
}