## 18.1
（a）range_error；  
（b）exception。  
throw p，此时抛出的为指向局部对象的指针，我们几乎可以肯定这是一种错误行为。  
  
## 18.2
p的内存将不会被释放，会出现内存泄漏。  
  
## 18.3
使用shared_ptr；自己写个类来实现。  
```cpp
std::shared_ptr<int> p(new int[v.size()], [](int *p) {delete p});
```
```cpp
struct P {
	int *p = nullptr;
	P(std::size_t n):p(new int[n]){}
	~P()
	{
		delete []p;
	}
};
```
  
## 18.4
应该把继承链最底端的类放在前面，而将继承链最顶端的类放在后面。  
```cpp
try{
	//使用C++标准库
}catch(overflow_error eobj){
	//...
}catch(const runtime_error &re){
	//...
}catch(exception){
	//...
}
```
  
## 18.5
```cpp
#include <exception>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <typeinfo>

using namespace std;

int main()
{
	try{
		//使用C++标准库
	}catch(bad_cast &r){
		cout << r.what();
		abort();
	}catch(range_error &r){
		cout << r.what();
		abort();
	}catch(underflow_error &r){
		cout << r.what();
		abort();
	}catch(overflow_error &r){
		cout << r.what();
		abort();
	}catch(runtime_error &r){
		cout << r.what();
		abort();
	}catch(length_error &r){
		cout << r.what();
		abort();
	}catch(out_of_range &r){
		cout << r.what();
		abort();
	}catch(invalid_argument &r){
		cout << r.what();
		abort();
	}catch(domain_error &r){
		cout << r.what();
		abort();
	}catch(logic_error &r){
		cout << r.what();
		abort();
	}catch(bad_alloc &r){
		cout << r.what();
		abort();
	}catch(exception &r){
		cout << r.what();
		abort();
	}

	return 0;
}
```
  
## 18.6
（a）
```cpp
exceptionType *pet;
//...
throw pet;
```
（b）
 可以捕获所有的异常。  
（c）
```cpp
int a;
//...
throw a;
```
  
## 18.7
```cpp
template <typename T>
Blob<T>::Blob()try :data(std::make_shared<vector<T>()>) {}
catch(const std::bad_alloc &e){
	handle_out_of_memory(e);
}
template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) try :data(make_shared<vector<T>>(il)) {}
catch(const std::bad_alloc &e){
	handle_out_of_memory(e);
}
```
```cpp
template <typename T>
BlobPtr<T>::BlobPtr()try:curr(0){}
catch (const std::bad_alloc& e) {
	handle_out_of_memory(e);
}
template <typename T>
BlobPtr<T>::BlobPtr(Blob<T> &a, size_t sz = 0)try : wptr(a.data), curr(sz) {}
catch (const std::bad_alloc& e) {
	handle_out_of_momory(e);
}
```
  
## 18.8
略。  
  
## 18.9
Sales_data.h
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>
#include <stdexcept>

class isbn_mismatch : public std::logic_error
{
public:
	explicit isbn_mismatch(const std::string &s) : std::logic_error(s) { }
	isbn_mismatch(const std::string &s, const std::string &lhs, const std::string &rhs) :
		std::logic_error(s), left(lhs), right(rhs) { }
	const std::string left, right;
};

struct Sales_data;

std::istream &operator>>(std::istream &is, Sales_data &item);
std::ostream &operator<<(std::ostream &os, const Sales_data &item);
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);

struct Sales_data
{
friend std::istream& operator>>(std::istream&, Sales_data&);
friend std::ostream& operator<<(std::ostream&, const Sales_data&);
friend Sales_data operator+(const Sales_data&, const Sales_data&);
friend bool operator==(const Sales_data&, const Sales_data&);
friend class std::hash<Sales_data>;
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
	if(isbn() != rhs.isbn())
		throw isbn_mismatch("wrong isbns", isbn(), rhs.isbn());
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

bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() == rhs.isbn() && 
		lhs.units_sold == rhs.units_sold && 
		lhs.revenue == rhs.revenue;
}

#endif
```
  
ex09.cpp
```cpp
#include <iostream>
#include <string>
#include "Sales_data.h"
#include <unordered_set>
#include <algorithm>
#include <utility>

namespace std
{
	template <>
	struct hash<Sales_data>
	{
		typedef size_t result_type;
		typedef Sales_data argument_type;
		size_t operator()(const Sales_data &s) const;
	};
	size_t hash<Sales_data>::operator()(const Sales_data &s) const
	{
		return hash<std::string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
	}
}

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}

struct matches
{
	std::vector<Sales_data>::size_type index;
	std::vector<Sales_data>::const_iterator first;
	std::vector<Sales_data>::const_iterator last;
	matches(std::vector<Sales_data>::size_type index_, std::vector<Sales_data>::const_iterator first_, std::vector<Sales_data>::const_iterator last_) : index(index_), first(first_), last(last_) {}
};

std::vector<matches> findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book)
{
	std::vector<matches> ret;
	for(auto it = files.cbegin(); it != files.cend(); ++it)
	{
		auto found = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);
		if(found.first != found.second)
			ret.push_back(matches(it - files.cbegin(), found.first, found.second));
	}
	return ret;
}

