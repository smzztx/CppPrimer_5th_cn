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
book_ex19.h
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
    friend bool operator<(const Book&, const Book&);
    friend bool operator>(const Book&, const Book&);
    friend bool operator<=(const Book&, const Book&);
    friend bool operator>=(const Book&, const Book&);

public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubdate):no_(no), name_(name), author_(author), pubdate_(pubdate) { }
    Book(std::istream &in) { in >> *this; }

private:
    unsigned int no_;
    std::string name_;
    std::string author_;
    std::string pubdate_;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);
bool operator<(const Book&, const Book&);
bool operator>(const Book&, const Book&);
bool operator<=(const Book&, const Book&);
bool operator>=(const Book&, const Book&);

#endif // CP5_CH14_EX14_05_H
```
  
book_ex19.cpp
```cpp
#include "book_ex19.h"

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

bool operator<(const Book &lhs, const Book &rhs)
{
	return lhs.no_ < rhs.no_;
}

bool operator>(const Book &lhs, const Book &rhs)
{
	return rhs < lhs;
}

bool operator<=(const Book &lhs, const Book &rhs)
{
	return !(rhs < lhs);
}

bool operator>=(const Book &lhs, const Book &rhs)
{
	return !(lhs < rhs);
}
```
  
ex19.cpp
```cpp
#include "book_ex19.h"

int main()
{
    Book book1(123, "CP5", "Lippman", "2012");
    Book book2(123, "CP5", "Lippman", "2012");

    if (book1 == book2)
        std::cout << book1 << std::endl;
}
```

## 14.20
参见14.20。  

## 14.21
```cpp
Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    Sales_data old_data = *this;
    *this = old_data + rhs;
    return *this;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum;
    sum.units_sold = lhs.units_sold + rhs.units_sold;
    sum.revenue = lhs.revenue + rhs.revenue;
    return sum;
}
```
本题中+和+=都用到了临时变量。  

## 14.22
Sales_data_ex22.h
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
	Sales_data& operator=(const std::string&);
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

Sales_data& Sales_data::operator=(const std::string &s)
{
	*this = Sales_data(s);
	return *this;
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
  
ex22.cpp
```cpp
#include <iostream>
#include <string>
#include "Sales_data_ex22.h"

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

## 14.23
StrVec_ex23.h
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
	StrVec &operator=(std::initializer_list<std::string>);
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

StrVec &StrVec::operator=(std::initializer_list<std::string> il)
{
	auto data = alloc_n_copy(il.begin(), il.end());
	free();
	elements = data.first;
	first_free = cap = data.second;

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
  
ex23.cpp
```cpp
#include "StrVec_ex23.h"

int main()
{
	StrVec s({"aaa", "bbb"});

	return 0;
}
```

## 14.24
book_ex24.h
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
    friend bool operator<(const Book&, const Book&);
    friend bool operator>(const Book&, const Book&);
    friend bool operator<=(const Book&, const Book&);
    friend bool operator>=(const Book&, const Book&);

public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubdate):no_(no), name_(name), author_(author), pubdate_(pubdate) { }
    Book(std::istream &in) { in >> *this; }
    Book& operator=(const Book&);
    Book& operator=(const Book&&) noexcept;

private:
    unsigned int no_;
    std::string name_;
    std::string author_;
    std::string pubdate_;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);
bool operator<(const Book&, const Book&);
bool operator>(const Book&, const Book&);
bool operator<=(const Book&, const Book&);
bool operator>=(const Book&, const Book&);

#endif // CP5_CH14_EX14_05_H
```
  
book_ex24.cpp
```cpp
#include "book_ex24.h"

Book& Book::operator=(const Book &rhs)
{
        this->no_ = rhs.no_;
        this->name_ = rhs.name_;
        this->author_ = rhs.author_;
        this->pubdate_ = rhs.pubdate_;

    return *this;
}

Book& Book::operator=(const Book &&rhs) noexcept
{
    if(this != &rhs)
    {
        this->no_ = rhs.no_;
        this->name_ = rhs.name_;
        this->author_ = rhs.author_;
        this->pubdate_ = rhs.pubdate_;
    }

    return *this;
}

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

bool operator<(const Book &lhs, const Book &rhs)
{
	return lhs.no_ < rhs.no_;
}

bool operator>(const Book &lhs, const Book &rhs)
{
	return rhs < lhs;
}

bool operator<=(const Book &lhs, const Book &rhs)
{
	return !(rhs < lhs);
}

