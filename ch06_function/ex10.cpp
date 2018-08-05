#include <iostream>

void swap_int(int *i,int *j)
{
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

int main()
{
	int i = 1,j = 2;

	std::cout << i << " " << j << std::endl;
	swap_int(&i,&j);
	std::cout << i << " " << j << std::endl;

	return 0;
}