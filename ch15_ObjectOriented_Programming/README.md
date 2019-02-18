## 15.1
虚函数是基类希望其派生类进行覆盖的函数。
  
## 15.2
派生类的成员函数可以访问protected访问运算符的成员，而不能访问private的。
  
## 15.3
Quote_ex03.h
```cpp
#ifndef QUOTE_H_
#define QUOTE_H_

#include <string>

class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; } 
	virtual ~Quote() = default;
private:
	std::string bookNo;
protected:
	double price = 0;
};

#endif
```
  
ex03.cpp
```cpp
#include "Quote_ex03.h"
#include <iostream>
#include <functional>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	print_total(std::cout, q, 2);

	return 0;
}
```
  
## 15.04
（a）不正确，是定义，不是声明，而且不能继承它自己；  
（b）不正确，是定义，不是声明；  
（c）不正确，声明中包含类名，但是不包含它的派生列表。  
  
## 15.05
```cpp
#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Quote_ex03.h"
#include <string>

class Bulk_quote : public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc) { }
	double net_price(std::size_t) const override;
private:
	std::size_t min_qty = 0;
	double discount = 0.0;
};

double Bulk_quote::net_price(size_t cnt) const
{
	if(cnt >= min_qty) return cnt * (1 - discount) * price;
	else return cnt * price;
}

#endif
```
  
## 15.06
```cpp
#include "Quote_ex03.h"
#include "Bulk_quote_ex05.h"
#include <iostream>
#include <functional>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	Bulk_quote bq("A1-001", 80, 5, 0.2);
	print_total(std::cout, q, 10);
	print_total(std::cout, bq, 10);

	return 0;
}
```
  
## 15.07
Limit_quote_ex07.h
```cpp
#ifndef LIMIT_QUOTE_H_
#define LIMIT_QUOTE_H_

#include "Quote_ex03.h"
#include <string>

class Limit_quote : public Quote
{
public:
	Limit_quote() = default;
	Limit_quote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), max_qty(qty), discount(disc) { }
	double net_price(std::size_t) const override;
private:
	std::size_t max_qty = 0;
	double discount = 0.0;
};

double Limit_quote::net_price(size_t cnt) const
{
	if(cnt > max_qty) return max_qty * (1 - discount) * price + (cnt - max_qty)*price;
	else return cnt * price;
}

#endif
```
  
ex07.cpp
```cpp
#include "Quote_ex03.h"
#include "Limit_quote_ex07.h"
#include <iostream>
#include <functional>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	Limit_quote bq("A1-001", 80, 5, 0.2);
	print_total(std::cout, q, 10);
	print_total(std::cout, bq, 10);

	return 0;
}
```
  
## 15.08
表达式的静态类型在编译时总是已知的，它是变量声明时的类型或表达式生成的类型；  
动态类型则是变量或表达式表示的内存中的对象类型。动态类型直到运行时才可知。  
  
## 15.09
摘自github。
```cpp
    Bulk_quote bulk_quote("bulk_quote_1", 10.10, 10, 0.5);

    // The pointer is of static type Quote, but it's dynamic type is Bulk Quote
    // Because of polymorphism the Bulk Quote implementation of the net_price()
    // method gets called.
    Quote *quote_pointer = &bulk_quote;
    quote_pointer->net_price(5);

    // The reference is of static type Quote, but it's dynamic type is Bulk Quote
    // Like with the pointer, the Bulk Quote implementation of the net_price()
    // method gets called.
    Quote &quote_reference = bulk_quote;
    quote_reference.net_price(5);

    // The static type of this variable is Quote. Here the Bulk Quote object
    // gets upcasted. The Quote part of bulk_quote gets copied into quote, but
    // the rest is not handled. Because of the cast the Quote implementation of
    // the net_price() method gets called.
    Quote quote = bulk_quote;
    quote.net_price(5);
```
  
## 15.10
read中std::istream，std::ifstream是继承自std::istream，因此，std::istream的实例传入后会转换为std::istream。
  
