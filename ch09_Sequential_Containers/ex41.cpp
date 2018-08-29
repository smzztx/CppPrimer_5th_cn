#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<char> vc = {'a','b','c'};
	string s(vc.begin(), vc.end());

	cout << s << endl;

	return 0;
}