#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool check_size(string &s, string::size_type sz)
{
	return s.size() >= sz;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	cout << count_if(vs.begin(), vs.end(), bind(check_size, placeholders::_1, 6)) << endl;

	return 0;
}