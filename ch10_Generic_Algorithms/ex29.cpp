#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ifstream ifs("../ch08_The_IO_Library/data");
	istream_iterator<string> str_istream_iter(ifs), eof;
	vector<string> v1(str_istream_iter, eof);
	ostream_iterator<string> cout_iter(cout, " ");
	copy(v1.begin(), v1.end(), cout_iter);
	cout << endl;

	return 0;
}