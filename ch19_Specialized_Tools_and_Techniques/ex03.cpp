#include <typeinfo>

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

	// B *pb = new B;
	// C *pc = dynamic_cast<C*>(pb);

	// A *pa = new D;
	// B *pb = dynamic_cast<B*>(pa);

	A *pa = new A;
	try{
		const C &c = dynamic_cast<const C&>(*pa);
	}catch(std::bad_cast){
		//...
	}

	return 0;
}