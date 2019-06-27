## 练习15.1

> 什么是虚成员？

虚函数是基类希望其派生类进行覆盖的函数。
  
## 练习15.2

> protected 访问说明符与 private 有何区别？

派生类的成员函数可以访问protected访问运算符的成员，而不能访问private的。
  
## 练习15.3

> 定义你自己的 Quote 类和 print_total 函数。

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
  
## 练习15.4

> 下面哪条声明语句是不正确的？请解释原因。
```cpp
class Base { ... };
(a) class Derived : public Derived { ... };
(b) class Derived : private Base { ... };
(c) class Derived : public Base;
```

（a）不正确，是定义，不是声明，而且不能继承它自己；  
（b）不正确，是定义，不是声明；  
（c）不正确，声明中包含类名，但是不包含它的派生列表。  
  
## 练习15.05

> 定义你自己的 Bulk_quote 类。

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
  
## 练习15.06

> 将 Quote 和 Bulk_quote 的对象传给15.2.1节练习中的 print_total 函数，检查该函数是否正确。

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
  
## 练习15.07

> 定义一个类使其实现一种数量受限的折扣策略，具体策略是：当购买书籍的数量不超过一个给定的限量时享受折扣，如果购买量一旦超过了限量，则超出的部分将以原价销售。

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
  
## 练习15.08

> 给出静态类型和动态类型的定义。

表达式的静态类型在编译时总是已知的，它是变量声明时的类型或表达式生成的类型；  
动态类型则是变量或表达式表示的内存中的对象类型。动态类型直到运行时才可知。  
  
## 练习15.09

> 在什么情况下表达式的静态类型可能与动态类型不同？请给出三个静态类型与动态类型不同的例子。

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
  
## 练习15.10

> 回忆我们在8.1节进行的讨论，解释第284页中将 ifstream 传递给 Sales_data 的read 函数的程序是如何工作的。

read中std::istream，std::ifstream是继承自std::istream，因此，std::istream的实例传入后会转换为std::istream。
  
## 练习15.11

> 为你的 Quote 类体系添加一个名为 debug 的虚函数，令其分别显示每个类的数据成员。

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
  
## 练习15.12

> 有必要将一个成员函数同时声明成 override 和 final 吗？为什么？

有必要，如果该成员函数不希望被后续的派生类继承，则可声明成final，与当前的override没有关系。
  
## 练习15.13

> 给定下面的类，解释每个 print 函数的机理：
```cpp
class base {
public:
	string name() { return basename;}
	virtual void print(ostream &os) { os << basename; }
private:
	string basename;
};
class derived : public base {
public:
	void print(ostream &os) { print(os); os << " " << i; }
private:
	int i;
};
```
在上述代码中存在问题吗？如果有，你该如何修改它？

派生类中的print函数会递归调用当前print，知道内存耗尽。  
```cpp
void print(ostream &os) { base::print(os); os << " " << i; }
```
  
## 练习15.14

> 给定上一题中的类以及下面这些对象，说明在运行时调用哪个函数：
```cpp
base bobj; 		base *bp1 = &bobj; 	base &br1 = bobj;
derived dobj; 	base *bp2 = &dobj; 	base &br2 = dobj;
(a) bobj.print();	(b)dobj.print();	(c)bp1->name();
(d)bp2->name();		(e)br1.print();		(f)br2.print();
```

（a）调用base中的print，编译时确定；  
（b）调用derived中的print，编译时确定；  
（c）调用base中的name函数，不是虚函数，没有动态绑定，所以编译时确定；  
（d）调用derived中的name函数，不是虚函数，没有动态绑定，所以编译时确定；  
（e）调用base中的print，运行时确定；  
（f）调用derived中的print，运行时确定。  
  
## 练习15.15

> 定义你自己的 Disc_quote 和 Bulk_quote。

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
  
## 练习15.16

> 改写你在15.2.2节练习中编写的数量受限的折扣策略，令其继承 Disc_quote。

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
  
## 练习15.17

> 尝试定义一个 Disc_quote 的对象，看看编译器给出的错误信息是什么？

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
  
## 练习15.18

