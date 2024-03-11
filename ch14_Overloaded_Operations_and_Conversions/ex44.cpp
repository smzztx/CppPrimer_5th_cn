#include <string>
#include <iostream>
#include <algorithm>
#include <map>
#include <functional>

int add(int i, int j) { return i + j; }

int main()
{
	
	auto mod = [](int i, int j) { return i % j; };
	struct divide
	{
		int operator()(int dividend, int divisor)
		{
			return dividend / divisor;
		}
	};
	std::map<std::string, std::function<int(int, int)>> binops = {
		{"+", add},
		{"-", std::minus<int>()},
		{"/", divide()},
		{"*", [](int i, int j) { return i * j; }},
		{"%", mod}
	};

	std::cout << binops["+"](10, 5) << std::endl;
	std::cout << binops["-"](10, 5) << std::endl;
	std::cout << binops["*"](10, 5) << std::endl;
	std::cout << binops["/"](10, 5) << std::endl;
	std::cout << binops["%"](10, 5) << std::endl;

	return 0;
}