#include <string>
#include <list>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
	list<int> list1 = {1,2,3,4,5,6};
	deque<int> deque_odd, deque_even;

	for(const auto i : list1)
		(i % 2 == 0) ? deque_even.push_back(i) : deque_odd.push_back(i);
		//(i & 0x1 ? deque_odd : deque_even).push_back(i);

	for(const auto i : deque_even)
		cout << i << " ";
	cout << endl;

	for(const auto i : deque_odd)
		cout << i << " ";
	cout << endl;
	
	return 0;
}