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
