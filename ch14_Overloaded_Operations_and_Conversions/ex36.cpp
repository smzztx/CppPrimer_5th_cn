#include <string>
#include <iostream>
#include <vector>

using std::string;

class ReadString
{
public:
	ReadString(std::istream &i = std::cin) : is(i) {}
	string operator()()
	{
		std::string s;
		std::getline(is, s);
		return s;
	}
private:
	std::istream &is;
};

int main()
{
	std::vector<string> vs;
	string new_string;
	ReadString ReadObject;
	
	do{
		new_string = ReadObject();
		vs.push_back(new_string);
	}while(!new_string.empty());

	for(auto s : vs)
		std::cout << s << " ";
	std::cout << std::endl;

	return 0;
}