#include <iostream>

using namespace std;

int main()
{
	auto add_int = [](int x, int y){return x + y;};
	cout << add_int(1, 2) << endl;
	
	return 0;
}