#ifndef FOO_H_
#define FOO_H_

#include <algorithm>
#include <iostream>

class Foo
{
public:
	Foo sorted() &&;
	Foo sorted() const &;
private:
	std::vector<int> data;
};

Foo Foo::sorted() &&
{
	std::cout << "Foo Foo::sorted() &&" << std::endl;
	sort(data.begin(), data.end());
	return *this;
}

Foo Foo::sorted() const &
{
	std::cout << "Foo Foo::sorted() const &" << std::endl;
	
	// Foo ret(*this);
	// sort(ret.data.begin(), ret.data.end());
	// return ret;

	//56
	// Foo ret(*this);
	// return ret.sorted();

	//57
	return Foo(*this).sorted();
}

#endif