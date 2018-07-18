#include<iostream>
inline double square (double x){return x*x;}
using namespace std;
int main()
{
	double a,b;
	double c=13.0;
	a=square(5.0);
	b=square(4.5+7.5);
	cout<<a<<endl;
	cout<<b<<endl;
	cout<<c<<endl;
	return 0;
}


