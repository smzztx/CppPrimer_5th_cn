#include <string>
#include <iostream>

using std::string;

struct if_then_else
{
	const string &operator()(bool b, const string &first_result, const string &second_result)
	{
		return b ? first_result : second_result;
	}
};

int main()
{
	if_then_else if_object;
	std::cout << if_object(true, "aaa", "bbb") << std::endl;

	return 0;
}