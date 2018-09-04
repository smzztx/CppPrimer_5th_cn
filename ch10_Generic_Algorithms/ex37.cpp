#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,4,5,6,7,8,9,0};
	list<int> l1(v1.crbegin()+2,v1.crbegin()+7);

	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	return 0;
}