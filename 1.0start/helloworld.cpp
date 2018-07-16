#include <iostream>

using namespace std;
int __global;

int main()
{
	cout<<"helloworld"<<endl;
	// int i = {3.14};
	// int i(3.14);
	// int i{3};
	// cout << i <<endl;
	// int _;
	// int _local;
	// int local_int;
	// double Double;
	// cout << local_int << endl;
	// int i=100;
	// cout << &i <<endl;
	// int *p = NULL;
	// cout << p <<endl;
	// cout << *p <<endl;
	// cout << &p <<endl;
	int dval = 3;
	const int &ri = dval;
	cout << ri << endl;
	dval = 4;
	cout << ri << endl;
	// int *const p;
	const int *p;
	return 0;
}
