#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<int> l1 = {1,2,3,4,5,6,7,8,0};

	// for(auto r_iter = l1.crbegin(); r_iter != l1.crend(); ++r_iter)
	// 	cout << *r_iter << " ";
	// cout << endl;

	auto r_iter = find(l1.crbegin(), l1.crend(), 0);
	// r_iter.base();
	cout << distance(r_iter, l1.crend()) << endl;
	// cout << l1.end() - l1.begin() << endl;

	return 0;
}