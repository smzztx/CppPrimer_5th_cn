#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

// int (*function)(int, int);

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main()
{
	vector<int (*)(int, int)> vf{add, subtract, multiply, divide};

	for(const auto &e : vf) cout << e(4, 2) << endl;

	return 0;
}