## 14.1
有所区别：  
当一个重载运算符是成员函数时，this绑定到左侧的运算对象；  
逻辑与运算符、逻辑或运算符和逗号运算符的运算对象求值顺序规则无法保留下来；  
&&和||运算符的重载版本也无法保留内置运算符的短路求值属性，两个运算对象总是会被求值。  
一样：  
对于一个重载的运算符来说，其优先级和结合律与对应的内置运算保持一致。  

## 14.2
Sales_data_ex02.h
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data;

std::istream &operator>>(std::istream &is, Sales_data &item);
std::ostream &operator<<(std::ostream &os, const Sales_data &item);
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);

struct Sales_data
{
friend std::istream& operator>>(std::istream&, Sales_data&);
friend std::ostream& operator<<(std::ostream&, const Sales_data&);
friend Sales_data operator+(const Sales_data&, const Sales_data&);
public:
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){std::cout << "Sales_data(const std::string &s, unsigned n, double p)" << std::endl;}
	Sales_data() : Sales_data("", 0, 0){std::cout << "Sales_data() : Sales_data(\"\", 0, 0)" << std::endl;}
	Sales_data(const std::string &s) : Sales_data(s, 0, 0){std::cout << "Sales_data(const std::string &s) : Sales_data" << std::endl;}
	Sales_data(std::istream &is) : Sales_data(){/*read(is, *this);*/ is >> *this; std::cout << "Sales_data(std::istream &is) : Sales_data()" << std::endl;}
	std::string isbn() const {return bookNo;}
    Sales_data& operator+=(const Sales_data&);
private:
	inline double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue / units_sold;
	else
		return 0;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

std::istream &operator>>(std::istream &is, Sales_data &item)
{
	double price = 0;

	is >> item.bookNo >> item.units_sold >> price;
	if(is)
		item.revenue = price * item.units_sold;
	else
		item = Sales_data();

	return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

	return os;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum += rhs;

	return sum;
}

#endif
```

ex02.cpp
```cpp
#include <iostream>
#include <string>
#include "Sales_data_ex02.h"

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2;
    Sales_data sales_data3("001-02");
    Sales_data sales_data4(std::cin);

    return 0;
}
```

## 14.3
（a）没有哪个版本；  
（b）string；  
（c）vector；  
（d）string。  

## 14.4
（a）不应该；（b）应该；（c）应该；（d）必须是成员；（e）不应该；（f）不应该；（g）不应该；（h）必须是成员。  

## 14.5
book_ex05.h
```cpp
#ifndef CP5_CH14_EX14_05_H
#define CP5_CH14_EX14_05_H

#include <iostream>
#include <string>

class Book {
    friend std::istream& operator>>(std::istream&, Book&);
    friend std::ostream& operator<<(std::ostream&, const Book&);
    friend bool operator==(const Book&, const Book&);
    friend bool operator!=(const Book&, const Book&);

public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubdate):no_(no), name_(name), author_(author), pubdate_(pubdate) { }
    Book(std::istream &in) { in >> *this; }

private:
    unsigned no_;
    std::string name_;
    std::string author_;
    std::string pubdate_;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);


#endif // CP5_CH14_EX14_05_H
```

book_ex05.cpp
```cpp
#include "book_ex05.h"

std::istream& operator>>(std::istream &in, Book &book)
{
    in >> book.no_ >> book.name_ >> book.author_ >> book.pubdate_;
    return in;
}

std::ostream& operator<<(std::ostream &out, const Book &book)
{
    out << book.no_ << " " << book.name_ << " " << book.author_ << " " << book.pubdate_;
    return out;
}

bool operator==(const Book &lhs, const Book &rhs)
{
    return lhs.no_ == rhs.no_;
}

bool operator!=(const Book &lhs, const Book &rhs)
{
    return !(lhs == rhs);
}
```

ex05.cpp
```cpp
#include "book_ex05.h"

