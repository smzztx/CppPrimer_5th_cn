## 12.1
b1包含4个元素；  
b2被销毁。  

## 12.2
strblob.h
```cpp
#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <string>
#include <initializer_list>
#include <memory>
#include <vector>
#include <stdexcept>

class StrBlob
{
public:
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();
	std::string& front();
	std::string& back();
	const std::string& front() const;
	const std::string& back() const;
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const;
};

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)){}

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

#endif
```
ex02.cpp
```cpp
#include "StrBlob.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	const StrBlob b2 = {"a", "b", "c"};

	std::cout << b1.back() << std::endl;
	std::cout << b2.back() << std::endl;

	return 0;
}
```

## 12.03
不需要，添加进去虽然编译器不会报错，但是这样不符合类使用者的使用习惯。  

## 12.04
可以忽略，本身i就是大于0的。  

## 12.05
使用explicit之后  
优点：我们可以清楚地知道使用的是哪种类型；  
缺点：不易使用，需要显示地初始化。  

## 12.06
```cpp
#include <string>
#include <iostream>
#include <vector>

std::vector<int> *create_vi()
{
	return new std::vector<int>;
}

void push_vi(std::vector<int> *p)
{
	int i;
	while(std::cin >> i)
		p->push_back(i);
}

void print_vi(std::vector<int> *p)
{
	for(const auto i : (*p))
		std::cout << i << std::endl;
}

int main()
{
	auto p = create_vi();
	push_vi(p);
	print_vi(p);
	delete p;

	return 0;
}
```

## 12.07
```cpp
#include <string>
#include <iostream>
#include <vector>
#include <memory>

std::shared_ptr<std::vector<int>> create_vi()
{
	return std::make_shared<std::vector<int>>();
}

void push_vi(std::shared_ptr<std::vector<int>> p)
{
	int i;
	while(std::cin >> i)
		p->push_back(i);
}

void print_vi(std::shared_ptr<std::vector<int>> p)
{
	for(const auto i : (*p))
		std::cout << i << std::endl;
}

int main()
{
	auto p = create_vi();
	push_vi(p);
	print_vi(p);
	// delete p;

	return 0;
}
```

## 12.08
指针p被转换成bool值，new的内存没有被delete，内存没有被释放。  

## 12.09
r=q后r所指的内存没有释放，应该先delete r，再r=q；  
第二段代码内存会自动释放。  

## 12.10
正确。

## 12.11
离开process时，p指向的内存会被释放，再使用p指针时会出现错误。  

## 12.12
（a）合法，将智能指针赋值给process；  
（b）不合法，shared_ptr初始化内置指针时需要使用直接初始化的形式；  
（c）不合法，shared_ptr初始化内置指针时需要使用直接初始化的形式；  
（d）合法。  

## 12.13
sp和p指向的是同一个内存，释放了p所指向的内存后，再使用sp调用对象时可能会出错。  

## 12.14
```cpp
#include <string>
#include <memory>
#include <iostream>

struct destination
{
    std::string des;
    destination(std::string des_) : des(des_){}
};

struct connection
{
    std::string conn;
    connection(std::string conn_) : conn(conn_){}
};

connection connect(destination *des_)
{
    std::cout << "connect to " << des_->des << std::endl;
    return connection (des_->des);
}

void disconnect(connection conn_)
{
    std::cout << "disconnect " << conn_.conn << std::endl;
}

void end_connection(connection *p){ disconnect(*p); }

void f(destination &d)
{
    connection c = connect(&d);
    std::shared_ptr<connection> p(&c, end_connection);
    std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}

int main()
{
    destination des("aaa");
    f(des);

    return 0;
}
```

## 12.15
```cpp
#include <string>
#include <memory>
#include <iostream>

struct destination
{
    std::string des;
    destination(std::string des_) : des(des_){}
};

struct connection
{
    std::string conn;
    connection(std::string conn_) : conn(conn_){}
};

connection connect(destination *des_)
{
    std::cout << "connect to " << des_->des << std::endl;
    return connection (des_->des);
}

void disconnect(connection conn_)
{
    std::cout << "disconnect " << conn_.conn << std::endl;
}

void end_connection(connection *p){ disconnect(*p); }

void f(destination &d)
{
    connection c = connect(&d);
    std::shared_ptr<connection> p(&c, [](connection *p){ disconnect(*p); });
    std::cout << "connecting now(" << p.use_count() << ")" << std::endl;
}

int main()
{
    destination des("aaa");
    f(des);

    return 0;
}
```

