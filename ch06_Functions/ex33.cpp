#include <iostream>
#include <vector>

void read_vi(std::vector<int>::const_iterator iterator_begin, std::vector<int>::const_iterator iterator_end)
{
	if(iterator_begin != iterator_end)
	{
		std::cout << *iterator_begin << " ";
		return read_vi(++iterator_begin, iterator_end);
	}else
	{
		std::cout << std::endl;
		return;
	}
}

int main()
{
	std::vector<int> v{1,2,3,4,5};

	read_vi(v.begin(), v.end());

	return 0;
}