## 15.11
Quote_ex11.h
```cpp
#ifndef QUOTE_H_
#define QUOTE_H_

#include <string>
#include <iostream>

class Quote
{
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual void debug() const;
	virtual ~Quote() = default;
private:
	std::string bookNo;
protected:
	double price = 0;
};

void Quote::debug() const
{
	std::cout << "bookNo: " << bookNo 
	<< "; price: " << price;
}

#endif
```
  
Bulk_quote_ex11.h
```cpp
#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Quote_ex11.h"
#include <string>
#include <iostream>

class Bulk_quote : public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), min_qty(qty), discount(disc) { }
	double net_price(std::size_t) const override;
	void debug() const override;
private:
	std::size_t min_qty = 0;
	double discount = 0.0;
};

double Bulk_quote::net_price(size_t cnt) const
{
	if(cnt >= min_qty) return cnt * (1 - discount) * price;
	else return cnt * price;
}

void Bulk_quote::debug() const
{
	Quote::debug();
	std::cout << "; min_qty: " << min_qty
	<< "; discount: " << discount;
}

#endif
```
  
ex11.cpp
```cpp
#include "Quote_ex11.h"
#include "Bulk_quote_ex11.h"
#include <iostream>
#include <functional>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	Bulk_quote bq("A1-001", 80, 5, 0.2);
	// print_total(std::cout, q, 10);
	// print_total(std::cout, bq, 10);

	q.debug();
	std::cout << std::endl;
	bq.debug();
	std::cout << std::endl;

	return 0;
}
```
  
## 15.12
有必要，如果该成员函数不希望被后续的派生类继承，则可声明成final，与当前的override没有关系。
  
## 15.13
派生类中的print函数会递归调用当前print，知道内存耗尽。  
```cpp
void print(ostream &os) { base::print(os); os << " " << i; }
```
  
## 15.14
（a）调用base中的print，编译时确定；  
（b）调用derived中的print，编译时确定；  
（c）调用base中的name函数，不是虚函数，没有动态绑定，所以编译时确定；  
（d）调用derived中的name函数，不是虚函数，没有动态绑定，所以编译时确定；  
（e）调用base中的print，运行时确定；  
（f）调用derived中的print，运行时确定。  
  
## 15.15
Disc_quote_ex15.h
```cpp
#ifndef DISC_QUOTE_
#define DISC_QUOTE_

#include "Quote_ex11.h"
#include <string>

class Disc_quote : public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const std::string &book, double price, std::size_t qty, double disc)
	: Quote(book, price), quantity(qty), discount(disc) { }
	double net_price(std::size_t) const = 0;
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};


#endif
```
  
Bulk_quote_ex15.h
```cpp
#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Disc_quote_ex15.h"
#include <string>
#include <iostream>

class Bulk_quote : public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }
	double net_price(std::size_t) const override;
	void debug() const override;
};

double Bulk_quote::net_price(size_t cnt) const
{
	if(cnt >= quantity) return cnt * (1 - discount) * price;
	else return cnt * price;
}

void Bulk_quote::debug() const
{
	Quote::debug();
	std::cout << "; quantity: " << quantity
	<< "; discount: " << discount;
}

#endif
```
  
ex15.cpp
```cpp
#include "Quote_ex11.h"
#include "Bulk_quote_ex15.h"
#include <iostream>
#include <functional>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	Bulk_quote bq("A1-001", 80, 5, 0.2);
	// print_total(std::cout, q, 10);
	// print_total(std::cout, bq, 10);

	q.debug();
	std::cout << std::endl;
	bq.debug();
	std::cout << std::endl;

	return 0;
}
```
  
## 15.16
Limit_quote_ex16.h
```cpp
#ifndef LIMIT_QUOTE_H_
#define LIMIT_QUOTE_H_

#include "Disc_quote_ex15.h"
#include <string>
#include <iostream>

class Limit_quote : public Disc_quote
{
public:
	Limit_quote() = default;
	Limit_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }
	double net_price(std::size_t) const override;
	void debug() const override;
};

double Limit_quote::net_price(size_t cnt) const
{
	if(cnt > quantity) return quantity * (1 - discount) * price + (cnt - quantity)*price;
	else return cnt * price;
}

void Limit_quote::debug() const
{
	Quote::debug();
	std::cout << "; quantity: " << quantity
	<< "; discount: " << discount;
}

#endif
```
  
