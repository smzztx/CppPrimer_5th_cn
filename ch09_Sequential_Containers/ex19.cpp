#include <string>
#include <list>
#include <iostream>

using namespace std;

int main()
{
	string s;
	list<string> list1;

	while(cin >> s)
		list1.push_back(s);

	for(auto iter = list1.cbegin(); iter != list1.cend(); ++iter)
		cout << *iter << " ";
	cout << endl;
	
	return 0;
}