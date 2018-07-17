#include <iostream>
#include <stdexcept>

using namespace std;
int __global;

int main()
{
	cout<<"helloworld"<<endl;
	// int i = {3.14};
	// int i(3.14);
	// int i{3.14};
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
	// const int &ri = dval;
	// cout << ri << endl;
	// dval = 4;
	// cout << ri << endl;
	// int *const p;
	// const int *p;
	// constexpr int mf = 20;
	int *const p = &dval;
	// constexpr int *p = &dval;
	// p = &dval;
	static int j = 0;
	constexpr int *p1 = &j;
	auto i = j;
	// constexpr int *p2 = &i;
	int *p3 = nullptr;
	return 0;
}