int main()
{
    Book book1(123, "CP5", "Lippman", "2012");
    Book book2(123, "CP5", "Lippman", "2012");

    if (book1 == book2)
        std::cout << book1 << std::endl;
}
```

## 14.6
参见14.2。  

## 14.7
String_ex07.h
```cpp
#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

class String
{
friend std::ostream &operator<<(std::ostream &os, const String &s);
public:
	String();
	String(const char*);
	String(const String&);
	String(String&&) noexcept;
	String& operator=(const String&);
	String& operator=(String&&) noexcept;
	char *begin() const { return elements; }
	char *end() const { return first_free; }
	~String();
private:
	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
	void free();

	std::allocator<char> alloc;
	char *elements;
	char *first_free;
};

std::pair<char*, char*> String::alloc_n_copy(const char *begin, const char *end)
{
	char *p = alloc.allocate(end - begin);
	// for(auto iter = begin; iter != end; ++iter)
	// 	alloc.construct(iter, *iter);
	return{p, std::uninitialized_copy(begin, end, p)};
}

String::String(const char* cp)
{
	size_t n = strlen(cp);
	auto newstr = alloc_n_copy(cp, cp + n);
	elements = newstr.first;
	first_free = newstr.second;
	// char* p = alloc.allocate(n);

	// for(int i = 0; i < n; ++i)
	// 	alloc.construct(p+i, *(cp+i));
}

String::String()
{
	String("");
}

String::String(const String &rhs)
{
	auto newstr = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newstr.first;
	first_free = newstr.second;
	std::cout << "String(const String &rhs)" << std::endl;
}

String::String(String &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free))
{
	std::cout << "String::String(String &&s) noexcept" << std::endl;
	s.elements = s.first_free = nullptr;
}

void String::free()
{
	if(elements)
	{
		std::for_each(elements, first_free, [this](char cp){ alloc.destroy(&cp); });
		alloc.deallocate(elements, first_free - elements);
	}
}

String& String::operator=(const String& rhs)
{
	auto newstr = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newstr.first;
	first_free = newstr.second;
	std::cout << "String& operator=(const String& rhs)" << std::endl;
	return *this;
}

String& String::operator=(String &&rhs) noexcept
{
	std::cout << "String& String::operator=(String &&rhs) noexcept" << std::endl;
	if(&rhs != this)
	{
		free();
		alloc = std::move(rhs.alloc);
		elements = std::move(rhs.elements);
		first_free = std::move(rhs.first_free);
		rhs.elements = rhs.first_free = nullptr;
	}
	return *this;
}

String::~String()
{
	// for(auto iter = elements; iter != first_free; )
	// 	alloc.destroy(--iter);
	free();
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
	for(auto iter = s.elements; iter != s.first_free; ++iter)
	{
		os << *iter ;
	}
	return os;
}

#endif
```

ex07.cpp
```cpp
#include "String_ex07.h"
#include <vector>
#include <iostream>

