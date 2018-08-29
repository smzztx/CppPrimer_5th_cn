#include <string>
#include <iostream>

using namespace std;

int main()
{
	string numbers{"123456789"};
	string alphabet{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	string str{"ab2c3d7R4E6"};

	for(string::size_type pos = 0; (pos = str.find_first_of(numbers, pos)) != string::npos; ++pos)
	{
		cout << "found number at index: " << pos
		<< " element is " << str[pos] << endl;
	}
	for(string::size_type pos = 0; (pos = str.find_first_of(alphabet, pos)) != string::npos; ++pos)
	{
		cout << "found alphabet at index: " << pos
		<< " element is " << str[pos] << endl;
	}

	for(string::size_type pos = 0; (pos = str.find_first_not_of(alphabet, pos)) != string::npos; ++pos)
	{
		cout << "found number at index: " << pos
		<< " element is " << str[pos] << endl;
	}
	for(string::size_type pos = 0; (pos = str.find_first_not_of(numbers, pos)) != string::npos; ++pos)
	{
		cout << "found alphabet at index: " << pos
		<< " element is " << str[pos] << endl;
	}

	return 0;
}