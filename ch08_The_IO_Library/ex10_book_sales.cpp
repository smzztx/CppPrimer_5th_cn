#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<string> v1;
	ifstream is("book_sales");
	string buf;

	if(!is)
	{
		cerr << "open error" << endl;
		return -1;
	}

	while(getline(is, buf))
		v1.push_back(buf);

	for(const auto &s : v1)
	{
		// cout << s << endl;
		istringstream iss(s);
		while(iss >> buf)
			cout << buf << endl;
	}

	return 0;
}