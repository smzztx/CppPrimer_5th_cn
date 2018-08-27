#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// vector<int> v1 = {1};
	vector<int> v1;

	cout << v1.at(0) << endl;		//terminate called after throwing an instance of 'std::out_of_range'   what():  vector::_M_range_check
	cout << v1[0] << endl;			//Segmentation fault (core dumped)
	cout << v1.front() << endl;		//Segmentation fault (core dumped)
	cout << *v1.begin() << endl;	//Segmentation fault (core dumped)

	return 0;
}