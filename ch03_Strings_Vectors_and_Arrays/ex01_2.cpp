#include <iostream>

using std::cout;
using std::endl;

int main()
{
	int i = 10 ,sum = 0;

	while(i >= 0)
	{
		sum += i;
		--i;
	}
	cout << sum << endl;

	return 0;
}