## 12.16
```cpp
#include <memory>
#include <iostream>

int main()
{
	std::unique_ptr<int> up1(new int(1));
	// std::unique_ptr<int> up2(up1);
	// std::unique_ptr<int> up2 = up1;
	std::unique_ptr<int> up2;
	up2.reset(up1.release());
	std::cout << *up2 << std::endl;

	return 0;
}
```
```sh
$ g++ -o ex16 ex16.cpp -std=c++11
ex16.cpp: In function ‘int main()’:
ex16.cpp:6:30: error: use of deleted function ‘std::unique_ptr<_Tp, _Dp>::unique_ptr(const std::unique_ptr<_Tp, _Dp>&) [with _Tp = int; _Dp = std::default_delete<int>]’
  std::unique_ptr<int> up2(up1);
                              ^
In file included from /usr/include/c++/4.8/memory:81:0,
                 from ex16.cpp:1:
/usr/include/c++/4.8/bits/unique_ptr.h:273:7: error: declared here
       unique_ptr(const unique_ptr&) = delete;
       ^
```

## 12.17
（a）非法，初始化错误；  
（b）编译时合法，运行时会报错，因为pi不是new出来的，销毁时使用默认的delete会出错；  
（c）编译时合法，但是运行时会导致空悬指针，unique_ptr释放空间时，使用pi2指针会出错；  
（d）编译时合法，运行时会报错，因为指针不是new出来的，销毁时使用默认的delete会出错；  
（e）合法；  
（f）编译时合法，但是会导致两次delete或者一个delete后另一个变为空悬指针。  

## 12.18
多个shared_ptr可以指向同一个对象，直接赋值即可，无需release成员。  

## 12.19
StrBlob_ex19.h
```cpp
#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <string>
#include <initializer_list>
#include <memory>
#include <vector>
#include <stdexcept>

class StrBlobPtr;

class StrBlob
{
public:
	friend class StrBlobPtr;
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();
	std::string& front();
	std::string& back();
	const std::string& front() const;
	const std::string& back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const;
};

class StrBlobPtr
{
public:
	StrBlobPtr() : curr(0){};
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	std::string& deref() const;
	StrBlobPtr& incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
};

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
	auto ret = wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if(i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

std::string& StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)){}

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

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end()
{
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

#endif
```
ex19.cpp
```cpp
#include "StrBlob_ex19.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	StrBlobPtr p1(b1);

	std::cout << p1.deref() << std::endl;
	p1.incr();
	std::cout << p1.deref() << std::endl;
	p1.incr();
	std::cout << p1.deref() << std::endl;
	p1.incr();
	// std::cout << p1.deref() << std::endl;

	return 0;
}
```

## 12.20
StrBlob_ex20.h
```cpp
#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <string>
#include <initializer_list>
#include <memory>
#include <vector>
#include <stdexcept>

class StrBlobPtr;

class StrBlob
{
public:
	friend class StrBlobPtr;
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t) { data->push_back(t); }
	void pop_back();
	std::string& front();
	std::string& back();
	const std::string& front() const;
	const std::string& back() const;
	StrBlobPtr begin();
	StrBlobPtr end();
private:
	std::shared_ptr<std::vector<std::string>> data;
	void check(size_type i, const std::string &msg) const;
};

class StrBlobPtr
{
public:
	StrBlobPtr() : curr(0){};
	StrBlobPtr(StrBlob &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	bool operator!=(const StrBlobPtr& p) { return p.curr != curr; }
	std::string& deref() const;
	StrBlobPtr& incr();
private:
	std::shared_ptr<std::vector<std::string>> check(std::size_t, const std::string&) const;
	std::weak_ptr<std::vector<std::string>> wptr;
	std::size_t curr;
};

std::shared_ptr<std::vector<std::string>> StrBlobPtr::check(std::size_t i, const std::string &msg) const
{
	auto ret = wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound StrBlobPtr");
	if(i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

std::string& StrBlobPtr::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

StrBlobPtr& StrBlobPtr::incr()
{
	check(curr, "increment past end of StrBlobPtr");
	++curr;
	return *this;
}

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()){}
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)){}

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

StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }

StrBlobPtr StrBlob::end()
{
	auto ret = StrBlobPtr(*this, data->size());
	return ret;
}

#endif
```
ex20.cpp
```cpp
#include "StrBlob_ex20.h"
#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream f("../ch08_The_IO_Library/data");
	StrBlob b1;

	for(std::string s;std::getline(f, s);)
		b1.push_back(s);

	for(StrBlobPtr beg = StrBlobPtr(b1.begin()), ed = StrBlobPtr(b1.end()); beg != ed; beg.incr())
		std::cout << beg.deref() << std::endl;

	return 0;
}
```

