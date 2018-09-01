#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool check_size(string &s, int sz)
{
	return s.size() < sz;
}

int main()
{
	vector<int> vi = {1,2,3,4,5,6};
	string s("aaaa");

	auto iter = find_if(vi.begin(), vi.end(), bind(check_size, s, placeholders::_1));

	cout << *iter << endl;

	return 0;
}