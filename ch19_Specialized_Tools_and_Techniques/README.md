## 19.1
```cpp
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>
#include <algorithm>
#include <iostream>

void *operator new(size_t size)
{
	std::cout << "void *operator new(size_t size)" << std::endl;
	if(void *mem = malloc(size))
		return mem;
	else
		throw std::bad_alloc();
}

void operator delete(void *mem) noexcept
{
	std::cout << "void operator delete(void *mem) noexcept" << std::endl;
	free(mem);
}

class StrVec
{
friend bool operator==(StrVec &lhs, StrVec &rhs);
friend bool operator!=(StrVec &lhs, StrVec &rhs);
friend bool operator<(StrVec &lhs, StrVec &rhs);
friend bool operator>(StrVec &lhs, StrVec &rhs);
friend bool operator<=(StrVec &lhs, StrVec &rhs);
friend bool operator>=(StrVec &lhs, StrVec &rhs);
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec&);
	StrVec(StrVec &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free)), cap(std::move(s.cap)) { s.elements = s.first_free = s.cap = nullptr; }
	template <typename... Args>
	void emplace_back(Args&&... args);
	StrVec &operator=(const StrVec&);
	StrVec &operator=(StrVec&&) noexcept;
	std::string& operator[](std::size_t n) { return elements[n]; }
	const std::string& operator[](std::size_t n) const { return elements[n]; }
	~StrVec();
	void push_back(const std::string&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	std::string *begin() const { return elements; }
	std::string *end() const { return first_free; }
	void reserve(size_t n);
	void resize(size_t n);
	void resize(size_t n, const std::string &s);
private:
	std::allocator<std::string> alloc;
	void chk_n_alloc() { if(size() == capacity()) reallocate(); }
	std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
	void free();
	void reallocate();
	std::string *elements;
	std::string *first_free;
	std::string *cap;
};

StrVec::StrVec(std::initializer_list<std::string> il)
{
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template <typename... Args>
inline void StrVec::emplace_back(Args&&... args)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::forward<Args>(args)...);
}

void StrVec::push_back(const std::string &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

std::pair<std::string*,std::string*> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
	auto data = alloc.allocate(e-b);
	return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
	if(elements)
	{
		std::for_each(elements, first_free, [this](std::string &p){ alloc.destroy(&p); });
		// for(auto p = first_free; p != elements; )
		// 	alloc.destroy(--p);
		alloc.deallocate(elements, cap-elements);
	}
}

StrVec::StrVec(const StrVec &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
	free();
}

void StrVec::reserve(size_t n)
{
	if(n > capacity()) return;
	auto newdata = alloc.allocate(n);
	auto dest = newdata;
	auto elem = elements;
	for(size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + n;
}

void StrVec::resize(size_t n)
{
	resize(n,std::string());
}

void StrVec::resize(size_t n, const std::string &s)
{
	if(n < size())
	{
		while(n < size())
			alloc.destroy(--first_free);
	}else if(n > size())
	{
		while(n > size())
			push_back(s);
			// alloc.construct(first_free, s);
	}
}

StrVec &StrVec::operator=(const StrVec &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
{
	if(this != &rhs)
	{
		free();
		alloc = std::move(rhs.alloc);
		elements = std::move(rhs.elements);
		first_free = std::move(rhs.first_free);
		cap = std::move(rhs.cap);
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

void StrVec::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for(size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

bool operator==(StrVec &lhs, StrVec &rhs)
{
	return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(StrVec &lhs, StrVec &rhs)
{
	return !(lhs == rhs);
}

bool operator<(StrVec &lhs, StrVec &rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator>(StrVec &lhs, StrVec &rhs)
{
	return rhs < lhs;
}

bool operator<=(StrVec &lhs, StrVec &rhs)
{
	return !(rhs < lhs);
}

bool operator>=(StrVec &lhs, StrVec &rhs)
{
	return !(lhs < rhs);
}

#endif
```
  
## 19.3
（a）成功；  
（b）失败，pb是指向B的指针，不能转换为指向C的指针；  
（c）失败，A *pa = new D具有二义性。  
  
## 19.4
```cpp
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
```
  
## 19.5
我们想使用基类对象的指针或引用执行某个派生类操作并且该操作不是虚函数，则可以使用RTTI运算符（该类类型应该含有虚函数）。  
  
## 19.6
Query_base为抽象虚类，AndQuery的构造函数为private，暂时没想到方法来实现该题，目前使用19.3的继承体系来验证。  
```cpp
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
```
  
## 19.7
详见１9.6。  
  
## 19.8
详见１9.6。  
  
## 19.9
```cpp
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
```
```sh
$ ./ex09 true
false
false
i, A10_i, 7Derived, Ss, P4Base, 7Derived, 7Derived
```
  
## 19.10
（a）P1A；  
（b）P1A；  
（c）1B。  
```cpp
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
```
  
## 19.11
普通的数据指针指向一个对象；类成员指针指向类的非静态成员。当初始化这样一个指针时，我们令其指向类的某个成员，但是不指定该成员所属的对象；直到使用成员指针时，才提供所属的对象。  
  
## 19.12
```cpp
#include <string>
#include <iostream>

class Screen {
    public:
        using pos = std::string::size_type;

        static const std::string Screen::*data() { return &Screen::contents; }
        static const pos Screen::*pcursor() { return &Screen::cursor; }
        Screen() = default;
        Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

        char get() const { return contents[cursor]; }
        char get(pos r, pos c) const { return contents[r*width+c]; }

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};

int main()
{
    // const std::string Screen::*pdata;
    // pdata = &Screen::contents;
    // auto pdata = &Screen::contents;  //contents is private

    const std::string Screen::*pdata = Screen::data();
    Screen myScreen(2, 2, 'c');
    auto s = myScreen.*pdata;
    std::cout << s << std::endl;

    const std::string::size_type Screen::*pcursor = Screen::pcursor();
    auto i = myScreen.*pcursor;
    std::cout << i << std::endl;

    return 0;
}
```
  
## 19.13
```cpp
const std::string Sales_data::*pdata;
```
  
## 19.14
不合法，Screen中get_cursor函数返回的为pos类型，get函数返回的为char类型。  
  
## 19.15
和普通函数指针不同的是，在成员函数和指向该成员的指针之间不存在自动转换规则。  
  
## 19.16
```cpp
using AvgPrice = double (Sales_data::*)() const;
AvgPrice avgprice = &Sales_data::avg_price;
```
  
## 19.17
```cpp
#include <string>
#include <iostream>

class Screen {
    public:
        using pos = std::string::size_type;

        static const std::string Screen::*data() { return &Screen::contents; }
        static const pos Screen::*pcursor() { return &Screen::cursor; }
        Screen() = default;
        Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

        char get() const { return contents[cursor]; }
        char get(pos r, pos c) const { return contents[r*width+c]; }

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};

int main()
{
    Screen myScreen(2, 2, 'c');
    char (Screen::*pmf2)(Screen::pos, Screen::pos) const;
    pmf2 = &Screen::get;
    // char c1 = (myScreen.*pmf2)();
    char c2 = (myScreen.*pmf2)(0, 0);
    std::cout << c2 << std::endl;

    using Get1 = char (Screen::*)() const;
    using Get2 = char (Screen::*)(Screen::pos, Screen::pos) const;
    Get1 get1 = &Screen::get;
    Get2 get2 = &Screen::get;
    std::cout << (myScreen.*get1)() << std::endl;
    std::cout << (myScreen.*get2)(0, 0) << std::endl;

    return 0;
}
```
  
## 19.18
