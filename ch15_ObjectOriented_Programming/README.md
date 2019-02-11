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
Bulk_quote_ex07.h
```cpp
#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Quote_ex03.h"
#include <string>

class Bulk_quote : public Quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), max_qty(qty), discount(disc) { }
	double net_price(std::size_t) const override;
private:
	std::size_t max_qty = 0;
	double discount = 0.0;
};

double Bulk_quote::net_price(size_t cnt) const
{
	if(cnt > max_qty) return max_qty * (1 - discount) * price + (cnt - max_qty)*price;
	else return cnt * price;
}

#endif
```
  
ex07.cpp
```cpp
#include "Quote_ex03.h"
#include "Bulk_quote_ex07.h"
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
	Bulk_quote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), max_qty(qty), discount(disc) { }
	double net_price(std::size_t) const override;
	void debug() const override;
private:
	std::size_t max_qty = 0;
	double discount = 0.0;
};

double Bulk_quote::net_price(size_t cnt) const
{
	if(cnt > max_qty) return max_qty * (1 - discount) * price + (cnt - max_qty)*price;
	else return cnt * price;
}

void Bulk_quote::debug() const
{
	Quote::debug();
	std::cout << "; max_qty: " << max_qty
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
