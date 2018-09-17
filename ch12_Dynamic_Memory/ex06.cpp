#include <string>
#include <iostream>
#include <vector>
#include <initializer_list>

std::vector<int> *create_vi()
{
	return new std::vector<int>;
}

void push_vi(std::vector<int> *p)
{
	int i;
	while(std::cin >> i)
		p->push_back(i);
}

void print_vi(std::vector<int> *p)
{
	for(const auto i : (*p))
		std::cout << i << std::endl;
}

int main()
{
	auto p = create_vi();
	push_vi(p);
	print_vi(p);
	delete p;

	return 0;
}