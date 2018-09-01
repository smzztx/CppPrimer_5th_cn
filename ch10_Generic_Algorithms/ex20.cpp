#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};
	string::size_type sz = 6;

	cout << count_if(vs.begin(), vs.end(),
		[sz](const string &s)
			{ return s.size() >=sz; }) << endl;

	return 0;
}