> 假设给定了第543页和第544页的类，同时已知每个对象的类型如注释所示，判断下面的哪些赋值语句是合法的。解释那些不合法的语句为什么不被允许：
```cpp
Base *p = &d1;  //d1 的类型是 Pub_Derv
p = &d2;		//d2 的类型是 Priv_Derv
p = &d3;		//d3 的类型是 Prot_Derv
p = &dd1;		//dd1 的类型是 Derived_from_Public	
p = &dd2;		//dd2 的类型是 Derived_from_Private
p = &dd3;		//dd3 的类型是 Derived_from_Protected
```

(a)合法；  
(b)非法；  
(c)非法；  
(d)合法；  
(d)非法；  
(f)非法。  
只有当D公有地继承B时，用户代码才能使用派生类向基类的转换。  
  
## 练习15.19

> 假设543页和544页的每个类都有如下形式的成员函数：
```cpp
void memfcn(Base &b) { b = *this; }
```
对于每个类，分别判断上面的函数是否合法。

Base类：合法；  
Pub_Derv类：合法；  
Priv_Derv类：合法；  
Prot_Derv类：合法；  
Derived_from_Public类：合法；  
Derived_from_Private类：非法；  
Derived_from_Protected类：合法。  
  
## 练习15.20

> 编写代码检验你对前面两题的回答是否正确。

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
  
## 练习15.21

> 从下面这些一般性抽象概念中任选一个（或者选一个你自己的），将其对应的一组类型组织成一个继承体系：
```cpp
(a) 图形文件格式（如gif、tiff、jpeg、bmp）
(b) 图形基元（如方格、圆、球、圆锥）
(c) C++语言中的类型（如类、函数、成员函数）
```

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
  
## 练习15.22

> 对于你在上一题中选择的类，为其添加函数的虚函数及公有成员和受保护的成员。

参见15.21。
  
## 练习15.23

> 假设第550页的 D1 类需要覆盖它继承而来的 fcn 函数，你应该如何对其进行修改？如果你修改之后 fcn 匹配了 Base 中的定义，则该节的那些调用语句将如何解析？

添加 int fcn() override;  
`bp1->fcn(); //虚调用，将在运行时调用Base::fcn`
`bp2->fcn(); //虚调用，将在运行时调用D1::fcn`
`bp3->fcn(); //虚调用，将在运行时调用D2::fcn`
  
## 练习15.24

> 哪种类需要虚析构函数？虚析构函数必须执行什么样的操作？

基类需要虚析构函数。如果一个类定义了析构函数，即使它通过=default的形式使用了合成的版本，编译器也不会为这个类合成移动操作。  
  
## 练习15.25

> 我们为什么为 Disc_quote 定义一个默认构造函数？如果去掉该构造函数的话会对 Bulk_quote 的行为产生什么影响？

已经定义了一个构造函数，默认构造函数是被删除的，需要显式地定义。  
如果去掉了Disc_quote的默认构造函数，Bulk_quote的默认构造函数是被删除的。  
  
## 练习15.26

> 定义 Quote 和 Bulk_quote 的拷贝控制成员，令其与合成的版本行为一致。为这些成员以及其他构造函数添加打印状态的语句，使得我们能够知道正在运行哪个程序。使用这些类编写程序，预测程序将创建和销毁哪些对象。重复实验，不断比较你的预测和实际输出结果是否相同，直到预测完全准确再结束。

[Quote_ex26.h](ex26)
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
  
## 练习15.27

> 重新定义你的 Bulk_quote 类，令其继承构造函数。

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
  
## 练习15.28

> 定义一个存放 Quote 对象的 vector，将 Bulk_quote 对象传入其中。计算 vector 中所有元素总的 net_price。

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

## 练习15.29

> 再运行一次你的程序，这次传入 Quote 对象的 shared_ptr 。如果这次计算出的总额与之前的不一致，解释为什么;如果一直，也请说明原因。

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
  
## 练习15.30

> 编写你自己的 Basket 类，用它计算上一个练习中交易记录的总价格。

将print_total函数放入Quote.h。
Basket.h
```cpp
#ifndef BASKET_H_
#define BASKET_H_

#include "Quote.h"
#include <iostream>
#include <memory>
#include <set>

class Basket
{
public:
	void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
	void add_item(const Quote &sale) { items.insert(std::shared_ptr<Quote>(sale.clone())); }
	void add_item(Quote &&sale) { items.insert(std::shared_ptr<Quote>(std::move(sale).clone())); }
	double total_receipt(std::ostream&) const;
private:
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &rhs) { return lhs->isbn() < rhs->isbn(); }
	std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

#endif
```
  
