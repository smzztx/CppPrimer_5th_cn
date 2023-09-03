#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	list<const char *> l1 = {"aaa","bbb","ccc"};
	vector<string> v1;

	v1.assign(l1.begin(),l1.end());

	for(auto s : v1)	cout << s << " ";
	cout << endl;

	return 0;
}