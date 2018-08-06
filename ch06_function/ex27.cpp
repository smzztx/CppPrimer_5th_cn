#include <iostream>
#include <initializer_list>

int counter_int(std::initializer_list<int> il)
{
	int cnt_i = 0;
	for(auto e : il)
		cnt_i += e;
	return cnt_i;
}

int main(int argc, char const *argv[])
{
	std::cout << counter_int({1,2,3,4,5}) << std::endl;

	return 0;
}