ex16.cpp
```cpp
#include "Quote_ex11.h"
#include "Limit_quote_ex16.h"
#include <iostream>
#include <functional>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	Limit_quote bq("A1-001", 80, 5, 0.2);
	print_total(std::cout, q, 10);
	print_total(std::cout, bq, 10);

	// q.debug();
	// std::cout << std::endl;
	// bq.debug();
	// std::cout << std::endl;

	return 0;
}
```
  
## 15.17
```
$ g++ -o ex17 ex17.cpp -std=c++11
ex17.cpp: In function ‘int main()’:
ex17.cpp:17:13: error: cannot declare variable ‘dq’ to be of abstract type ‘Disc_quote’
  Disc_quote dq("A1-001", 80, 5, 0.2);
             ^
In file included from Limit_quote_ex16.h:4:0,
                 from ex17.cpp:2:
Disc_quote_ex15.h:7:7: note:   because the following virtual functions are pure within ‘Disc_quote’:
 class Disc_quote : public Quote
       ^
Disc_quote_ex15.h:13:9: note: 	virtual double Disc_quote::net_price(std::size_t) const
  double net_price(std::size_t) const = 0;
         ^
```
  
## 15.18
(a)合法；  
(b)非法；  
(c)非法；  
(d)合法；  
(d)非法；  
(f)非法。  
只有当D公有地继承B时，用户代码才能使用派生类向基类的转换。  
  
## 15.19
Base类：合法；  
Pub_Derv类：合法；  
Priv_Derv类：合法；  
Prot_Derv类：合法；  
Derived_from_Public类：合法；  
Derived_from_Private类：非法；  
Derived_from_Protected类：合法。  
  
## 15.20
```cpp
class Base
{
public:
	void memfcn(Base &b) { b = *this; };
protected:
	int prot_mem;
private:
	char priv_mem;
};

struct Pub_Derv : public Base
{
public:
	void memfcn(Base &b) { b = *this; };
};

struct Priv_Derv : private Base
{
public:
	void memfcn(Base &b) { b = *this; };
};

struct Prot_Derv : protected Base
{
public:
	void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Public : public Pub_Derv
{
public:
	void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Private : public Priv_Derv
{
public:
	// void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Protected : public Prot_Derv
{
public:
	void memfcn(Base &b) { b = *this; };
};

int main()
{
	Pub_Derv d1;
	Priv_Derv d2;
	Prot_Derv d3;
	Derived_from_Public dd1;
	Derived_from_Private dd2;
	Derived_from_Protected dd3;

	Base *p = &d1;
	// p = &d2;
	// p = &d3;
	p = &dd1;
	// p = &dd2;
	// p = &dd3;

	return 0;
}
```
  
## 15.21
代码取自github：  
```cpp
#include <iostream>
#include <string>

// just for 2D shape
class Shape
{
public:
    typedef std::pair<double, double>    Coordinate;

    Shape() = default;
    Shape(const std::string& n) :
        name(n) { }

    virtual double area()       const = 0;
    virtual double perimeter()  const = 0;

    virtual ~Shape() = default;
private:
    std::string name;
};

class Rectangle : public Shape
{
public:
    Rectangle() = default;
    Rectangle(const std::string& n,
              const Coordinate& a,
              const Coordinate& b,
              const Coordinate& c,
              const Coordinate& d) :
        Shape(n), a(a), b(b), c(c), d(d) { }

    ~Rectangle() = default;

protected:
    Coordinate  a;
    Coordinate  b;
    Coordinate  c;
    Coordinate  d;
};

class Square : public Rectangle
{
public:
    Square() = default;
    Square(const std::string& n,
           const Coordinate& a,
           const Coordinate& b,
           const Coordinate& c,
           const Coordinate& d) :
        Rectangle(n, a, b, c, d) { }

    ~Square() = default;
};


int main()
{

    return 0;
}
```
  
## 15.22
参见15.21。
  
## 15.23
添加 int fcn() override;  
`bp1->fcn(); //虚调用，将在运行时调用Base::fcn`
`bp2->fcn(); //虚调用，将在运行时调用D1::fcn`
`bp3->fcn(); //虚调用，将在运行时调用D2::fcn`
  
