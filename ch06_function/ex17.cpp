#include <iostream>
#include <string>

bool is_upper(const std::string &s)
{
	for(auto c : s)
	{
		if(isupper(c)) return true;
	}
	return false;
}

void to_upper(std::string &s)
{
	for(auto &c : s) c = tolower(c);
}

int main(int argc, char const *argv[])
{
	std::string s("abcdABCD");

	std::cout << (is_upper(s) ? "is upper" : "is not upper") << std::endl;
	std::cout << s << std::endl;
	to_upper(s);
	std::cout << s << std::endl;

	return 0;
}