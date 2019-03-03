#include <iostream>
#include <string>

template<typename T>
void print(const T &arr)
{
	for(auto elem : arr)
		std::cout << elem << std::endl;
}

int main()
{
	char ac[] = "aabbccdd";
	int ai[] = {1, 2, 3, 4};

	print(ac);
	print(ai);

	return 0;
}