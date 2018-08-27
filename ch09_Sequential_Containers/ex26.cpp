#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };

	vector<int> v1(ia, end(ia));
	list<int> l1(ia, end(ia));

	for(auto iter = l1.begin(); iter != l1.end(); )
	{		
		if(*iter % 2) iter = l1.erase(iter);
		else ++iter;
	}

	for(auto iter = v1.begin(); iter != v1.end(); )
	{	
			if(*iter % 2 == 0) iter = v1.erase(iter);
			else ++iter;
	}

	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	for(const auto i : v1)
		cout << i << " ";
	cout << endl;

	// list<int> l2={1,2,3,4,5,6,7,8};
	// for(auto iter = l2.begin(); iter != l2.end(); ++iter)
	// {
	// 	if(*iter % 2) l2.erase(iter);
	// }

	return 0;
}