bool operator>=(const Book &lhs, const Book &rhs)
{
	return !(lhs < rhs);
}
```
  
ex24.cpp
```cpp
#include "book_ex24.h"

int main()
{
    Book book1(123, "CP5", "Lippman", "2012");
    Book book2(123, "CP5", "Lippman", "2012");

    if (book1 == book2)
        std::cout << book1 << std::endl;
}
```
  
## 14.25
参见14.24。  
  
## 14.26
StrBlob_ex26.h
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
	std::string& operator[](size_t n) { return (*data)[n]; }
	const std::string& operator[](size_t n) const { return (*data)[n]; }
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
  
ex26_2.cpp
```cpp
#include "StrBlob_ex26.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	StrBlob b2 = b1;

	return 0;
}
```
  
StrVec_ex26.h
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
  
ex26_2.cpp
```cpp
#include "StrVec_ex26.h"

int main()
{
	StrVec s({"aaa", "bbb"});

	return 0;
}
```
  
String_ex26.h
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
	char& operator[](size_t n) { return elements[n]; }
	const char& operator[](size_t n) const { return elements[n]; }
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
  
ex26_3.cpp
```cpp
#include "String_ex26.h"
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
  
## 14.27
StrBlob_ex27.h
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
	std::string& operator[](size_t n) { return (*data)[n]; }
	const std::string& operator[](size_t n) const { return (*data)[n]; }
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
	ConstStrBlobPtr &operator++();
	ConstStrBlobPtr &operator--();
	ConstStrBlobPtr operator++(int);
	ConstStrBlobPtr operator--(int);
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

ConstStrBlobPtr &ConstStrBlobPtr::operator++()
{
	check(curr, "increment past end of ConstStrBlobPtr");
	++curr;
	return *this;
}

ConstStrBlobPtr &ConstStrBlobPtr::operator--()
{
	--curr;
	check(curr, "decrement past begin of ConstStrBlobPtr");
	return *this;
}

ConstStrBlobPtr ConstStrBlobPtr::operator++(int)
{
	ConstStrBlobPtr ret = *this;
	++*this;
	return ret;
}

