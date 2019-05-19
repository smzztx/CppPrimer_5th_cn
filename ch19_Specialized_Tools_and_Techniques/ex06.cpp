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
	A *pa1 = new C;
    if(C *qc = dynamic_cast<C*>(pa1))
    {
        std::cout << "success" << std::endl;
    }else
    {
        std::cout << "fail" << std::endl;
    }

	A *pa2 = new C;
	try{
		const C &rc = dynamic_cast<const C&>(*pa2);
	}catch(std::bad_cast &e){
		std::cout << e.what() << std::endl;
	}

	C c = C();
	if(typeid(*pa1) == typeid(*pa2)) std::cout << "same type" << std::endl;
	if(typeid(*pa1) == typeid(c)) std::cout << "same type as C" << std::endl;
	if(typeid(*pa1) == typeid(C)) std::cout << "same type as C" << std::endl;

	return 0;
}