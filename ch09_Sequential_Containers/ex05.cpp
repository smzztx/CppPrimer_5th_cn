#include <iostream>
#include <vector>

using namespace std;

vector<int>::const_iterator find_int(vector<int>::const_iterator begin_, vector<int>::const_iterator end_, int n)
{
	while(begin_ != end_)
	{
		if( *begin_ == n) return begin_;
		++begin_;
	}

	return begin_;
}

int main()
{
	vector<int> vi{1,2,3,4,5,6};

	find_int(vi.begin(), vi.end(), 0);

	return 0;
}