ConstStrBlobPtr ConstStrBlobPtr::operator--(int)
{
	ConstStrBlobPtr ret = *this;
	--*this;
	return ret;
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
  
ex27.cpp
```cpp
#include "StrBlob_ex27.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	StrBlob b2 = b1;

	return 0;
}
```
  
## 14.28
参见14.27。
  
## 14.29
const的StrBlob不能改变成员变量，而递增和递减运算符需要改变其状态，本身就是矛盾的。
  
## 14.30
>为你的StrBlob类和在12.1.6节练习12.22中定义的ConstStrBlobPtr类分别添加解引用运算符和箭头运算符。注意：因为ConstStrBlobPtr的数据成员指向const vector，所以ConstStrBlobPtr中的运算符必须返回常量引用。

StrBlob_ex30.h
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
	std::string& operator[](size_t n) { return (*data)[n]; }
	const std::string& operator[](size_t n) const { return (*data)[n]; }
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
	ConstStrBlobPtr &operator++();
	ConstStrBlobPtr &operator--();
	ConstStrBlobPtr operator++(int);
	ConstStrBlobPtr operator--(int);
	const std::string &operator*() const
	{
		auto p = check(curr, "dereference past end");
		return (*p)[curr];
	}
	const std::string *operator->() const
	{
		return &this->operator*();
	}
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

ConstStrBlobPtr &ConstStrBlobPtr::operator++()
{
	check(curr, "increment past end of ConstStrBlobPtr");
	++curr;
	return *this;
}

ConstStrBlobPtr &ConstStrBlobPtr::operator--()
{
	--curr;
	check(curr, "decrement past begin of ConstStrBlobPtr");
	return *this;
}

ConstStrBlobPtr ConstStrBlobPtr::operator++(int)
{
	ConstStrBlobPtr ret = *this;
	++*this;
	return ret;
}

ConstStrBlobPtr ConstStrBlobPtr::operator--(int)
{
	ConstStrBlobPtr ret = *this;
	--*this;
	return ret;
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
  
ex30.cpp
```cpp
#include "StrBlob_ex30.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	StrBlob b2 = b1;

	return 0;
}
```
  
## 14.31
>我们的StrBlobPtr类没有定义拷贝构造函数、赋值运算符和析构函数，为什么？

StrBlobPtr的数据成员的类型为std::weak_ptr<std::vector<std::string>>和内置类型，前者有自己的三个函数，后者也无需定义，使用默认的即可。
  
## 14.32
>定义一个类令其含有指向StrBlobPtr对象的指针，为这个类定义重载的建投运算符。

```cpp
class MyClass
{
public:
	std::string* operator->() const
	{
		return ptr->operator->();
	}
private:
	StrBlobPtr *ptr;
}
```
  
## 14.33
>一个重载的函数调用运算符应该接受几个运算对象？

可以接受的对象为0-256个。

## 14.34
>定义一个函数对象类，令其执行if-then-else的操作：该类的调用运算符接受三个形参，它首先检查第一个形参，如果成功返回第二个形参的值，如果不成功返回第三个形参的值。

```cpp
#include <string>
#include <iostream>

using std::string;

struct if_then_else
{
	string operator()(bool b, string first_result, string second_result)
	{
		return b ? first_result : second_result;
	}
};

int main()
{
	if_then_else if_object;
	std::cout << if_object(true, "aaa", "bbb") << std::endl;

	return 0;
}
```
  
## 14.35
>编写一个类似PrintString的类，令其从istream中读取一行输入，然后返回一个表示我们所读内容的string。如果读取失败，返回空string。

```cpp
#include <string>
#include <iostream>

using std::string;

class ReadString
{
public:
	ReadString(std::istream &i = std::cin) : is(i) {}
	const string &operator()()
	{
		is >> s;
		return s;
	}
private:
	std::istream &is;
	string s;
};

int main()
{
	ReadString ReadObject;
	std::cout << ReadObject() << std::endl;

	return 0;
}
```
  
## 14.36
>使用前一个练习定义的类读取标准输入，将每一行保存为vector的一个元素。

```cpp
#include <string>
#include <iostream>
#include <vector>

using std::string;

class ReadString
{
public:
	ReadString(std::istream &i = std::cin) : is(i) {}
	string operator()()
	{
		std::string s;
		std::getline(is, s);
		return s;
	}
private:
	std::istream &is;
};

int main()
{
	std::vector<string> vs;
	string new_string;
	ReadString ReadObject;
	
	do{
		new_string = ReadObject();
		vs.push_back(new_string);
	}while(!new_string.empty());

	for(auto s : vs)
		std::cout << s << " ";
	std::cout << std::endl;

	return 0;
}
```
  
## 14.37
>编写一个类令其检查两个值是否相等。使用该对象及标准库算法编写程序，令其替换某个序列中具有给定值的所有实例。

```cpp
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class equal_int
{
public:
	equal_int(int i) : default_number(i) {}
	bool operator()(int ele) { return default_number == ele; }
private:
	int default_number;
};

int main()
{
	std::vector<int> vi = {1,2,3,3,4,3,5};

	std::replace_if(vi.begin(), vi.end(), equal_int(3), 5);

	for(int i : vi)
		std::cout << i << " ";
	std::cout << std::endl;

	return 0;
}
```
  
## 14.38
```cpp
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class CompareString
{
public:
	CompareString(size_t n) : default_size(n) {};
	bool operator()(const std::string &s) const
	{
		return default_size == s.size();
	}
private:
	size_t default_size;
};

int main()
{
	std::ifstream ifs("../ch09_Sequential_Containers/letter.txt");
    if (!ifs) return -1;

    std::vector<std::string> vs;

    for(std::string curr; ifs >> curr; vs.push_back(curr));

    for(int i = 1, n = 0; i < 11; ++i)
    {
    	for(auto iter = vs.begin(); iter != vs.end(); )
    	{
    		iter = std::find_if(iter+1, vs.end(), CompareString(i));
    		if(iter != vs.end()) ++n;
    	}
    	std::cout << "length:" << i << "," << n << std::endl;
    	n = 0;
    }
    	

	return 0;
}
```
  
## 14.39
```cpp
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class CompareString
{
public:
	CompareString(size_t n) : default_size(n) {};
	bool operator()(const std::string &s) const
	{
		return default_size == s.size();
	}
private:
	size_t default_size;
};

int main()
{
	std::ifstream ifs("../ch09_Sequential_Containers/letter.txt");
    if (!ifs) return -1;

    std::vector<std::string> vs;

    for(std::string curr; ifs >> curr; vs.push_back(curr));

    int n = 0;
    for(int i = 1; i < 10; ++i)
    {
    	for(auto iter = vs.begin(); iter != vs.end(); )
    	{
    		iter = std::find_if(iter+1, vs.end(), CompareString(i));
    		if(iter != vs.end()) ++n;
    	}
    }
    std::cout << "length:1-9" << "," << n << std::endl;
    	
    n = 0;
    for(int i = 10; i < 30; ++i)
    {
        for(auto iter = vs.begin(); iter != vs.end(); )
        {
            iter = std::find_if(iter+1, vs.end(), CompareString(i));
            if(iter != vs.end()) ++n;
        }
    }
    std::cout << "length:1-9" << "," << n << std::endl;

	return 0;
}
```

## 14.40
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class bigger
{
public:
	bigger(vector<string>::size_type i) : default_num(i) {};
	bool operator()(const std::string &s)
	{
		return s.size() >= default_num;
	}
private:
	vector<string>::size_type default_num;
};

class str_compare
{
public:
	bool operator()(const std::string &lhs, const std::string &rhs)
	{
		return lhs.size() < rhs.size();
	}	
};

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

		// [](const string &a, const string &b)
		// 	{ return a.size() < b.size(); }
void biggies(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(), str_compare());
	auto wc = find_if(words.begin(), words.end(), bigger(sz));
	auto count = words.end() - wc;
	cout << count << endl;
	for(const auto s : words)
		cout << s << " ";
	cout << endl;
}
// [sz](const string &a)
// 			{ return a.size() >= sz; }
int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	biggies(vs, 5);

	return 0;
}
```
  
## 14.41
当传递的函数使用次数少且实现简单时，使用lambda；反之则使用类。  
  
## 14.42
```cpp
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<int> vi = {1025, 1024, 1, 2, 2000};
	std::vector<std::string> vs = {"pooh", "abc", "123"};
	std::vector<int> vi2 = {1, 3, 4, 5, 6};

	std::cout << std::count_if(vi.begin(), vi.end(), std::bind(std::greater<int>(), std::placeholders::_1, 1024)) << std::endl;

	std::cout << *(std::find_if(vs.begin(), vs.end(), std::bind(std::not_equal_to<std::string>(), std::placeholders::_1, "pooh"))) << std::endl;

	std::transform(vi2.begin(), vi2.end(), vi.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));

	for(const auto i : vi)
		std::cout << i << " ";
	std::cout << std::endl;

	return 0;
}
```
  
## 14.43
```cpp
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>