int main()
{
	std::vector<String> v;
	v.push_back("aaa");
	v.push_back("bbb");
	std::cout << v[1] << std::endl;

	return 0;
}
```

## 14.8
参见14.5。  

## 14.9
参见14.2。  

## 14.10
（a）正确格式；（b）错误格式，但是.95被保存到price，10是ISBN，最终输出为：10 24 22.8 0.95。  

## 14.11
没有输入检查，与上题结果一样。  

## 14.12
参见14.5。  

## 14.13
添加加法和减法。  
  
Sales_data_ex13.h
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data;

std::istream &operator>>(std::istream &is, Sales_data &item);
std::ostream &operator<<(std::ostream &os, const Sales_data &item);
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);

struct Sales_data
{
friend std::istream& operator>>(std::istream&, Sales_data&);
friend std::ostream& operator<<(std::ostream&, const Sales_data&);
friend Sales_data operator+(const Sales_data&, const Sales_data&);
public:
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){std::cout << "Sales_data(const std::string &s, unsigned n, double p)" << std::endl;}
	Sales_data() : Sales_data("", 0, 0){std::cout << "Sales_data() : Sales_data(\"\", 0, 0)" << std::endl;}
	Sales_data(const std::string &s) : Sales_data(s, 0, 0){std::cout << "Sales_data(const std::string &s) : Sales_data" << std::endl;}
	Sales_data(std::istream &is) : Sales_data(){/*read(is, *this);*/ is >> *this; std::cout << "Sales_data(std::istream &is) : Sales_data()" << std::endl;}
	std::string isbn() const {return bookNo;}
    Sales_data& operator+=(const Sales_data&);
    Sales_data& operator-=(const Sales_data&);
private:
	inline double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue / units_sold;
	else
		return 0;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

Sales_data& Sales_data::operator-=(const Sales_data &rhs)
{
	units_sold -= rhs.units_sold;
	revenue -= rhs.revenue;

	return *this;
}

std::istream &operator>>(std::istream &is, Sales_data &item)
{
	double price = 0;

	is >> item.bookNo >> item.units_sold >> price;
	if(is)
		item.revenue = price * item.units_sold;
	else
		item = Sales_data();

	return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

	return os;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum += rhs;

	return sum;
}

#endif
```
  
ex13.cpp
```cpp
#include <iostream>
#include <string>
#include "Sales_data_ex13.h"

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2;
    Sales_data sales_data3("001-02");
    Sales_data sales_data4(std::cin);
    std::cout << sales_data4 << std::endl;

    return 0;
}
```
  
## 14.14
operator+需要创建新对象；operator+=只使用一个对象。调用operator+=为用户重载的运算符，更简洁，更符合实际逻辑。  

## 14.15
参见14.5，暂不添加。

## 14.16
StrBlob_ex16.h
```cpp
#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <string>
#include <initializer_list>
#include <memory>
#include <vector>
#include <stdexcept>

class ConstStrBlobPtr;

class StrBlob
{
friend class ConstStrBlobPtr;
friend bool operator==(const StrBlob &lhs, const StrBlob &rhs);
friend bool operator!=(const StrBlob &lhs, const StrBlob &rhs);
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	StrBlob(const StrBlob&);
	StrBlob &operator=(const StrBlob&);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t) { data->push_back(t); }
	void push_back(std::string &&t) { data->push_back(t); }
	void pop_back();
	std::string& front();
	std::string& back();
	const std::string& front() const;
	const std::string& back() const;
	ConstStrBlobPtr begin();
	ConstStrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const;
};

class ConstStrBlobPtr
{
friend bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
friend bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
public:
	ConstStrBlobPtr() : curr(0){};
	ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	std::string& deref() const;
	ConstStrBlobPtr& incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
};

std::shared_ptr<std::vector<std::string>> ConstStrBlobPtr::check(std::size_t i, const std::string &msg) const
{
	auto ret = wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound ConstStrBlobPtr");
	if(i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

std::string& ConstStrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
	check(curr, "increment past end of ConstStrBlobPtr");
	++curr;
	return *this;
}

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)){}
StrBlob::StrBlob(const StrBlob &sb) { data = std::make_shared<std::vector<std::string>>(*sb.data); }
StrBlob &StrBlob::operator=(const StrBlob &sb) { data = std::make_shared<std::vector<std::string>>(*sb.data); return *this; }

void StrBlob::check(size_type i, const std::string &msg) const
{
	if(i >= data->size())
		throw std::out_of_range(msg);
}

std::string & StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

std::string & StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

const std::string& StrBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}

const std::string& StrBlob::back() const
{
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

ConstStrBlobPtr StrBlob::begin() { return ConstStrBlobPtr(*this); }

ConstStrBlobPtr StrBlob::end()
{
	auto ret = ConstStrBlobPtr(*this, data->size());
	return ret;
}

bool operator==(const StrBlob &lhs, const StrBlob &rhs)
{
	return *lhs.data == *rhs.data;
}

bool operator!=(const StrBlob &lhs, const StrBlob &rhs)
{
	return !(lhs == rhs);
}

bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
	auto lret = lhs.wptr.lock(), rret = rhs.wptr.lock();

	return lret == rret && lhs.curr == rhs.curr;
}

bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
	return !(lhs == rhs);
}

#endif
```
  
