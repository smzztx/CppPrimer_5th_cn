#include <string>
#include <vector>
#include <iostream>

template <typename T>
void print_vector(T &v)
{
	for(typename T::size_type i = 0; i != v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void print_vector2(T &v)
{
	for(typename T::iterator iter = v.begin(); iter != v.end(); ++iter)
		std::cout << *iter << " ";
	std::cout << std::endl;
}

int main()
{
	std::vector<std::string> vs = {"a", "bb", "ccc"};
	print_vector(vs);

	std::vector<int> vi = {1, 2, 3};
	print_vector(vi);

	print_vector2(vs);
	print_vector2(vi);

	return 0;
}