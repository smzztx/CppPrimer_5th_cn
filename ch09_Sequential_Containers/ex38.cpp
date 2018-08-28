#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string> v;

	for (string buffer; cin >> buffer; v.push_back(buffer))
		cout << v.size() << " " << v.capacity() << endl;

	return 0;
}