## 15.24
基类需要虚析构函数。如果一个类定义了析构函数，即使它通过=default的形式使用了合成的版本，编译器也不会为这个类合成移动操作。  
  
## 15.25
已经定义了一个构造函数，默认构造函数是被删除的，需要显式地定义。  
如果去掉了Disc_quote的默认构造函数，Bulk_quote的默认构造函数是被删除的。  
  
## 15.26
Quote_ex26.h
```cpp
#ifndef QUOTE_H_
#define QUOTE_H_

#include <string>
#include <iostream>

class Quote
{
friend bool operator!=(const Quote &lhs, const Quote &rhs) { return lhs.bookNo != rhs.bookNo && lhs.price != rhs.price; }
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
	Quote(const Quote&);
	Quote(Quote&&) noexcept;
	Quote& operator=(const Quote&);
	Quote& operator=(Quote&&) noexcept;
	std::string isbn() const { return bookNo; }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual void debug() const;
	virtual ~Quote();
private:
	std::string bookNo;
protected:
	double price = 0;
};

#endif
```
  
Bulk_quote_ex26.h
```cpp
#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Disc_quote_ex26.h"
#include <string>
#include <iostream>

class Bulk_quote : public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }
	Bulk_quote(Bulk_quote&);
	Bulk_quote(Bulk_quote&&) noexcept;
	Bulk_quote& operator=(Bulk_quote&);
	Bulk_quote& operator=(Bulk_quote&&) noexcept;
	double net_price(std::size_t) const override;
	void debug() const override;
	~Bulk_quote() override;
};

#endif
```
  
## 15.27
Bulk_quote.h
```cpp
#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Disc_quote.h"
#include <string>
#include <iostream>

class Bulk_quote : public Disc_quote
{
public:
	Bulk_quote() = default;
	using Disc_quote::Disc_quote;
	Bulk_quote(Bulk_quote&);
	Bulk_quote(Bulk_quote&&) noexcept;
	Bulk_quote& operator=(Bulk_quote&);
	Bulk_quote& operator=(Bulk_quote&&) noexcept;
	double net_price(std::size_t) const override;
	void debug() const override;
	~Bulk_quote() override;
};

#endif
```
  
## 15.28
ex28.cpp
```cpp
#include "Quote.h"
#include "Bulk_quote.h"
#include "Limit_quote.h"
#include <iostream>
#include <functional>
#include <vector>
#include <memory>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	Bulk_quote bq("A1-001", 80, 5, 0.2);
	Limit_quote lq("A1-001", 80, 5, 0.2);
	print_total(std::cout, q, 10);
	print_total(std::cout, bq, 10);
	print_total(std::cout, lq, 10);

	double total_price = 0;
	std::vector<Quote> vector_quote;
	vector_quote.push_back(bq);
	for(const auto &q : vector_quote)
		total_price += q.net_price(10);
	std::cout << "total_price:" << total_price << std::endl;

	return 0;
}
```

## 15.29
当派生类对象被赋值给基类对象时，其中的派生类部分将被“切掉”，因此容器和存在继承关系的类型无法兼容。  
而使用指针时，调用的是net_price版本依赖于指针所指对象的动态类型。  
ex29.cpp
```cpp
#include "Quote.h"
#include "Bulk_quote.h"
#include "Limit_quote.h"
#include <iostream>
#include <functional>
#include <vector>
#include <memory>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	Bulk_quote bq("A1-001", 80, 5, 0.2);
	Limit_quote lq("A1-001", 80, 5, 0.2);
	print_total(std::cout, q, 10);
	print_total(std::cout, bq, 10);
	print_total(std::cout, lq, 10);

	std::vector<std::shared_ptr<Quote>> basket;
	// basket.push_back(std::make_shared<Quote>(q));
	basket.push_back(std::make_shared<Bulk_quote>(bq));
	// basket.push_back(std::make_shared<Limit_quote>(lq));

	double total_price = 0;
	for (const auto &vq : basket)
		total_price += vq->net_price(10);
	std::cout << "total_price:" << total_price << std::endl;

	return 0;
}
```
  
## 15.30
