#include <iostream>
#include <string>

struct X
{
	X() { std::cout << "X()" << std::endl; }
	X(const X&) { std::cout << "X(const X&)" << std::endl; }
	X& operator=(const X &rh)
	{
		std::cout << "X& operator=(const X &rh)" << std::endl;
		return *this;
	}
	~X() { std::cout << "~x()" << std::endl; }
};

void func1(X x)
{
	std::cout << "void func1(X x)" << std::endl;
}

void func2(X &x)
{
	std::cout << "void func2(X &x)" << std::endl;
}

int main()
{
	std::cout << "x1" << std::endl;
	X x1;
	func1(x1);
	std::cout << "main" << std::endl;
	func2(x1);
	std::cout << "main" << std::endl;
	X *x2 = new X();
	delete x2;
	std::cout << "delete x2" << std::endl;

	return 0;
}