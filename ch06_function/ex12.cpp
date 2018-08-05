#include <iostream>

void swap_int(int &i,int &j)
{
	int tmp = i;
	i = j;
	j = tmp;
}
void print(std::vector<int>::iterator &begin, std::vector<int>::iterator &end)
{
        for (std::vector<int>::iterator iter = begin; iter != end; ++iter)
                std::cout << *iter << std::endl;
}
int main()
{
	int i = 1,j = 2;

	std::cout << i << " " << j << std::endl;
	swap_int(i,j);
	std::cout << i << " " << j << std::endl;

	return 0;
}