#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,1,1,2,3,4,5};
	list<int> l1;

	unique_copy(v1.begin(),v1.end(),back_inserter(l1));

	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	return 0;
}