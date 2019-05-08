#include <bitset>
#include <vector>
#include <iostream>

int main()
{
	std::vector<int> vi = {1, 2, 3, 5, 8, 13, 21};
	std::bitset<32> bset;
	for(auto const i : vi)
	{
		bset.set(i);
	}
	std::cout << bset << std::endl;

	return 0;
}