int main()
{
	std::vector<int> vi = {1025, 1024, 1, 2, 2000};
	std::vector<std::string> vs = {"pooh", "abc", "123"};
	std::vector<int> vi2 = {1, 3, 4, 5, 6};

	std::cout << std::count_if(vi.begin(), vi.end(), std::bind(std::greater<int>(), std::placeholders::_1, 1024)) << std::endl;

	std::cout << *(std::find_if(vs.begin(), vs.end(), std::bind(std::not_equal_to<std::string>(), std::placeholders::_1, "pooh"))) << std::endl;

	std::transform(vi2.begin(), vi2.end(), vi.begin(), std::bind(std::multiplies<int>(), std::placeholders::_1, 2));

	for(const auto i : vi)
		std::cout << i << " ";
	std::cout << std::endl;

	return 0;
}
```
  
## 14.44
```cpp
#include <string>
#include <iostream>
#include <algorithm>
#include <map>

int add(int i, int j) { return i + j; }

int main()
{
	
	auto mod = [](int i, int j) { return i % j; };
	struct divide
	{
		int operator()(int dividend, int divisor)
		{
			return dividend / divisor;
		}
	};
	std::map<std::string, std::function<int(int, int)>> binops = {
		{"+", add},
		{"-", std::minus<int>()},
		{"/", divide()},
		{"*", [](int i, int j) { return i * j; }},
		{"%", mod}
	};

	std::cout << binops["+"](10, 5) << std::endl;
	std::cout << binops["-"](10, 5) << std::endl;
	std::cout << binops["*"](10, 5) << std::endl;
	std::cout << binops["/"](10, 5) << std::endl;
	std::cout << binops["%"](10, 5) << std::endl;

	return 0;
}
```
  
## 14.45
转换成string的返回值应该是bookNo；转换成double的返回值应该是revenue。
  
## 14.46
不应该，类类型与转换类型之间不存在明显的映射关系，这样的类型转换可能具有误导性。应该声明成explicit，可以防止异常发生。
  
## 14.47
前者没什么意义，会被编译器忽略；后者不能改变对象。
  
## 14.48
应该含有向bool的类型转换运算符，应该是explicit，可以防止自动转换。
  
## 14.49
book_ex49.h
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
    friend bool operator<(const Book&, const Book&);
    friend bool operator>(const Book&, const Book&);
    friend bool operator<=(const Book&, const Book&);
    friend bool operator>=(const Book&, const Book&);

public:
    Book() = default;
    Book(unsigned no, std::string name, std::string author, std::string pubdate):no_(no), name_(name), author_(author), pubdate_(pubdate) { }
    Book(std::istream &in) { in >> *this; }
    Book& operator=(const Book&);
    Book& operator=(const Book&&) noexcept;
    explicit operator bool() { return !(name_.empty()); }

private:
    unsigned int no_;
    std::string name_;
    std::string author_;
    std::string pubdate_;
};

std::istream& operator>>(std::istream&, Book&);
std::ostream& operator<<(std::ostream&, const Book&);
bool operator==(const Book&, const Book&);
bool operator!=(const Book&, const Book&);
bool operator<(const Book&, const Book&);
bool operator>(const Book&, const Book&);
bool operator<=(const Book&, const Book&);
bool operator>=(const Book&, const Book&);

#endif // CP5_CH14_EX14_05_H
```
  
