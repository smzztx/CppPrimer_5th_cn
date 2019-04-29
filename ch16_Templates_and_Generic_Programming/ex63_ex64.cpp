#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
size_t get_number(T t, std::vector<T> const &vt)
{
	size_t n = 0;
	auto iter = vt.begin();

	do{
		iter = std::find(iter, vt.end(), t);
		if(iter != vt.end())
		{
			++n;
			++iter;
		}
	}while(iter != vt.end());
	return n;
}

size_t get_number(const char* p, const std::vector<std::string> &vt)
{
	size_t n = 0;
	auto iter = vt.begin();
	std::string s(p);

	do{
		iter = std::find(iter, vt.end(), s);
		if(iter != vt.end())
		{
			++n;
			++iter;
		}
	}while(iter != vt.end());
	return n;
}

template <>
size_t get_number(const char* t, std::vector<const char*> const &vt)
{
	size_t n = 0;
	auto iter = vt.begin();

	do{
		iter = std::find(iter, vt.end(), t);
		if(iter != vt.end())
		{
			++n;
			++iter;
		}
	}while(iter != vt.end());
	return n;
}

int main()
{
	std::vector<double> vd = {1, 2, 3, 3.14, 4, 3.14, 5, 6.28};
	std::vector<int> vi = {1, 2, 3, 3, 4, 3, 5, 6};
	std::vector<std::string> vs = {"a", "bb", "ccc", "dddd"};
	std::vector<const char*> vcp = {"a", "bb", "ccc", "dddd"};

	std::cout << get_number(3.14, vd) << std::endl;
	std::cout << get_number(3, vi) << std::endl;
	std::cout << get_number("a", vs) << std::endl;
	std::cout << get_number("a", vcp) << std::endl;

	return 0;
}