#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
	vector<int> v1(10, 1);
	fill_n(v1.begin(), v1.size(), 0);
	for(const auto i : v1)
		cout << i << " ";
	cout << endl;

	vector<int> v2;
	fill_n(back_inserter(v2), 10, 0);
	for(const auto i : v2)
		cout << i << " ";
	cout << endl;

	return 0;
}