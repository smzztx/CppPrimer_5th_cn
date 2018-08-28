#include <list>
#include <iostream>

using namespace std;

int main()
{
	list<int> l1 = {0,1,2,3,4,5,6,7,8,9};
	auto iter = l1.begin();

	while(iter != l1.end())
	{
		if(*iter % 2)
		{
			iter = l1.insert(iter, *iter);
			++iter;
			++iter;
		}else
		{
			iter = l1.erase(iter);
		}
	}

	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	return 0;
}