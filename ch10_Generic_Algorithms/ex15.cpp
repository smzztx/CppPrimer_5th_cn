#include <iostream>

using namespace std;

int main()
{
	int x = 1;
	auto add_int = [x](int y){return x + y;};

	cout << add_int(2) << endl;
	
	return 0;
}