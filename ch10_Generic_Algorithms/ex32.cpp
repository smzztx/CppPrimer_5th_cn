#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include "../ch01_Getting_Started/Sales_item.h"

using namespace std;

int main()
{
	istream_iterator<Sales_item> int_cin(cin), eof;
	vector<Sales_item> v1(int_cin, eof);
	sort(v1.begin(), v1.end(), compareIsbn);
	// for(const auto s : v1)
	// 	cout << s.isbn() << endl;
	cout << endl;
	for(auto beg = v1.cbegin(), end = beg; beg != v1.cend(); beg = end)
	{
		end = find_if(beg, v1.cend(), [beg](const Sales_item &sale_item){ return sale_item.isbn() != beg->isbn(); });
		cout << accumulate(beg, end, Sales_item(beg->isbn())) << endl;
	}

	return 0;
}