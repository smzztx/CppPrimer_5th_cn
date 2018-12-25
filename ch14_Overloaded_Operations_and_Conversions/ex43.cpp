#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<int> vi = {2, 3, 4, 5, 6};
	int input = 0;
	std::cin >> input;

	std::modulus<int> mod;
	// auto predicator = [&](int i){ return 0 == mod(input, i); };
	auto is_divisible = std::all_of(vi.begin(), vi.end(), [&](int i){ return 0 == mod(input, i); });

	std::cout << (is_divisible ? "yes" : "no") << std::endl;

	return 0;
}