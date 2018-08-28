#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> v1 = {0,1,2,3,4,5,6,7,8,9,10};
	auto iter = v1.begin();

	while(iter != v1.end())
	{
		if(*iter % 2)
			iter = v1.insert(iter, *iter);
		++iter;
	}

	for(const auto i : v1)
		cout << i << " ";
	cout << endl;

	return 0;
}