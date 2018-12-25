#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<int> vi = {1025, 1024, 1, 2, 2000};
	std::vector<std::string> vs = {"pooh", "abc", "123"};
	std::vector<int> vi2 = {1, 3, 4, 5, 6};

	std::cout << std::count_if(vi.begin(), vi.end(), std::bind(std::greater<int>(), std::placeholders::_1, 1024)) << std::endl;

	std::cout << *(std::find_if(vs.begin(), vs.end(), std::bind(std::not_equal_to<std::string>(), std::placeholders::_1, "pooh"))) << std::endl;

	std::transform(vi2.begin(), vi2.end(), vi.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));

	for(const auto i : vi)
		std::cout << i << " ";
	std::cout << std::endl;

	return 0;
}