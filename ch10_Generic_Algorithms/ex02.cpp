#include <list>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	list<string> l1 = {"a", "b", "c", "a", "aa"};

	cout << count(l1.cbegin(), l1.cend(), "a") << endl;

	return 0;
}