## 12.21
之前的版本更好，更容易读懂。

## 12.22
StrBlob_ex22.h
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
public:
	friend class ConstStrBlobPtr;
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const std::string &t) { data->push_back(t); }
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

#endif
```
ex22.cpp
```cpp
#include "StrBlob_ex22.h"
#include <iostream>

int main()
{
	const StrBlob b1 = {"a", "an", "the"};
	ConstStrBlobPtr p1(b1);

	std::cout << p1.deref() << std::endl;
	p1.incr();
	std::cout << p1.deref() << std::endl;
	p1.incr();
	std::cout << p1.deref() << std::endl;
	p1.incr();
	// std::cout << p1.deref() << std::endl;

	return 0;
}
```

## 12.23
ex23_1.cpp
```cpp
#include <string>
#include <iostream>
#include <cstring>

int main()
{
	const char a[] = "aaa";
	const char b[] = "bbb";
	char *pca = new char[strlen("aaa" "bbb")+1];

	std::strcat(pca, a);
	std::strcat(pca, b);
	std::cout << std::string(pca) << std::endl;
	delete [] pca;

	return 0;
}
```
ex23_2.cpp
```cpp
#include <string>
#include <iostream>
#include <cstring>

int main()
{
	std::string a = "aaa";
	std::string b = "bbb";
	std::string *ps = new std::string;

	*ps = a + b;
	std::cout << *ps << std::endl;
	delete ps;

	return 0;
}
```

## 12.24
```cpp
//
//  ex12_24.cpp
//  Exercise 12.24
//
//  Created by pezy on 12/30/14.
//
//  Write a program that reads a string from the standard input into a dynamically allocated character array.
//  Describe how your program handles varying size inputs.
//  Test your program by giving it a string of data that is longer than the array size you've allocated.


#include <iostream>

int main()
{
    // need to tell the size.
    std::cout << "How long do you want the string? ";
    int size{ 0 };
    std::cin >> size;
    char *input = new char[size+1]();
    std::cin.ignore();
    std::cout << "input the string: ";
    std::cin.get(input, size+1);
    std::cout << input;
    delete [] input;
    // Test: if longer than the array size, we will lost the characters which are out of range.
}
```

## 12.25
```cpp
delete [] pa;
```

## 12.26
```cpp
#include <iostream>
#include <string>
#include <memory>

int main()
{
    std::allocator<std::string> alloc;
    auto const p = alloc.allocate(5);
    auto q = p;
    alloc.construct(q++);
    alloc.construct(q++, 10, 'c');
    alloc.construct(q++, "hi");
    
    while(q != p)
    {
        std::cout << *(--q) << std::endl;
        alloc.destroy(q);
    }
    alloc.deallocate(p, 5);

    return 0;
}
```

## 12.27
TextQuery_ex27.h
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

class QueryResult;

class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	std::shared_ptr<std::vector<std::string>> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, std::shared_ptr<std::vector<std::string>> f) : sought(s), lines(p), file(f) { }
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	std::shared_ptr<std::vector<std::string>> file;
};

TextQuery::TextQuery(std::ifstream &ifs) : file(new std::vector<std::string>)
{
	std::string text;

	while(std::getline(ifs, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		std::istringstream line(text);
		std::string text;
		while(line >> text)
		{
			std::string word;
			std::copy_if(text.begin(), text.end(), std::back_inserter(word), isalpha);
			// std::cout << word << std::endl;
			auto &lines = wm[word];
			if(!lines)
				lines.reset(new std::set<line_no>);
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<TextQuery::line_no>> nodata(new std::set<TextQuery::line_no>);
	auto loc = wm.find(sought);
	if(loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
	// QueryResult QR;
	// auto count = word_line.count(s);
	// QR.count = count;
	// auto iter = word_line.find(s);

	// while(count)
	// {
	// 	QR.line_num.insert(iter->second);
	// 	++iter;
	// 	--count;
	// }

	// return QR;
	// // for(auto iter = word_line.lower_bound(s), end = word_line.upper_bound(s); iter != end; ++iter)
	// // {
	// // 	line_num.insert(iter->second);
	// // }
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " /*<< make_plural(qr.lines->size(), "time", "s")*/ << std::endl;
	for(auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
	return os;
}

#endif
```