Basket.cpp
```cpp
#include "Basket.h"

double Basket::total_receipt(std::ostream &os) const
{
	double sum = 0.0;
	for(auto iter = items.cbegin(); iter != items.cend(); iter = items.upper_bound(*iter))
	{
		sum += print_total(os, **iter, items.count(*iter));
	}

	os << "Total Sale: " << sum << std::endl;
	return sum;
}
```
  
ex30.cpp
```cpp
#include "Quote.h"
#include "Bulk_quote.h"
#include "Limit_quote.h"
#include "Basket.h"
#include <iostream>
#include <functional>
#include <vector>
#include <memory>

int main()
{
	Bulk_quote bq("A1-001", 80, 5, 0.2);
	print_total(std::cout, bq, 10);

	std::vector<std::shared_ptr<Quote>> basket;
	basket.push_back(std::make_shared<Bulk_quote>(bq));

	// double total_price = 0;
	// for (const auto &vq : basket)
	// 	total_price += vq->net_price(10);
	// std::cout << "total_price:" << total_price << std::endl;

	Basket basket_object;
	for (int i = 0; i < 10; ++i)
	{
		basket_object.add_item(bq);
	}
	basket_object.total_receipt(std::cout);

	return 0;
}
```
  
## 练习15.31

> 已知 s1、s2、s3 和 s4 都是 string，判断下面的表达式分别创建了什么样的对象：
```cpp
(a) Query(s1) | Query(s2) & ~Query(s3);
(b) Query(s1) | (Query(s2) & ~Query(s3));
(c) (Query(s1) & (Query(s2)) | (Query(s3) & Query(s4)));
```

（a）WordQuery orQuery AndQuery NotQuery；  
（b）WordQuery orQuery AndQuery NotQuery；  
（c）WordQuery orQuery AndQuery。  
  
## 练习15.32

> 当一个 Query 类型的对象被拷贝、移动、赋值或销毁时，将分别发生什么？

拷贝：将会调用合成的拷贝构造函数。它将数据成员复制到新对象中。数据成员是一个共享指针，复制时，对应的共享指针指向相同的地址，两个共享指针的使用计数变为2。  
移动：将会调用合成的移动构造函数。它将数据成员移动到新对象中。移动时，新建对象的共享指针将指向原始共享指针指向的地址。移动操作后，新对象中共享指针的使用计数为1，而来自原始对象的指针变为nullptr。  
拷贝赋值：将调用合成的拷贝赋值函数。此操作与复制操作相同。  
拷贝移动：将调用合成的移动赋值函数。此操作与移动操作相同。  
销毁：将调用合成的析构函数。它将调用share_ptr的析构函数，减少计数次数。如果计数变为0，shared_ptr的析构函数将删除它所指向的资源。  
  
## 练习15.33

> 当一个 Query_base 类型的对象被拷贝、移动赋值或销毁时，将分别发生什么？

由合成的版本管理。Query_base是一个抽象类，所以这种类型的对象本质上是派生类的子对象。  
  
## 练习15.34

> 针对图15.3构建的表达式：
```cpp
(a) 例举出在处理表达式的过程中执行的所有构造函数。
(b) 例举出 cout << q 所调用的 rep。
(c) 例举出 q.eval() 所调用的 eval。
```

