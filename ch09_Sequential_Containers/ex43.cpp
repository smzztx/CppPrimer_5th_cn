#include <string>
#include <iostream>

using namespace std;

void replace_with_str(string &s, const string &oldVal, const string &newVal)
{
	auto iter = s.begin();

	while(iter != s.end())
	{
		if(oldVal == string(iter, iter+oldVal.size()))
		{
			iter = s.erase(iter, iter+oldVal.size());
			iter = s.insert(iter, newVal.begin(), newVal.end());
			iter += newVal.size();
		}else
			++iter;
	}
}

int main()
{
	string s("tho thru");

	replace_with_str(s, "tho", "though");
	cout << s << endl;

	replace_with_str(s, "thru", "through");
	cout << s << endl;

	return 0;
}