ex16_1.cpp  
```cpp
#include "StrBlob_ex16.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	StrBlob b2 = b1;

	return 0;
}
```

StrVec_ex16.h
```cpp
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>
#include <algorithm>

class StrVec
{
friend bool operator==(StrVec &lhs, StrVec &rhs);
friend bool operator!=(StrVec &lhs, StrVec &rhs);
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec&);
	StrVec(StrVec &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free)), cap(std::move(s.cap)) { s.elements = s.first_free = s.cap = nullptr; }
	StrVec &operator=(const StrVec&);
	StrVec &operator=(StrVec&&) noexcept;
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

#endif
```
  
ex16_2.cpp  
```cpp
#include "StrVec_ex16.h"

int main()
{
	StrVec s({"aaa", "bbb"});

	return 0;
}
```
  
String_ex16.h  
```cpp
#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

class String
{
friend std::ostream &operator<<(std::ostream &os, const String &s);
friend bool operator==(const String lhs, const String rhs);
friend bool operator!=(const String lhs, const String rhs);
public:
	String();
	String(const char*);
	String(const String&);
	String(String&&) noexcept;
	String& operator=(const String&);
	String& operator=(String&&) noexcept;
	char *begin() const { return elements; }
	char *end() const { return first_free; }
	~String();
private:
	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
	void free();

	std::allocator<char> alloc;
	char *elements;
	char *first_free;
};

std::pair<char*, char*> String::alloc_n_copy(const char *begin, const char *end)
{
	char *p = alloc.allocate(end - begin);
	return{p, std::uninitialized_copy(begin, end, p)};
}

String::String(const char* cp)
{
	size_t n = strlen(cp);
	auto newstr = alloc_n_copy(cp, cp + n);
	elements = newstr.first;
	first_free = newstr.second;
}

String::String()
{
	String("");
}

String::String(const String &rhs)
{
	auto newstr = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newstr.first;
	first_free = newstr.second;
	std::cout << "String(const String &rhs)" << std::endl;
}

String::String(String &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free))
{
	std::cout << "String::String(String &&s) noexcept" << std::endl;
	s.elements = s.first_free = nullptr;
}

void String::free()
{
	if(elements)
	{
		std::for_each(elements, first_free, [this](char cp){ alloc.destroy(&cp); });
		alloc.deallocate(elements, first_free - elements);
	}
}

String& String::operator=(const String& rhs)
{
	auto newstr = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newstr.first;
	first_free = newstr.second;
	std::cout << "String& operator=(const String& rhs)" << std::endl;
	return *this;
}

String& String::operator=(String &&rhs) noexcept
{
	std::cout << "String& String::operator=(String &&rhs) noexcept" << std::endl;
	if(&rhs != this)
	{
		free();
		alloc = std::move(rhs.alloc);
		elements = std::move(rhs.elements);
		first_free = std::move(rhs.first_free);
		rhs.elements = rhs.first_free = nullptr;
	}
	return *this;
}

String::~String()
{
	free();
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
	for(auto iter = s.elements; iter != s.first_free; ++iter)
	{
		os << *iter ;
	}
	return os;
}

bool operator==(const String lhs, const String rhs)
{
	return (lhs.first_free - lhs.elements) == (rhs.first_free - rhs.elements) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const String lhs, const String rhs)
{
	return !(lhs == rhs);
}

#endif
```
  
