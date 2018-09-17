#include <string>
#include <iostream>
#include <vector>
#include <memory>

std::shared_ptr<std::vector<int>> create_vi()
{
	return std::make_shared<std::vector<int>>();
}

void push_vi(std::shared_ptr<std::vector<int>> p)
{
	int i;
	while(std::cin >> i)
		p->push_back(i);
}

void print_vi(std::shared_ptr<std::vector<int>> p)
{
	for(const auto i : (*p))
		std::cout << i << std::endl;
}

int main()
{
	auto p = create_vi();
	push_vi(p);
	print_vi(p);
	// delete p;

	return 0;
}