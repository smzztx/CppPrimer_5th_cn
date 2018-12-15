#include <string>
#include <iostream>

using std::string;

class ReadString
{
public:
	ReadString(std::istream &i = std::cin) : is(i) {}
	const string &operator()()
	{
		is >> s;
		return s;
	}
private:
	std::istream &is;
	string s;
};

int main()
{
	ReadString ReadObject;
	std::cout << ReadObject() << std::endl;

	return 0;
}