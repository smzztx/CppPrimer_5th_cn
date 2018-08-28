#include <forward_list>
#include <iostream>

using namespace std;

int main()
{
	forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};
	auto iter = flst.begin();
	auto prev = flst.before_begin();

	while(iter != flst.end())
	{
		if(*iter % 2)
		{
			iter = flst.insert_after(iter, *iter);
			prev = iter;
			++iter;
		}else
		{
			iter = flst.erase_after(prev);
		}
	}

	for(const auto i : flst)
		cout << i << " ";
	cout << endl;

	return 0;
}