ex27.cpp
```cpp
#include <iostream>
#include <string>
#include "TextQuery_ex27.h"

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
        // tq.query(s);
    }
}

int main()
{
    std::ifstream file("storyDataFile");
    runQueries(file);
}
```

## 12.28
略。

## 12.29
```cpp
do{
    std::cout << "enter word to look for, or q to quit: ";
    std::string s;
    if (!(std::cin >> s) || s == "q") break;
    print(std::cout, tq.query(s)) << std::endl;
    // tq.query(s);
}while (true);
```
更喜欢while，更加习惯，看起来更简单。

## 12.30
见12.27。

## 12.31
vector不能确保元素的唯一性，所以这里set更好。

## 12.32
TextQuery_ex32.h
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
#include "StrBlob_ex22.h"

class QueryResult;

class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	StrBlob file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, StrBlob f) : sought(s), lines(p), file(f) { }
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	StrBlob file;
};

TextQuery::TextQuery(std::ifstream &ifs){
	std::string text;

	while(std::getline(ifs, text))
	{
		file.push_back(text);
		int n = file.size() - 1;
		std::istringstream line(text);
		std::string text;
		while(line >> text)
		{
			std::string word;
			std::copy_if(text.begin(), text.end(), std::back_inserter(word), isalpha);
			// std::cout << word << std::endl;
			auto &lines = wm[word];
			if(!lines)
				lines.reset(new std::set<line_no>);
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<TextQuery::line_no>> nodata(new std::set<TextQuery::line_no>);
	auto loc = wm.find(sought);
	if(loc == wm.end())
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

#endif
```

ex32.cpp
```cpp
#include <iostream>
#include <string>
#include "TextQuery_ex32.h"

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
        // tq.query(s);
    }
}

int main()
{
    std::ifstream file("storyDataFile");
    runQueries(file);
}
```

## 12.33
TextQuery_ex33.h
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
#include "StrBlob_ex22.h"

class QueryResult;

class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	StrBlob file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, StrBlob f) : sought(s), lines(p), file(f) { }
	std::set<StrBlob::size_type>::iterator begin() const { return lines->begin(); }
	std::set<StrBlob::size_type>::iterator end() const { return lines->end(); }
	shared_ptr<StrBlob> get_file() const { return std::make_shared<StrBlob>(file); }
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	StrBlob file;
};

TextQuery::TextQuery(std::ifstream &ifs){
	std::string text;

	while(std::getline(ifs, text))
	{
		file.push_back(text);
		int n = file.size() - 1;
		std::istringstream line(text);
		std::string text;
		while(line >> text)
		{
			std::string word;
			std::copy_if(text.begin(), text.end(), std::back_inserter(word), isalpha);
			// std::cout << word << std::endl;
			auto &lines = wm[word];
			if(!lines)
				lines.reset(new std::set<line_no>);
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<TextQuery::line_no>> nodata(new std::set<TextQuery::line_no>);
	auto loc = wm.find(sought);
	if(loc == wm.end())
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

#endif
```

ex33.cpp
```cpp
#include <iostream>
#include <string>
#include "TextQuery_ex32.h"

void runQueries(std::ifstream &infile)
{
    TextQuery tq(infile);
    while (true) {
        std::cout << "enter word to look for, or q to quit: ";
        std::string s;
        if (!(std::cin >> s) || s == "q") break;
        print(std::cout, tq.query(s)) << std::endl;
        // tq.query(s);
    }
}

int main()
{
    std::ifstream file("storyDataFile");
    runQueries(file);
}
```