#include <string>
#include <iostream>

using namespace std;

void replace_with_str(string &s, const string &oldVal, const string &newVal)
{
	// auto iter = s.begin();
	string::size_type index = 0;

	while(index != s.size())
	{
		if(oldVal == string(s, index, oldVal.size()))
		{
			s.replace(index, oldVal.size(), newVal);
		}
		++index;
	}
}

int main()
{
	string s("tho thru tho");

	replace_with_str(s, "tho", "though");
	cout << s << endl;

	replace_with_str(s, "thru", "through");
	cout << s << endl;

	return 0;
}