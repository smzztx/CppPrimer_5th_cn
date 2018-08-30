#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,1,1};

	cout << accumulate(v1.cbegin(), v1.cend(), 0) << endl;

	return 0;
}