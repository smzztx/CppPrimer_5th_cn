#include <iostream>
#include <string>

template <typename T>
std::ostream &print(std::ostream &os, const T &t)
{
	os << t;
}

template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args&... rest)
{
	os << t << ", ";
	return print(os, rest...);
}

int main()
{
	int i = 1, *p = &i;
	double d = 0.1;
	std::string s = "abc";

	print(std::cout, i);
	std::cout << std::endl;
	print(std::cout, i, d);
	std::cout << std::endl;
	print(std::cout, i, d, s, p, "ccc");
	std::cout << std::endl;

	return 0;
}