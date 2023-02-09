#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,4,5,6,7,8};

	for(auto iter = v1.end(); iter != v1.begin(); )
		cout << *--iter << " ";
	cout << endl;

	return 0;
}