ex16_3.cpp
```cpp
#include "String_ex16.h"
#include <vector>
#include <iostream>

int main()
{
	std::vector<String> v;
	v.push_back("aaa");
	v.push_back("bbb");
	std::cout << v[1] << std::endl;

	return 0;
}
```

## 14.17
参见14.5。  

## 14.18
StrBlob_ex18.h
```cpp
#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <string>
#include <initializer_list>
#include <memory>
#include <vector>
#include <stdexcept>

class ConstStrBlobPtr;

class StrBlob
{
friend class ConstStrBlobPtr;
friend bool operator==(const StrBlob &lhs, const StrBlob &rhs);
friend bool operator!=(const StrBlob &lhs, const StrBlob &rhs);
friend bool operator<(const StrBlob &lhs, const StrBlob &rhs);
friend bool operator>(const StrBlob &lhs, const StrBlob &rhs);
friend bool operator<=(const StrBlob &lhs, const StrBlob &rhs);
friend bool operator>=(const StrBlob &lhs, const StrBlob &rhs);
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	StrBlob(const StrBlob&);
	StrBlob &operator=(const StrBlob&);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t) { data->push_back(t); }
	void push_back(std::string &&t) { data->push_back(t); }
	void pop_back();
	std::string& front();
	std::string& back();
	const std::string& front() const;
	const std::string& back() const;
	ConstStrBlobPtr begin();
	ConstStrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const;
};

class ConstStrBlobPtr
{
friend bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
friend bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs);
public:
	ConstStrBlobPtr() : curr(0){};
	ConstStrBlobPtr(const StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	std::string& deref() const;
	ConstStrBlobPtr& incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
};

std::shared_ptr<std::vector<std::string>> ConstStrBlobPtr::check(std::size_t i, const std::string &msg) const
{
	auto ret = wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound ConstStrBlobPtr");
	if(i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

std::string& ConstStrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

ConstStrBlobPtr& ConstStrBlobPtr::incr()
{
	check(curr, "increment past end of ConstStrBlobPtr");
	++curr;
	return *this;
}

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)){}
StrBlob::StrBlob(const StrBlob &sb) { data = std::make_shared<std::vector<std::string>>(*sb.data); }
StrBlob &StrBlob::operator=(const StrBlob &sb) { data = std::make_shared<std::vector<std::string>>(*sb.data); return *this; }

void StrBlob::check(size_type i, const std::string &msg) const
{
	if(i >= data->size())
		throw std::out_of_range(msg);
}

std::string & StrBlob::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

std::string & StrBlob::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

const std::string& StrBlob::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}

const std::string& StrBlob::back() const
{
	check(0, "back on empty StrBlob");
	return data->back();
}

void StrBlob::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

ConstStrBlobPtr StrBlob::begin() { return ConstStrBlobPtr(*this); }

ConstStrBlobPtr StrBlob::end()
{
	auto ret = ConstStrBlobPtr(*this, data->size());
	return ret;
}

bool operator==(const StrBlob &lhs, const StrBlob &rhs)
{
	return *lhs.data == *rhs.data;
}

bool operator!=(const StrBlob &lhs, const StrBlob &rhs)
{
	return !(lhs == rhs);
}

bool operator<(const StrBlob &lhs, const StrBlob &rhs)
{
	return std::lexicographical_compare(lhs.data->begin(), lhs.data->end(), rhs.data->begin(), rhs.data->end());
}

bool operator>(const StrBlob &lhs, const StrBlob &rhs)
{
	return rhs < lhs;
}

bool operator<=(const StrBlob &lhs, const StrBlob &rhs)
{
	return !(rhs < lhs);
}

bool operator>=(const StrBlob &lhs, const StrBlob &rhs)
{
	return !(lhs < rhs);
}

bool operator==(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
	auto lret = lhs.wptr.lock(), rret = rhs.wptr.lock();

	return lret == rret && lhs.curr == rhs.curr;
}

bool operator!=(const ConstStrBlobPtr &lhs, const ConstStrBlobPtr &rhs)
{
	return !(lhs == rhs);
}

#endif
```
  
