#include <iostream>
#include <memory>
#include <sstream>

template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);
std::string debug_rep(const std::string &s);

template <typename T>
std::string debug_rep(const T &t)
{
	std::ostringstream ret;
	ret << t;
	return ret.str();
}

template <typename T>
std::string debug_rep(T *p)
{
	std::ostringstream ret;
	ret << "pointer: " << p;

	if(p)
		ret << " " << debug_rep(*p);
	else
		ret << " null pointer";
	return ret.str();
}

std::string debug_rep(const std::string &s)
{
	return '"' + s + '"';
}

template <>
std::string debug_rep(char *p)
{
	return debug_rep(std::string(p));
}

template <>
std::string debug_rep(const char *p)
{
	std::cout << "debug_rep(const char *p)" << std::endl;
	return debug_rep(std::string(p));
}

int main()
{
	char ca[] = {'a', 'b', 'c', '\0'};
	std::cout << debug_rep(ca) << std::endl;

	return 0;
}