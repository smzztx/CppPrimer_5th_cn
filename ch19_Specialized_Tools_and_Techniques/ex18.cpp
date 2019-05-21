#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

int main()
{
	std::vector<std::string> vs = {"a", "bb", "", "ccc", ""};
	std::function<bool (const std::string&)> fcn = &std::string::empty;

	auto it1 = std::find_if(vs.begin(), vs.end(), fcn);
	std::cout << "function: " << it1 - vs.begin() << std::endl;

	auto it2 = std::find_if(vs.begin(), vs.end(), std::mem_fn(&std::string::empty));
	std::cout << "mem_fn: " << it2 - vs.begin() << std::endl;

	auto it3 = std::find_if(vs.begin(), vs.end(), std::bind(&std::string::empty, std::placeholders::_1));
	std::cout << "bind: " << it3 - vs.begin() << std::endl;

	std::cout << "count_if: " << std::count_if(vs.begin(), vs.end(), fcn) << std::endl;

	return 0;
}