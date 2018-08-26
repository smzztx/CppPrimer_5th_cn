#include <string>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
	string s;
	deque<string> deque1;

	while(cin >> s)
		deque1.push_back(s);

	for(auto iter = deque1.cbegin(); iter != deque1.cend(); ++iter)
		cout << *iter << " ";
	cout << endl;

	return 0;
}