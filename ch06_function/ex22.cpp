#include <iostream>

void swap_intp(int *&i, int *&j)
{
	int *tmp;
	tmp = i;
	i = j;
	j = tmp;
}

int main()
{
	int i = 0, j = 1;
	int *pi = &i, *pj = &j;

	std::cout << pi << " " << pj << std::endl;
	swap_intp(pi, pj);
	std::cout << pi << " " << pj << std::endl;

	return 0;
}