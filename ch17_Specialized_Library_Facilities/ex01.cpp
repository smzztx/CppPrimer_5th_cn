#include <iostream>
#include <tuple>
#include <vector>

int main()
{
	std::tuple<int, int, int> threeI(10, 20, 30);
	std::tuple<std::string, std::vector<std::string>, std::pair<std::string, int>> someVal("constants", {"a", "bb"}, {"ccc", 3});

	return 0;
}