（a）Query(const std::string &s)，s为fiery、bird、wind；  
WordQuery(const std::string &s)，s为fiery、bird、wind；  
AndQuery(const Query &left, const Query &right）；  
BinaryQuery(const Query &l, const Query &r, std::string s)；  
Query(std::shared_ptr<Query_base> query)；  
OrQuery(const Query &left, const Query &right)；  
BinaryQuery(const Query &l, const Query &r, std::string s)；  
Query(std::shared_ptr<Query_base> query)；  
（b）query.rep()；  
q->rep()，指向OrQuery::rep()；  
Query::rep(),lhs为AndQuery::rep()，rhs为WordQuery::rep()；  
AndQuery::rep()；  
Query::rep();  
（c）q->eval()，指向OrQuery::eval()。  
  
## 练习15.35

> 实现 Query 类和 Query_base 类，其中需要定义rep 而无须定义 eval。

Query.h
```cpp
#ifndef QUERY_H_
#define QUERY_H_

#include <string>
#include <iostream>
#include "Query_base.h"
#include "WordQuery.h"
#include "TextQuery.h"

class Query
{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, const Query&);
	friend Query operator&(const Query&, const Query&);
public:
	Query(const std::string&);
	QueryResult eval(const TextQuery &t) const { return q->eval(t); }
	std::string rep() const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_base> query) : q(query) { }
	std::shared_ptr<Query_base> q;
};

std::ostream& operator<<(std::ostream &os, const Query &query)
{
	return os << query.rep();
}

inline Query::Query(const std::string &s) : q(new WordQuery(s)) { std::cout << "Query::Query(const std::string &s)" << std::endl; }

#endif
```
  
Query_base.h
```cpp
#ifndef QUERY_BASE_H_
#define QUERY_BASE_H_

#include <string>
#include <iostream>
#include "TextQuery.h"
#include "Query.h"

class Query_base
{
	friend class Query;
protected:
	using line_no = TextQuery::line_no;
	virtual ~Query_base() = default;
private:
	virtual QueryResult eval(const TextQuery&) const = 0;
	virtual std::string rep() const = 0;
};

#endif
```
  
## 练习15.36

> 在构造函数和 rep 成员中添加打印语句，运行你的代码以检验你对本节第一个练习中(a)、(b)两小题的回答是否正确。

（a）
```sh
WordQuery(const std::string &s)
Query::Query(const std::string &s)
WordQuery(const std::string &s)
Query::Query(const std::string &s)
WordQuery(const std::string &s)
Query::Query(const std::string &s)
BinaryQuery(const Query &l, const Query &r, std::string s)
AndQuery(const Query &left, const Query &right)
Query(std::shared_ptr<Query_base> query)
BinaryQuery(const Query &l, const Query &r, std::string s)
OrQuery(const Query &left, const Query &right)
Query(std::shared_ptr<Query_base> query)
```
  
（b）
```sh
Query::rep()
BinaryQuery::rep()|
Query::rep()
WordQuery::rep()
Query::rep()
BinaryQuery::rep()&
Query::rep()
WordQuery::rep()
Query::rep()
WordQuery::rep()
```
  
## 练习15.37

> 如果在派生类中含有 shared_ptr<Query_base> 类型的成员而非 Query 类型的成员，则你的类需要做出怎样的改变？

接口函数需要改变，需要将Query改为shared_ptr<Query_base>。  
  
## 练习15.38

> 下面的声明合法吗？如果不合法，请解释原因;如果合法，请指出该声明的含义。
```cpp
BinaryQuery a = Query("fiery") & Query("bird");
AndQuery b = Query("fiery") & Query("bird");
OrQuery c = Query("fiery") & Query("bird");
```

（a）非法，BinaryQuery为抽象类；  
（b）非法，返回的为Query类型，不能转换为AndQuery；  
（c）非法，返回的为Query类型，不能转换为AndQuery。  
  
## 练习15.39

> 实现 Query 类和　Query_base 类，求图15.3中表达式的值并打印相关信息，验证你的程序是否正确。

返回的是shared_ptr<StrBlob>，需要增加构造函数或者修改get_file()。  
Query类和Query_base类都没有变化，运行结果如下：
```sh
((fiery & bird) | wind) occurs 3 
	(line 2) Her Daddy says when the wind blows 
	(line 4) like a fiery bird in flight. 
	(line 5) A beautiful fiery bird, he tells her, 
```
  
## 练习15.40

> 在 OrQuery 的 eval 函数中，如果 rhs 成员返回的是空集将发生什么？

不会发生什么。  
  
## 练习15.41

> 重新实现你的类，这次使用指向 Query_base 的内置指针而非 shared_ptr。请注意，做出上述改动后你的类将不能再使用合成的拷贝控制成员。

请自行实现。  
  
## 练习15.42

> 从下面的几种改进中选择一种，设计并实现它:
```cpp
(a) 按句子查询并打印单词，而不再是按行打印。
(b) 引入一个历史系统，用户可以按编号查阅之前的某个查询，并可以在其中添加内容或者将其余其他查询组合。
(c) 允许用户对结果做出限制，比如从给定范围的行中跳出匹配的进行显示。
```

请自行实现。  