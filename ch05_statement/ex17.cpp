#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

bool function(vector<int> v1,vector<int> v2)
{
	for(decltype(v1.size()) i = 0,sz1 = v1.size(),sz2 = v2.size();i != sz1 && i != sz2;++i)
	{
		if(v1[i] != v2[i])
		{
			cout << "false" << endl;
			return false;
		}
	}
	cout << "true" << endl;
	return true;
}

int main()
{
	vector<int> v1{0,1,2,3,4,5,6,7,8,9};
	vector<int> v2{0,1,2,3};

	function(v1,v2);

	return 0;
}
