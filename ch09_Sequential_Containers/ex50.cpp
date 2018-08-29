#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<string> v1(10, "5");
	int sum_int = 0;
	for(const auto s : v1)
		sum_int += stoi(s);
	cout << sum_int << endl;

	vector<string> v2(10, "3.14");
	double sum_double = 0;
	for(const auto s : v2)
		sum_double += stod(s);
	cout << sum_double << endl;

	return 0;
}