ex18_1.cpp
```cpp
#include "StrBlob_ex18.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	StrBlob b2 = b1;

	return 0;
}
```
  
StrVec_ex18.h
```cpp
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>
#include <algorithm>

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
	StrVec &operator=(const StrVec&);
	StrVec &operator=(StrVec&&) noexcept;
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
  
ex18_2.cpp
```cpp
#include "StrVec_ex18.h"

int main()
{
	StrVec s({"aaa", "bbb"});

	return 0;
}
```
  
String_ex18.h
```cpp
#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

class String
{
friend std::ostream &operator<<(std::ostream &os, const String &s);
friend bool operator==(const String lhs, const String rhs);
friend bool operator!=(const String lhs, const String rhs);
friend bool operator<(const String lhs, const String rhs);
friend bool operator>(const String lhs, const String rhs);
friend bool operator<=(const String lhs, const String rhs);
friend bool operator>=(const String lhs, const String rhs);
public:
	String();
	String(const char*);
	String(const String&);
	String(String&&) noexcept;
	String& operator=(const String&);
	String& operator=(String&&) noexcept;
	char *begin() const { return elements; }
	char *end() const { return first_free; }
	~String();
private:
	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
	void free();

	std::allocator<char> alloc;
	char *elements;
	char *first_free;
};

std::pair<char*, char*> String::alloc_n_copy(const char *begin, const char *end)
{
	char *p = alloc.allocate(end - begin);
	return{p, std::uninitialized_copy(begin, end, p)};
}

String::String(const char* cp)
{
	size_t n = strlen(cp);
	auto newstr = alloc_n_copy(cp, cp + n);
	elements = newstr.first;
	first_free = newstr.second;
}

String::String()
{
	String("");
}

String::String(const String &rhs)
{
	auto newstr = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newstr.first;
	first_free = newstr.second;
	std::cout << "String(const String &rhs)" << std::endl;
}

String::String(String &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free))
{
	std::cout << "String::String(String &&s) noexcept" << std::endl;
	s.elements = s.first_free = nullptr;
}

void String::free()
{
	if(elements)
	{
		std::for_each(elements, first_free, [this](char cp){ alloc.destroy(&cp); });
		alloc.deallocate(elements, first_free - elements);
	}
}

String& String::operator=(const String& rhs)
{
	auto newstr = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newstr.first;
	first_free = newstr.second;
	std::cout << "String& operator=(const String& rhs)" << std::endl;
	return *this;
}

String& String::operator=(String &&rhs) noexcept
{
	std::cout << "String& String::operator=(String &&rhs) noexcept" << std::endl;
	if(&rhs != this)
	{
		free();
		alloc = std::move(rhs.alloc);
		elements = std::move(rhs.elements);
		first_free = std::move(rhs.first_free);
		rhs.elements = rhs.first_free = nullptr;
	}
	return *this;
}

String::~String()
{
	free();
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
	for(auto iter = s.elements; iter != s.first_free; ++iter)
	{
		os << *iter ;
	}
	return os;
}

bool operator==(const String lhs, const String rhs)
{
	return (lhs.first_free - lhs.elements) == (rhs.first_free - rhs.elements) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const String lhs, const String rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String lhs, const String rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), lhs.end());
}

bool operator>(const String lhs, const String rhs)
{
	return rhs < lhs;
}

bool operator<=(const String lhs, const String rhs)
{
	return !(rhs < lhs);
}

bool operator>=(const String lhs, const String rhs)
{
	return !(lhs < rhs);
}

#endif
```
  
ex18_3.cpp
```cpp
#include "String_ex18.h"
#include <vector>
#include <iostream>

int main()
{
	std::vector<String> v;
	v.push_back("aaa");
	v.push_back("bbb");
	std::cout << v[1] << std::endl;

	return 0;
}
```

## 14.19
