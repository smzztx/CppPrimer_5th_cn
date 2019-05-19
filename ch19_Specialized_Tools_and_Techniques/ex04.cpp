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

class D : public B, public A
{};

int main(int argc, char const *argv[])
{
	// A *pa = new C;
	// B *pb = dynamic_cast<B*>(pa);
	// if(pb) std::cout << "success" << std::endl;
	// else std::cout << "fail" << std::endl;

	// B *pb = new B;
	// C *pc = dynamic_cast<C*>(pb);
	// if(pc) std::cout << "success" << std::endl;
	// else std::cout << "fail" << std::endl;

	// A *pa = new D;
	// B *pb = dynamic_cast<B*>(pa);
	// if(pb) std::cout << "success" << std::endl;
	// else std::cout << "fail" << std::endl;

	A *pa = new C;
	try{
		const C &c = dynamic_cast<const C&>(*pa);
	}catch(std::bad_cast &e){
		std::cout << e.what() << std::endl;
	}

	return 0;
}