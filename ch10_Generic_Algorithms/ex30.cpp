#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	istream_iterator<int> int_cin(cin), eof;
	vector<int> v1(int_cin, eof);
	sort(v1.begin(), v1.end());
	ostream_iterator<int> cout_iter(cout, " ");
	copy(v1.begin(), v1.end(), cout_iter);
	cout << endl;

	return 0;
}