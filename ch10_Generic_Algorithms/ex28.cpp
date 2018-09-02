#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,4,5,6,7,8,9};
	list<int> l1,l2,l3 = {0};

	copy(v1.begin(),v1.end(),back_inserter(l1));
	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	copy(v1.begin(),v1.end(),front_inserter(l2));
	for(const auto i : l2)
		cout << i << " ";
	cout << endl;

	copy(v1.begin(),v1.end(),inserter(l3,l3.end()));
	for(const auto i : l3)
		cout << i << " ";
	cout << endl;

	return 0;
}