#include <iostream>
#include <typeinfo>

class Base
{
	friend bool operator==(const Base&, const Base&);
public:
	Base() = default;
	Base(int i_) : i(i_) { }
protected:
	virtual bool equal(const Base&) const;
private:
	int i;
};

class Derived : public Base
{
public:
	Derived() = default;
	Derived(std::string s_, int i_) : s(s_), Base(i_) { }
protected:
	bool equal(const Base&) const;
private:
	std::string s;
};

bool operator==(const Base &lhs, const Base &rhs)
{
	return typeid(lhs) == typeid(rhs) && lhs.equal(rhs);
}

bool Base::equal(const Base &rhs) const
{
	return this->i == rhs.i;
}

bool Derived::equal(const Base &rhs) const
{
	auto r = dynamic_cast<const Derived&>(rhs);
	return (this->s == r.s) && this->Base::equal(rhs);
}

int main()
{
	Base *pb1 = new Derived();
	Base *pb2 = new Derived();
	Base *pb3 = new Derived("a", 1);
	Base *pb4 = new Base();

	std::cout << std::boolalpha << (*pb1 == *pb2) << std::endl;
	std::cout << std::boolalpha << (*pb1 == *pb3) << std::endl;
	std::cout << std::boolalpha << (*pb1 == *pb4) << std::endl;

	int arr[10];
	Derived d;

	std::cout << typeid(42).name() << ", "
			  << typeid(arr).name() << ", "
			  << typeid(d).name() << ", "
			  << typeid(std::string).name() << ", "
			  << typeid(pb1).name() << ", "
			  << typeid(*pb1).name() << ", "
			  << typeid(*pb3).name() << std::endl;

	return 0;
}