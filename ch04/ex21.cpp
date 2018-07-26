#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
	vector<int> iv{1,2,3};

	for(auto &i:iv)
		i = (i % 2) ? (i * 2):i;

	for(const auto &i:iv) 
		cout << i << " ";
	cout << endl;
}