void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
	std::string s;
	while(in >> s)
	{
		auto trans = findBook(files, s);
		if(trans.empty())
		{
			std::cout << s << " not found in any stores" << std::endl;
			continue;
		}
		for(const auto &store : trans)
			os << "store " << store.index << " sales: " << std::accumulate(store.first, store.last, Sales_data(s)) << std::endl;
	}
}

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2("001-01", 2, 100);
    Sales_data sales_data3("001-02", 2, 80);

    try{
    	auto sum = sales_data1 + sales_data3;
    }catch(const isbn_mismatch &e){
    	std::cerr << e.what() << ": left isbn(" << e.left << ") right isbn(" << e.right << ")" << std::endl;
    }
    return 0;
}
```
  
## 18.10
程序详见18.9，出现一个未被捕获的异常时，程序将会执行terminate。  
  
## 18.11
what中如果抛出异常，需要try catch捕获，再调用what，一直循环，直达内存耗尽。  
  
## 18.12
Query.h  
```cpp
#ifndef QUERY_H_
#define QUERY_H_

#include <string>
#include <iostream>
#include "Query_base.h"
#include "WordQuery.h"
#include "TextQuery.h"

namespace chapter15
{
	class Query
	{
		friend Query operator~(const Query&);
		friend Query operator|(const Query&, const Query&);
		friend Query operator&(const Query&, const Query&);
	public:
		Query(const std::string&);
		chapter10::QueryResult eval(const chapter10::TextQuery &t) const { return q->eval(t); }
		std::string rep() const { std::cout << "Query::rep()" << std::endl; return q->rep(); }
	private:
		Query(std::shared_ptr<Query_base> query) : q(query) { std::cout << "Query(std::shared_ptr<Query_base> query)" << std::endl; }
		std::shared_ptr<Query_base> q;
	};

	std::ostream& operator<<(std::ostream &os, const Query &query)
	{
		return os << query.rep();
	}

	inline Query::Query(const std::string &s) : q(new WordQuery(s)) { std::cout << "Query::Query(const std::string &s)" << std::endl; }
}

#endif
```
  
TextQuery.h
```cpp
#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "StrBlob.h"

namespace chapter10
{
	class QueryResult;

	class TextQuery
	{
	public:
		using line_no = std::vector<std::string>::size_type;
		TextQuery(std::ifstream&);
		QueryResult query(const std::string&) const;
	private:
		StrBlob file;
		std::map<std::string, std::shared_ptr<std::set<line_no>>> word_map;
	};

	class QueryResult
	{
		friend std::ostream& print(std::ostream&, const QueryResult&);
	public:
		QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, StrBlob f) : sought(s), lines(p), file(f) { }
		std::set<StrBlob::size_type>::iterator begin() const { return lines->begin(); }
		std::set<StrBlob::size_type>::iterator end() const { return lines->end(); }
		// std::shared_ptr<StrBlob> get_file() const { return std::make_shared<StrBlob>(file); }
		const StrBlob& get_file() const { return file; }
	private:
		std::string sought;
		std::shared_ptr<std::set<TextQuery::line_no>> lines;
		StrBlob file;
	};

	TextQuery::TextQuery(std::ifstream &ifs)
	{
		std::string text_line;

		while(std::getline(ifs, text_line))
		{
			file.push_back(text_line);
			int line_number = file.size() - 1;
			std::istringstream line(text_line);
			std::string text_word;
			while(line >> text_word)
			{
				std::string word;
				std::copy_if(text_word.begin(), text_word.end(), std::back_inserter(word), isalpha);
				// std::cout << word << std::endl;
				auto &wm_lines = word_map[word];
				if(!wm_lines)
					wm_lines.reset(new std::set<line_no>);
				wm_lines->insert(line_number);
			}
		}
	}

	QueryResult TextQuery::query(const std::string &sought) const
	{
		static std::shared_ptr<std::set<TextQuery::line_no>> nodata(new std::set<TextQuery::line_no>);
		auto loc = word_map.find(sought);
		if(loc == word_map.end())
			return QueryResult(sought, nodata, file);
		else
			return QueryResult(sought, loc->second, file);
	}

	std::ostream &print(std::ostream &os, const QueryResult &qr)
	{
		os << qr.sought << " occurs " << qr.lines->size() << " " /*<< make_plural(qr.lines->size(), "time", "s")*/ << std::endl;
		for(auto num : *qr.lines)
		{
			ConstStrBlobPtr p(qr.file, num);
			os << "\t(line " << num + 1 << ") " << p.deref() << std::endl;
		}
			
		return os;
	}
}

#endif
```
  
## 18.13
在需要在其所在的文件中可见，在其所在的文件外不可见时；  
static只能用于变量与函数，不可用于用户自定义的类型。  
  
## 18.14
```cpp
mathLib::MatrixLib::matrix mathLib::MatrixLib::operator*(const matrix&, const matrix&);
```
  
## 18.15
using指示引入的名字的作用域远比using声明引入的名字的作用域复杂。它具有将命名空间成员提升到包含命名空间本身和using指示的最近作用域的能力。对于using声明来说，我们指示简单地领名字在局部作用域有效。using指示是令整个命名空间的所有内容变得有效。通常情况下，命名空间中会含有一些不能出现在局部作用域的定义，因此using指示一般被看作是出现在最近的外层作用域中。  
  
## 18.16
```cpp
namespace Exercise{
	int ivar = 0;
	double dvar = 0;
	const int limit = 1000;
}
int ivar = 0;

using Exercise::ivar;	//1
using Exercise::dvar;
using Exercise::limit;

// using namespace Exercise;	//3

void mainp(){
	// using Exercise::ivar;	//2
	// using Exercise::dvar;
	// using Exercise::limit;

	// using namespace Exercise;	//4

	double dvar = 3.1416;
	int iobj = limit + 1;
	++ivar;
	++::ivar;
}

int main()
{
	return 0;
}
```
  
## 18.18