book_ex49.cpp
```cpp
#include "book_ex49.h"

Book& Book::operator=(const Book &rhs)
{
        this->no_ = rhs.no_;
        this->name_ = rhs.name_;
        this->author_ = rhs.author_;
        this->pubdate_ = rhs.pubdate_;

    return *this;
}

Book& Book::operator=(const Book &&rhs) noexcept
{
    if(this != &rhs)
    {
        this->no_ = rhs.no_;
        this->name_ = rhs.name_;
        this->author_ = rhs.author_;
        this->pubdate_ = rhs.pubdate_;
    }

    return *this;
}

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

bool operator<(const Book &lhs, const Book &rhs)
{
	return lhs.no_ < rhs.no_;
}

bool operator>(const Book &lhs, const Book &rhs)
{
	return rhs < lhs;
}

bool operator<=(const Book &lhs, const Book &rhs)
{
	return !(rhs < lhs);
}

bool operator>=(const Book &lhs, const Book &rhs)
{
	return !(lhs < rhs);
}
```
  
ex49.cpp

```cpp
#include "book_ex49.h"

int main()
{
    Book book1(123, "CP5", "Lippman", "2012");
    Book book2(123, "CP5", "Lippman", "2012");

    if (book1 == book2)
        std::cout << book1 << std::endl;
}
```
  
## 14.50
>在初始化ex1和ex2的过程中，可能用到哪些类类型的转换序列呢？说明初始化是否正确并解释原因。

前者转换具有二义性，可能用到operator double()和operator float()；后者正确。
  
## 14.51
>在调用calc的过程中，可能用到哪些类型转换序列呢？说明最佳可行函数是如何被选出来的。

void calc(int);
实参类型转换到形参类型有如下几个等级：
1.精确匹配；
2.通过const转换实现匹配；
3.通过类型提升实现的匹配；
4.通过算数类型转换或指针转换实现的匹配；
5.通过类类型转换实现的匹配。
详见6.6.1实参类型转换。
  
## 14.52
>在下面的加法表达式中分别选用了哪个operator+？列出候选函数、可行函数以及为每个可行函数的实参执行的类型转换。

operator+(int, double)<built-in>
 SmallInt->int,LongDouble->double
operator+(int, float)<built-in>
 SmallInt->int,LongDouble->float
SmallInt operator+(const SmallInt&, const SmallInt&)
 编译器只能执行一个用户定义的类型转换。
上述加法表达式具有二义性。
  
LongDouble operator(const SmallInt&)
 精确匹配
operator+(double, int)<built-in>
 LongDouble->double，SmallInt->int
operator+(float, int) <built-in>
 LongDouble->float，SmallInt->int
  
## 14.53
>假设我们已经定义了如522页的SmallInt，判断下面的加法表达式是否合法。如果合法，使用了哪个加法运算符？如果不合法，应该怎样修改代码使其合法？

```cpp
#include <cstddef>

class SmallInt
{
friend SmallInt operator+(const SmallInt &si1, const SmallInt &si2) { SmallInt si_sum(si1.val + si2.val); return si_sum; }
public:
	SmallInt(int i = 0) : val(i) {}
	operator int() const { return val; }
private:
	std::size_t val;
};

int main()
{
	SmallInt s1;
	// double d = s1 + 3.14;
	double d1 = s1 + SmallInt(3.14);
	double d2 = s1.operator int() + 3.14;

	return 0;
}
```