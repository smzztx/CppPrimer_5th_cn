#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class equal_int
{
public:
	equal_int(int i) : default_number(i) {}
	bool operator()(int ele) { return default_number == ele; }
private:
	int default_number;
};

int main()
{
	std::vector<int> vi = {1,2,3,3,4,3,5};

	std::replace_if(vi.begin(), vi.end(), equal_int(3), 5);

	for(int i : vi)
		std::cout << i << " ";
	std::cout << std::endl;

	return 0;
}