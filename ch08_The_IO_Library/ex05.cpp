#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	ifstream ifs("data");
	vector<char> v1;
	char buf;

	if(ifs)
	{
		while(ifs >> buf)
		{
			v1.push_back(buf);
		}
	}


	for(const auto &c : v1)
		cout << c << endl;

	return 0;
}