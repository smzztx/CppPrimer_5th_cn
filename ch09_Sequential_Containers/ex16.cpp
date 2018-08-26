#include <vector>
#include <iostream>
#include <list>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3};
	list<int> l1 = {1,2,3};

	cout << boolalpha << (vector<int>(l1.begin(),l1.end()) == v1) << endl;

	return 0;
}