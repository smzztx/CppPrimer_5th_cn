#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 4) return -1;

	ifstream ifs(argv[1]);
	istream_iterator<int> int_istream_iter(ifs), eof;
	vector<int> v1(int_istream_iter, eof);
	
	ofstream ofs_odd("argv[2]");
	ostream_iterator<int> odd_iter(ofs_odd, "\n");
	copy_if(v1.begin(), v1.end(), odd_iter, [](int i){return i % 2; });
	ofs_odd.close();

	ofstream ofs_even("argv[3]");
	ostream_iterator<int> even_iter(ofs_even, "\n");
	copy_if(v1.begin(), v1.end(), even_iter, [](int i){return !(i % 2); });
	ofs_even.close();

	return 0;
}