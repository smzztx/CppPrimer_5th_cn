#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	string repeat_s,pre_s,s;
	while(cin >> s)
	{
		if(!isupper(s[0])) continue;
		if(s == pre_s)
		{
			repeat_s = s;
			cout << repeat_s << endl;
			break;
		}
		pre_s = s;
	}
	if(repeat_s.empty())
	{
		cout << "no repeat" << endl;
	}

	return 0;
}