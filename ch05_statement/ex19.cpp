#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	do
	{
		string s1,s2;
		cin >> s1 >> s2;
		(s1.size() < s2.size()) ? (cout << s1 << endl) : (cout << s2 << endl);
	}while(cin);

	return 0;
}