#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../ch07_Classes/Sales_data_ex26.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	vector<string> v1;

	ifstream is("../ch08_The_IO_Library/book_sales");
	string buf;

	if(!is)
	{
		cerr << "open error" << endl;
		return -1;
	}

	while(getline(is, buf))
		v1.push_back(buf);

	vector<Sales_data> v2;
	for(const auto &s : v1)
	{
		// cout << s << endl;
		istringstream iss(s);
		v2.push_back(Sales_data(iss));
	}

	stable_sort(v2.begin(), v2.end(), []
		(const Sales_data &sales_data1, const Sales_data &sales_data2)
			{ return sales_data1.isbn() < sales_data2.isbn(); });

	for(const auto s : v2)
		cout << s.isbn() << endl;

	return 0;
}