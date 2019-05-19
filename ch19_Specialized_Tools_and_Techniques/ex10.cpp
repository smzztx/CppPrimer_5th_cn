#include <typeinfo>
#include <iostream>

class A
{
public:
	virtual ~A() {}
};

class B : public A
{};

class C : public B
{};

int main(int argc, char const *argv[])
{
	// A *pa = new C;
	// std::cout << typeid(pa).name() << std::endl;

	// C cobj;
	// A &ra = cobj;
	// std::cout << typeid(&ra).name() << std::endl;

	B *px = new B;
	A &ra = *px;
	std::cout << typeid(ra).name() << std::endl;

	return 0;
}