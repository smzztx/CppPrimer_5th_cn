#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	string s,pres,max_string;
	unsigned int cnt = 1,max_cnt = 1;

	while(cin >> s)
	{
		if(s == pres)
		{
			++cnt;
		}else
		{
			if(cnt > max_cnt)
			{
				max_cnt = cnt;
				max_string = pres;
			}
			cnt = 1;
		}
		pres = s;
	}
	if(cnt > max_cnt)
	{
		max_cnt = cnt;
		max_string = pres;
	}
	(max_cnt > 1) ? (cout << max_string << ":" << max_cnt << endl) : (cout << "no repeat" << endl);
	return 0;
}