#include <iostream>

int compare(int j, int *i)
{
	return j > *i ? j : *i; 
}

int main()
{
	int j = 0, i = 1;
	
	std::cout << compare(j, &i) << std::endl;

	return 0;
}