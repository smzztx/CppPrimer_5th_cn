#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	char c1[5] = "aaaa";
	char c2[5] = "bbbb";
	char c3[5] = "cccc";
	list<char *> l1 = { c1,c2,c3 };
	vector<string> v1;

	v1.assign(l1.begin(),l1.end());

	for(auto s : v1)	cout << s << " ";
	cout << endl;

	return 0;
}