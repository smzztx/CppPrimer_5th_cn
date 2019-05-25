## 练习13.1

> 拷贝构造函数是什么？什么时候使用它？

如果一个构造函数的第一个参数是自身类类型的引用，且任何额外的参数都有默认值，则次构造函数是拷贝构造函数。  
1) 一个对象作为函数参数，以值传递的方式传入函数体；  
2) 一个对象作为函数返回值，以值传递的方式从函数返回；  
3) 一个对象用于给另外一个对象进行初始化（常称为赋值初始化）；  
4) 用花括号列表初始化一个数组中的元素或一个聚合类成员。  

## 练习13.2

> 解释为什么下面的声明是非法的：
```cpp
Sales_data::Sales_data(Sales_data rhs);
```

永远也不会调用成功，为了调用拷贝构造函数，我们需要拷贝它的实参，但为了拷贝实参，我们又需要调用拷贝构造函数，如此无限循环。  

## 练习13.3

> 当我们拷贝一个StrBlob时，会发生什么？拷贝一个StrBlobPtr呢？

拷贝StrBlob时shared_ptr+1，拷贝StrBlobPtr不会。  

## 练习13.4

> 假定 Point 是一个类类型，它有一个public的拷贝构造函数，指出下面程序片段中哪些地方使用了拷贝构造函数：
```cpp
Point global;
Point foo_bar(Point arg) // 1
{
	Point local = arg, *heap = new Point(global); // 2: Point local = arg,  3: Point *heap = new Point(global) 
	*heap = local; 
	Point pa[4] = { local, *heap }; // 4, 5
	return *heap;  // 6
}
```

```cpp
Point global;
Point foo_bar(Point arg) //1 函数参数
{
    Point local = arg, *heap = new Point(global); //2,3 赋值初始化
    *heap = local;
    Point pa[ 4 ] = { local, *heap }; //4,5 列表初始化
    return *heap; //6 返回值
}
```

## 练习13.5

> 给定下面的类框架，编写一个拷贝构造函数，拷贝所有成员。你的构造函数应该动态分配一个新的string，并将对象拷贝到ps所指向的位置，而不是拷贝ps本身：
```cpp
class HasPtr {
public:
	HasPtr(const std::string& s = std::string()):
		ps(new std::string(s)), i(0) { }
private:
	std::string *ps;
	int i;
}
```

```cpp
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
private:
    std::string *ps;
    int i;
};
```

## 练习13.6

> 拷贝赋值运算符是什么？什么时候使用它？合成拷贝赋值运算符完成什么工作？什么时候会生成合成拷贝赋值运算符？

拷贝赋值运算符是一个名为operator=的函数，它接受与类相同类型的参数；  
当赋值发生时使用该运算符；  
将右侧运算对象的每个非static成员赋予左侧运算对象的对应成员，对于数组类型的成员，逐个赋值数组元素，合成拷贝赋值运算符返回一个指向其左侧运算对象的引用；  
如果一个类未定义自己的拷贝赋值运算符。  

## 练习13.7

> 当我们将一个 StrBlob 赋值给另一个 StrBlob 时，会发生什么？赋值 StrBlobPtr 呢？

同13.3一样，赋值StrBlob时shared_ptr+1，赋值StrBlobPtr不会。  

## 练习13.8

> 为13.1.1节练习13.5中的 HasPtr 类编写赋值运算符。类似拷贝构造函数，你的赋值运算符应该将对象拷贝到ps指向的位置。

```cpp
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
    HasPtr& operator=(const HasPtr &rhs_hp) {
        if(this != &rhs_hp){
            std::string *temp_ps = new std::string(*rhs_hp.ps);
            delete ps;
            ps = temp_ps;
            i = rhs_hp.i;
        }
        return *this;
    }
private:
    std::string *ps;
    int i;
};
```

## 练习13.9

> 析构函数是什么？合成析构函数完成什么工作？什么时候会生成合成析构函数？

析构函数是类的一个成员函数，名字由波浪号接类名构成，它没有返回值，也不接受参数，用于释放对象所使用的资源，并销毁对象的非static数据成员；  
类似拷贝构造函数和拷贝赋值运算符，对于某些类，和合成析构函数被用来阻止该类型的对象被销毁，如果不是这种情况，合成析构函数的函数体就为空；  
当一个类未定义自己的析构函数时，编译器会为它定义一个合成析构函数。  

## 练习13.10

> 当一个 StrBlob 对象销毁时会发生什么？一个 StrBlobPtr 对象销毁时呢？

销毁StrBlob时shared_ptr-1，直到为0时，对象销毁，销毁StrBlobPtr不会销毁对象。  

## 练习13.11

> 为前面练习中的 HasPtr 类添加一个析构函数。

```cpp
#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
    HasPtr& operator=(const HasPtr &rhs_hp) {
        if(this != &rhs_hp){
            std::string *temp_ps = new std::string(*rhs_hp.ps);
            delete ps;
            ps = temp_ps;
            i = rhs_hp.i;
        }
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

#endif
```

## 练习13.12

> 在下面的代码片段中会发生几次析构函数调用？
```cpp
bool fcn(const Sales_data *trans, Sales_data accum)
{
	Sales_data item1(*trans), item2(accum);
	return item1.isbn() != item2.isbn();
}
```

离开后accum、item1和item2销毁。  

## 练习13.13

> 理解拷贝控制成员和构造函数的一个好方法的定义一个简单的类，为该类定义这些成员，每个成员都打印出自己的名字：
```cpp
struct X {
	X() {std::cout << "X()" << std::endl;}
	X(const X&) {std::cout << "X(const X&)" << std::endl;}
}
```
给 X 添加拷贝赋值运算符和析构函数，并编写一个程序以不同的方式使用 X 的对象：将它们作为非引用参数传递；动态分配它们；将它们存放于容器中；诸如此类。观察程序的输出，直到你确认理解了什么时候会使用拷贝控制成员，以及为什么会使用它们。当你观察程序输出时，记住编译器可以略过对拷贝构造函数的调用。

```cpp
#include <iostream>
#include <string>
#include <vector>

struct X
{
	X() { std::cout << "X()" << std::endl; }
	X(const X&) { std::cout << "X(const X&)" << std::endl; }
	X& operator=(const X &rh)
	{
		std::cout << "X& operator=(const X &rh)" << std::endl;
		return *this;
	}
	~X() { std::cout << "~x()" << std::endl; }
};

void func1(X x)
{
	std::cout << "void func1(X x)" << std::endl;
}

void func2(X &x)
{
	std::cout << "void func2(X &x)" << std::endl;
}

int main()
{
	std::cout << "x1" << std::endl;
	X x1;
	func1(x1);
	std::cout << "main" << std::endl;
	func2(x1);
	std::cout << "main" << std::endl;
	X *x2 = new X();
	{	
		std::cout << "vector" << std::endl;
		std::vector<X> v;
		v.reserve(2);
		v.push_back(x1);
		v.push_back(*x2);
	}
	delete x2;
	std::cout << "after delete x2" << std::endl;

	return 0;
}
```
```sh
$ ./ex13
x1
X()
X(const X&)
void func1(X x)
~x()
main
void func2(X &x)
main
X()
vector
X(const X&)
X(const X&)
~x()
~x()
~x()
after delete x2
~x()
```

## 练习13.14

> 假定 numbered 是一个类，它有一个默认构造函数，能为每个对象生成一个唯一的序号，保存在名为 mysn 的数据成员中。假定 numbered 使用合成的拷贝控制成员，并给定如下函数：
```cpp
void f (numbered s) { cout << s.mysn < endl; }
```
则下面代码输出什么内容？
```cpp
numbered a, b = a, c = b;
f(a); f(b); f(c);
```

输出同一个mysn。  

## 练习13.15

> 假定numbered 定义了一个拷贝构造函数，能生成一个新的序列号。这会改变上一题中调用的输出结果吗？如果会改变，为什么？新的输出结果是什么？

会，在拷贝初始化时会调用拷贝构造函数，能生成一个新的序号，但是，调用f函数时又生成一个新的序号，所以，新的输出结果会输出不同的mysn，但不是a、b、c的mysn。  

## 练习13.16

> 如果 f 中的参数是 const numbered&，将会怎样？这会改变输出结果吗？如果会改变，为什么？新的输出结果是什么？

会，在拷贝初始化时会调用拷贝构造函数，能生成一个新的序号，所以，新的输出结果会输出不同的mysn，是a、b、c的mysn。  

## 练习13.17

> 分别编写前三题中所描述的 numbered 和 f，验证你是否正确预测了输出结果。

ex17_1.cpp
```cpp
#include <iostream>
#include <cstdlib>
#include <string>

class numbered
{
friend void f(numbered s);
public:
	numbered() : mysn(std::to_string(std::rand())) { };
	~numbered() { };
private:
	std::string mysn;
};

void f(numbered s)
{
	std::cout << s.mysn << std::endl;
}

int main()
{
	numbered a, b = a, c = b;
	f(a); f(b); f(c);

	return 0;
}
```

ex17_2.cpp
```cpp
#include <iostream>
#include <cstdlib>
#include <string>

class numbered
{
friend void f(numbered s);
public:
	numbered() : mysn(std::to_string(std::rand())) { };
	numbered(const numbered&) : mysn(std::to_string(std::rand())) { };
	~numbered() { };
private:
	std::string mysn;
};

void f(numbered s)
{
	std::cout << s.mysn << std::endl;
}

int main()
{
	numbered a, b = a, c = b;
	f(a); f(b); f(c);

	return 0;
}
```

ex17_3.cpp
```cpp
#include <iostream>
#include <cstdlib>
#include <string>

class numbered
{
friend void f(const numbered&);
public:
	numbered() : mysn(std::to_string(std::rand())) { };
	numbered(const numbered&) : mysn(std::to_string(std::rand())) { };
	~numbered() { };
private:
	std::string mysn;
};

void f(const numbered &s)
{
	std::cout << s.mysn << std::endl;
}

int main()
{
	numbered a, b = a, c = b;
	f(a); f(b); f(c);

	return 0;
}
```

## 练习13.18

> 定义一个 Employee 类，它包含雇员的姓名和唯一的雇员证号。为这个类定义默认构造函数，以及接受一个表示雇员姓名的 string 的构造函数。每个构造函数应该通过递增一个 static 数据成员来生成一个唯一的证号。

```cpp
#include <iostream>
#include <string>

class Employee
{
friend void print(const Employee&);
public:
	Employee() { id = n; ++n; };
	Employee(const std::string &s) { id = n; ++n; name = s; };
private:
	std::string name;
	int id;
	static int n;
};

void print(const Employee &e)
{
	std::cout << e.name << " " << e.id << std::endl;
}

int Employee::n = 0;

int main()
{
	Employee a;
	Employee b("bbb");

	print(a);
	print(b);

	return 0;
}
```

## 练习13.19

> 你的 Employee 类需要定义它自己的拷贝控制成员吗？如果需要，为什么？如果不需要，为什么？实现你认为 Employee 需要的拷贝控制成员。

不需要，员工在现实中不能复制。  
```cpp
#include <iostream>
#include <string>

class Employee
{
friend void print(const Employee&);
public:
	Employee() { id = n; ++n; };
	Employee(const std::string &s) { id = n; ++n; name = s; };
	Employee(const Employee&) = delete;
	Employee &operator=(const Employee&) = delete;
private:
	std::string name;
	int id;
	static int n;
};

void print(const Employee &e)
{
	std::cout << e.name << " " << e.id << std::endl;
}

int Employee::n = 0;

int main()
{
	Employee a;
	Employee b("bbb");

	print(a);
	print(b);

	return 0;
}
```

## 练习13.20

> 解释当我们拷贝、赋值或销毁 TextQuery 和 QueryResult 类对象时会发生什么？

成员对象会被复制。  

## 练习13.21

> 你认为 TextQuery 和 QueryResult 类需要定义它们自己版本的拷贝控制成员吗？如果需要，为什么？实现你认为这两个类需要的拷贝控制操作。

不需要，合成拷贝控制成员已满足需求。  

## 练习13.22

> 假定我们希望 HasPtr 的行为像一个值。即，对于对象所指向的 string 成员，每个对象都有一份自己的拷贝。我们将在下一节介绍拷贝控制成员的定义。但是，你已经学习了定义这些成员所需的所有知识。在继续学习下一节之前，为 HasPtr 编写拷贝构造函数和拷贝赋值运算符。

见13.11。  

## 练习13.23

> 比较上一节练习中你编写的拷贝控制成员和这一节中的代码。确定你理解了你的代码和我们的代码之间的差异。

请自行比较。  

## 练习13.24

> 如果本节的 HasPtr 版本未定义析构函数，将会发生什么？如果未定义拷贝构造函数，将会发生什么？

如果未定义析构函数，将会发生内存泄漏，动态内存得不到释放，直到没有内存可以申请；如果未定义拷贝构造函数，指针将被复制，可能会多次释放同一个内存。  

## 练习13.25

> 假定希望定义 StrBlob 的类值版本，而且希望继续使用 shared_ptr，这样我们的 StrBlobPtr 类就仍能使用指向vector的 weak_ptr 了。你修改后的类将需要一个拷贝的构造函数和一个拷贝赋值运算符，但不需要析构函数。解释拷贝构造函数和拷贝赋值运算符必须要做什么。解释为什么不需要析构函数。

拷贝构造函数和拷贝赋值运算符需要使用值新建一个shared_ptr，当类销毁时，shared_ptr计数减1，当计数为0时，其指向的对象会自动销毁。  

## 练习13.26

> 对上一题中描述的 strBlob 类，编写你自己的版本。

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
public:
	friend class ConstStrBlobPtr;
	typedef std::vector<std::string>::size_type size_type;
	StrBlob();
	StrBlob(std::initializer_list<std::string> il);
	StrBlob(const StrBlob&);
	StrBlob &operator=(const StrBlob&);
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

#endif
```

ex26.cpp
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

## 练习13.27

> 定义你自己的使用引用计数版本的 HasPtr。

HasPtr_ex27.h
```cpp
#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { ++*use;}
    HasPtr& operator=(const HasPtr &rhs_hp) {
        ++*rhs_hp.use;
        if(--*use == 0)
        {
            delete ps;
            delete use;
        }
        ps = rhs_hp.ps;
        i = rhs_hp.i;
        use = rhs_hp.use;
        return *this;
    }
    ~HasPtr()
    {
        if(--*use == 0)
        {
            delete ps;
            delete use;
        }
    }
private:
    std::string *ps;
    int i;
    std::size_t *use;
};

#endif
```
ex27.cpp
```cpp
#include "HasPtr_ex27.h"

int main()
{
	HasPtr hp("aaa");

	return 0;
}
```

## 练习13.28

> 给定下面的类，为其实现一个默认构造函数和必要的拷贝控制成员。
```cpp
(a) 
class TreeNode {
pravite:
	std::string value;
	int count;
	TreeNode *left;
	TreeNode *right;	
};
(b)
class BinStrTree{
pravite:
	TreeNode *root;	
};
```

ex13_28.h
```cpp
//
//  ex13_28.h
//  Exercise 13.28
//
//  Created by pezy on 1/20/15.
//
//  Given the following classes, implement a default constructor and the necessary copy-control members.

#ifndef CP5_ex13_28_h
#define CP5_ex13_28_h

#include <string>
using std::string;

class TreeNode {
public:
    TreeNode() : value(string()), count(new int(1)), left(nullptr), right(nullptr) { }
    TreeNode(const TreeNode &rhs) : value(rhs.value), count(rhs.count), left(rhs.left), right(rhs.right) { ++*count; }
    TreeNode& operator=(const TreeNode &rhs);
    ~TreeNode() {
        if (--*count == 0) {
            delete left;
            delete right;
            delete count;
        }
    }

private:
    std::string value;
    int         *count;
    TreeNode    *left;
    TreeNode    *right;
};

class BinStrTree {
public:
    BinStrTree() : root(new TreeNode()) { }
    BinStrTree(const BinStrTree &bst) : root(new TreeNode(*bst.root)) { }
    BinStrTree& operator=(const BinStrTree &bst);
    ~BinStrTree() { delete root; }

private:
    TreeNode *root;
};

#endif
```

ex28.cpp
```cpp
//
//  ex13_28.cpp
//  Exercise 13.28
//
//  Created by pezy on 1/20/15.
//
//  Given the following classes, implement a default constructor and the necessary copy-control members.

#include "ex13_28.h"

TreeNode& TreeNode::operator=(const TreeNode &rhs)
{
    ++*rhs.count;
    if (--*count == 0) {
        delete left;
        delete right;
        delete count;
    }
    value = rhs.value;
    left = rhs.left;
    right = rhs.right;
    count = rhs.count;
    return *this;
}

BinStrTree& BinStrTree::operator=(const BinStrTree &bst)
{
    TreeNode *new_root = new TreeNode(*bst.root);
    delete root;
    root = new_root;
    return *this;
}

int main()
{
    return 0;
}
```

## 练习13.29

> 解释 swap(HasPtr&, HasPtr&)中对 swap 的调用不会导致递归循环。

函数的参数不一样，调用的函数不一样。  

## 练习13.30

> 为你的类值版本的 HasPtr 编写 swap 函数，并测试它。为你的 swap 函数添加一个打印语句，指出函数什么时候执行。

HasPtr_ex30.h
```cpp
#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>
#include <iostream>

class HasPtr {
friend void swap(HasPtr&, HasPtr&);
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
    HasPtr& operator=(const HasPtr &rhs_hp) {
        auto newp = new std::string(*rhs_hp.ps);
        delete ps;
        ps = newp;
        i = rhs_hp.i;
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "swap" << std::endl;
}

#endif
```

ex39.cpp
```cpp
#include "HasPtr_ex30.h"
#include <iostream>

int main()
{
	HasPtr hp1("aaa"),hp2("bbb");
	swap(hp1,hp2);
	std::cout << "main" << std::endl;

	return 0;
}
```

## 练习13.31

> 为你的 HasPtr 类定义一个 < 运算符，并定义一个 HasPtr 的 vector。为这个 vector 添加一些元素，并对它执行 sort。注意何时会调用 swap。

HasPtr_ex31.h
```cpp
#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>
#include <iostream>

class HasPtr {
friend void swap(HasPtr&, HasPtr&);
friend bool operator<(const HasPtr&, const HasPtr&);
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
    HasPtr& operator=(const HasPtr &rhs_hp) {
        auto newp = new std::string(*rhs_hp.ps);
        delete ps;
        ps = newp;
        i = rhs_hp.i;
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "swap" << std::endl;
}

bool operator<(const HasPtr &lhs, const HasPtr &rhs)
{
    std::cout << "<" << std::endl;
    return *lhs.ps < *rhs.ps;
}

#endif
```

ex31.cpp
```cpp
#include "HasPtr_ex31.h"
#include <vector>
#include <algorithm>

int main()
{
	HasPtr hp1("aaa"),hp2("bbb");
	std::vector<HasPtr> vh{hp1, hp2};
	std::sort(vh.begin(), vh.end());

	return 0;
}
```

## 练习13.32

> 类指针的 HasPtr 版本会从 swap 函数收益吗？如果会，得到了什么益处？如果不是，为什么？

不会，类指针本身就是指针交换，没有内存分配。  

## 练习13.33

> 为什么Message的成员save和remove的参数是一个 Folder&？为什么我们不能将参数定义为 Folder 或是 const Folder？

因为需要更改Folder的值。  

## 练习13.34

> 编写本节所描述的 Message。

Message_ex34.h
```cpp
#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <set>

class Message
{
	friend class Folder;
	friend void swap(Message&, Message&);
public:
	explicit Message(const std::string &str = "") : contents(str) { };
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	void save(Folder&);
	void remove(Folder&);
private:
	std::string contents;
	std::set<Folder*> folders;
	void add_to_Folders(const Message&);
	void remove_from_Folders();
	void addFldr(Folder *f) { folders.insert(f); }
	void remFldr(Folder *f) { folders.erase(f); }
};

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
	for(auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message & m) : contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Folders()
{
	for(auto f : folders)
		f->remMsg(this);
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

#endif
```

## 练习13.35

> 如果Message 使用合成的拷贝控制成员，将会发生什么？

将不能正确拷贝，Message中保存的Folder信息与Folder中保存的Message信息不统一。  

## 练习13.36

> 设计并实现对应的 Folder 类。此类应该保存一个指向 Folder 中包含  Message 的 set。

```cpp
#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <set>

class Folder;

class Message
{
	friend class Folder;
	friend void swap(Message&, Message&);
public:
	explicit Message(const std::string &str = "") : contents(str) { };
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	void save(Folder&);
	void remove(Folder&);
private:
	std::string contents;
	std::set<Folder*> folders;
	void add_to_Folders(const Message&);
	void remove_from_Folders();
	void addFldr(Folder *f) { folders.insert(f); }
	void remFldr(Folder *f) { folders.erase(f); }
};

class Folder
{
	friend void swap(Folder&, Folder&);
	friend class Message;
public:
	Folder() = default;
	Folder(const Folder &);
	Folder& operator=(const Folder&);
	~Folder();
private:
	std::set<Message*> msgs;
	void add_to_Message(const Folder&);
	void remove_from_Message();
	void addMsg(Message *m) { msgs.insert(m); }
	void remMsg(Message *m) { msgs.erase(m); }
};

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
	for(auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message & m) : contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Folders()
{
	for(auto f : folders)
		f->remMsg(this);
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

// void swap(Message &lhs, Message &rhs)
// {
// 	using std::swap;
// 	for(auto f : lhs.folders)
// 		f->remMsg(&lhs);
// 	for(auto f : rhs.folders)
// 		f->remMsg(&rhs);
// 	swap(lhs.folders, rhs.folders);
// 	swap(lhs.contents, rhs.contents);
// 	for(auto f : lhs.folders)
// 		f->addMsg(&lhs);
// 	for(auto f : rhs.folders)
// 		f->addMsg(&rhs);
// }

void Folder::add_to_Message(const Folder &f)
{
	for(auto m : f.msgs)
		m->addFldr(this);
}

Folder::Folder(const Folder &f) : msgs(f.msgs)
{
	add_to_Message(f);
}

void Folder::remove_from_Message()
{
	for(auto m : msgs)
		m->remFldr(this);
}

Folder::~Folder()
{
	remove_from_Message();
}

Folder &Folder::operator=(const Folder &rhs)
{
	remove_from_Message();
	msgs = rhs.msgs;
	add_to_Message(rhs);
	return *this;
}

#endif
```

ex36.cpp
```cpp
#include "Message_ex36.h"

int main()
{
	return 0;
}
```

## 练习13.37

> 为 Message 类添加成员，实现向 folders 添加和删除一个给定的 Folder*。这两个成员类似Folder 类的 addMsg 和 remMsg 操作。

同上。  

## 练习13.38

> 我们并未使用拷贝交换方式来设计 Message 的赋值运算符。你认为其原因是什么？

动态内存分配时用拷贝和交换比较好，本题中，交换是自定义的，会清除Forder中的Message再添加，因此拷贝和交换都会造成额外的消耗。  

## 练习13.39

> 编写你自己版本的 StrVec，包括自己版本的 reserve、capacity 和 resize。

```cpp
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>

class StrVec
{
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(const StrVec&);
	StrVec &operator=(const StrVec&);
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
		for(auto p = first_free; p != elements; )
			alloc.destroy(--p);
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

#endif
```
ex39.cpp
```cpp
#include "StrVec_ex39.h"

int main()
{
	return 0;
}
```

## 练习13.40

> 为你的 StrVec 类添加一个构造函数，它接受一个 initializer_list<string> 参数。

StrVec_ex40.h
```cpp
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>

class StrVec
{
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec&);
	StrVec &operator=(const StrVec&);
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
		for(auto p = first_free; p != elements; )
			alloc.destroy(--p);
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

#endif
```

ex40.cpp
```cpp
#include "StrVec_ex40.h"

int main()
{
	StrVec s({"aaa", "bbb"});

	return 0;
}
```

## 练习13.41

> 在 push_back 中，我们为什么在 construct 调用中使用后置递增运算？如果使用前置递增运算的话，会发生什么？

first_free为尾后指针，如果使用前置递增会空出一个位置。  
## 练习13.42

> 在你的 TextQuery 和 QueryResult 类中用你的 StrVec 类代替vector<string>，以此来测试你的 StrVec 类。

TextQuery_ex42.h
```cpp
#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_

#include <string>
// #include <vector>
#include "StrVec_ex40.h"
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
	using line_no = size_t;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	std::shared_ptr<StrVec> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, std::shared_ptr<StrVec> f) : sought(s), lines(p), file(f) { }
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	std::shared_ptr<StrVec> file;
};

TextQuery::TextQuery(std::ifstream &ifs) : file(new StrVec)
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

ex42.cpp
```cpp
#include <iostream>
#include <string>
#include "TextQuery_ex42.h"

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
    std::ifstream file("../ch12_Dynamic_Memory/storyDataFile");
    runQueries(file);
}
```

## 练习13.43

> 重写 free 成员，用 for_each 和 lambda 来代替 for 循环 destroy 元素。你更倾向于哪种实现，为什么？

StrVec_ex43.h
```cpp
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>
#include <algorithm>

class StrVec
{
public:
	StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
	StrVec(std::initializer_list<std::string>);
	StrVec(const StrVec&);
	StrVec &operator=(const StrVec&);
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

#endif
```

ex43.cpp
```cpp
#include "StrVec_ex43.h"

int main()
{
	StrVec s({"aaa", "bbb"});

	return 0;
}
```

## 练习13.44

> 编写标准库 string 类的简化版本，命名为 String。你的类应该至少有一个默认构造函数和一个接受 C 风格字符串指针参数的构造函数。使用 allocator 为你的 String类分配所需内存。

String_ex44.h
```cpp
#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>

class String
{
public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String&);
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
	return *this;
}

String::~String()
{
	// for(auto iter = elements; iter != first_free; )
	// 	alloc.destroy(--iter);
	free();
}

#endif
```

ex44.cpp
```cpp
#include "String_ex44.h"

int main()
{
	return 0;
}
```

## 练习13.45

> 解释左值引用和右值引用的区别？

左值引用是绑定到左值上的引用，左值持久；  
右值引用是绑定到右值上的引用，右值短暂，右值引用可以绑定到要求转换的表达式、字面值常量或是返回右值的表达式上。  

## 练习13.46

> 什么类型的引用可以绑定到下面的初始化器上？
```cpp
int f();
vector<int> vi(100);
int? r1 = f();
int? r2 = vi[0];
int? r3 = r1;
int? r4 = vi[0] * f();
```

```cpp
int f();
vector<int> vi(100);
int&& r1 = f();
int& r2 = vi[0];
int& r3 = r1;
int&& r4 = vi[0] * f();
```

## 练习13.47

> 对你在练习13.44中定义的 String类，为它的拷贝构造函数和拷贝赋值运算符添加一条语句，在每次函数执行时打印一条信息。

String_ex47.h
```cpp
#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

class String
{
public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String&);
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

String::~String()
{
	// for(auto iter = elements; iter != first_free; )
	// 	alloc.destroy(--iter);
	free();
}

#endif
```

ex47.cpp
```cpp
#include "String_ex47.h"

int main()
{
	return 0;
}
```

## 练习13.48

> 定义一个vector<String> 并在其上多次调用 push_back。运行你的程序，并观察 String 被拷贝了多少次。

String_ex47.h
```cpp
#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

class String
{
public:
	String();
	String(const char*);
	String(const String&);
	String& operator=(const String&);
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

String::~String()
{
	// for(auto iter = elements; iter != first_free; )
	// 	alloc.destroy(--iter);
	free();
}

#endif
```

ex48.cpp
```cpp
#include "String_ex47.h"
#include <vector>

int main()
{
	std::vector<String> v;
	v.push_back("aaa");
	v.push_back("bbb");

	return 0;
}
```

运行结果如下，显示被拷贝了3次（只执行了两次拷贝，vector有扩容）。  
```sh
$ ./ex48 
String(const String &rhs)
String(const String &rhs)
String(const String &rhs)
```

## 练习13.49

> 为你的 StrVec、String 和 Message 类添加一个移动构造函数和一个移动赋值运算符。

StrVec_ex49.h
```cpp
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>
#include <algorithm>

class StrVec
{
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

#endif
```

ex49_1.cpp
```cpp
#include "StrVec_ex49.h"

int main()
{
	StrVec s({"aaa", "bbb"});

	return 0;
}
```

String_ex49.h
```cpp
#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

class String
{
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

#endif
```

ex49_2.cpp
```cpp
#include "String_ex49.h"

int main()
{
	return 0;
}
```

Message_ex49.h
```cpp
#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <string>
#include <set>
#include <utility>

class Folder;

class Message
{
	friend class Folder;
	friend void swap(Message&, Message&);
public:
	explicit Message(const std::string &str = "") : contents(str) { };
	Message(const Message&);
	Message(Message&& m) : contents(std::move(m.contents))
	{
		move_Folders(&m);
	}
	Message& operator=(const Message&);
	Message& operator=(Message&&);
	~Message();
	void save(Folder&);
	void remove(Folder&);
	void move_Folders(Message*);
private:
	std::string contents;
	std::set<Folder*> folders;
	void add_to_Folders(const Message&);
	void remove_from_Folders();
	void addFldr(Folder *f) { folders.insert(f); }
	void remFldr(Folder *f) { folders.erase(f); }
};

class Folder
{
	friend void swap(Folder&, Folder&);
	friend class Message;
public:
	Folder() = default;
	Folder(const Folder &);
	Folder& operator=(const Folder&);
	~Folder();
private:
	std::set<Message*> msgs;
	void add_to_Message(const Folder&);
	void remove_from_Message();
	void addMsg(Message *m) { msgs.insert(m); }
	void remMsg(Message *m) { msgs.erase(m); }
};

void Message::move_Folders(Message *m)
{
	folders = std::move(m->folders);
	for(auto f : folders)
	{
		f->remMsg(m);
		f->addMsg(this);
	}
	m->folders.clear();
}

void Message::save(Folder &f)
{
	folders.insert(&f);
	f.addMsg(this);
}

void Message::remove(Folder &f)
{
	folders.erase(&f);
	f.remMsg(this);
}

void Message::add_to_Folders(const Message &m)
{
	for(auto f : m.folders)
		f->addMsg(this);
}

Message::Message(const Message & m) : contents(m.contents), folders(m.folders)
{
	add_to_Folders(m);
}

void Message::remove_from_Folders()
{
	for(auto f : folders)
		f->remMsg(this);
}

Message::~Message()
{
	remove_from_Folders();
}

Message& Message::operator=(const Message &rhs)
{
	remove_from_Folders();
	contents = rhs.contents;
	folders = rhs.folders;
	add_to_Folders(rhs);
	return *this;
}

Message& Message::operator=(Message &&rhs)
{
	if(this != &rhs)
	{
		remove_from_Folders();
		contents = std::move(rhs.contents);
		move_Folders(&rhs);
	}
	return *this;
}
// void swap(Message &lhs, Message &rhs)
// {
// 	using std::swap;
// 	for(auto f : lhs.folders)
// 		f->remMsg(&lhs);
// 	for(auto f : rhs.folders)
// 		f->remMsg(&rhs);
// 	swap(lhs.folders, rhs.folders);
// 	swap(lhs.contents, rhs.contents);
// 	for(auto f : lhs.folders)
// 		f->addMsg(&lhs);
// 	for(auto f : rhs.folders)
// 		f->addMsg(&rhs);
// }

void Folder::add_to_Message(const Folder &f)
{
	for(auto m : f.msgs)
		m->addFldr(this);
}

Folder::Folder(const Folder &f) : msgs(f.msgs)
{
	add_to_Message(f);
}

void Folder::remove_from_Message()
{
	for(auto m : msgs)
		m->remFldr(this);
}

Folder::~Folder()
{
	remove_from_Message();
}

Folder &Folder::operator=(const Folder &rhs)
{
	remove_from_Message();
	msgs = rhs.msgs;
	add_to_Message(rhs);
	return *this;
}

#endif
```

ex49_3.cpp
```cpp
#include "Message_ex49.h"

int main()
{
	return 0;
}
```

## 练习13.50

> 在你的 String 类的移动操作中添加打印语句，并重新运行13.6.1节的练习13.48中的程序，它使用了一个vector<String>，观察什么时候会避免拷贝。

String_ex50.h
```cpp
#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

class String
{
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

#endif
```

ex50.cpp
```cpp
#include "String_ex50.h"
#include <vector>

int main()
{
	std::vector<String> v;
	v.push_back("aaa");
	v.push_back("bbb");

	return 0;
}
```

```sh
$ ./ex50 
String::String(String &&s) noexcept
String::String(String &&s) noexcept
String::String(String &&s) noexcept
```

## 练习13.51

> 虽然 unique_ptr 不能拷贝，但我们在12.1.5节中编写了一个 clone 函数，它以值的方式返回一个 unique_ptr。解释为什么函数是合法的，以及为什么它能正确工作。

此时使用的是移动操作，而不是拷贝赋值操作，所以可以正常工作。  

## 练习13.52

> 详细解释第478页中的 HasPtr 对象的赋值发生了什么？特别是，一步一步描述 hp、hp2 以及 HasPtr 的赋值运算符中的参数 rhs 的值发生了什么变化。

hp = hp2;调用拷贝赋值运算符时会进行拷贝初始化，左值被拷贝，因此会调用拷贝构造函数；  
hp = std::move(hp2);经过move后，是右值，移动构造函数为精确匹配。  

## 练习13.53

> 从底层效率的角度看，HasPtr 的赋值运算符并不理想，解释为什么？为 HasPtr 实现一个拷贝赋值运算符和一个移动赋值运算符，并比较你的新的移动赋值运算符中执行的操作和拷贝并交换版本中的执行的操作。

交换操作需要给另一个不需要的变量赋值。  
HasPtr_ex53.h
```cpp
#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>
#include <iostream>

class HasPtr {
friend void swap(HasPtr&, HasPtr&);
friend bool operator<(const HasPtr&, const HasPtr&);
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
    HasPtr(HasPtr &&hp) noexcept : ps(std::move(hp.ps)), i(std::move(hp.i)) { hp.ps = nullptr; }
    HasPtr& operator=(const HasPtr &rhs_hp) {
        auto newp = new std::string(*rhs_hp.ps);
        delete ps;
        ps = newp;
        i = rhs_hp.i;
        return *this;
    }
    HasPtr& operator=(HasPtr &&rhs_hp) noexcept
    {
        if(this != &rhs_hp)
        {
            delete ps;
            ps = std::move(rhs_hp.ps);
            i = rhs_hp.i;
        }
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "swap" << std::endl;
}

bool operator<(const HasPtr &lhs, const HasPtr &rhs)
{
    std::cout << "<" << std::endl;
    return *lhs.ps < *rhs.ps;
}

#endif
```

ex53.cpp
```cpp
#include "HasPtr_ex53.h"
#include <vector>
#include <algorithm>

int main()
{
	HasPtr hp1("aaa"),hp2("bbb");
	std::vector<HasPtr> vh{hp1, hp2};
	std::sort(vh.begin(), vh.end());

	return 0;
}
```

## 练习13.54

> 如果我们为 HasPtr 定义了移动赋值运算符，但未改变拷贝并交换运算符，会发生什么？编写代码验证你的答案。

HasPtr_ex54.h
```cpp
#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>
#include <iostream>

class HasPtr {
friend void swap(HasPtr&, HasPtr&);
friend bool operator<(const HasPtr&, const HasPtr&);
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
    HasPtr(HasPtr &&hp) noexcept : ps(std::move(hp.ps)), i(std::move(hp.i)) { hp.ps = nullptr; }
    HasPtr& operator=(HasPtr rhs);
    // HasPtr& operator=(const HasPtr &rhs_hp) {
    //     auto newp = new std::string(*rhs_hp.ps);
    //     delete ps;
    //     ps = newp;
    //     i = rhs_hp.i;
    //     return *this;
    // }
    HasPtr& operator=(HasPtr &&rhs_hp) noexcept
    {
        if(this != &rhs_hp)
        {
            delete ps;
            ps = std::move(rhs_hp.ps);
            i = rhs_hp.i;
        }
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

inline void swap(HasPtr &lhs, HasPtr &rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "swap" << std::endl;
}

bool operator<(const HasPtr &lhs, const HasPtr &rhs)
{
    std::cout << "<" << std::endl;
    return *lhs.ps < *rhs.ps;
}

#endif
```

ex54.cpp
```cpp
#include "HasPtr_ex54.h"
#include <vector>
#include <algorithm>

int main()
{
	HasPtr hp1("aaa"),hp2("bbb");
	std::vector<HasPtr> vh{hp1, hp2};
	std::sort(vh.begin(), vh.end());

	return 0;
}
```
```sh
error: ambiguous overload for ‘operator=’ (operand types are ‘HasPtr’ and ‘std::remove_reference<HasPtr&>::type {aka HasPtr}’)
```

## 练习13.55

> 为你的 StrBlob 添加一个右值引用版本的 push_back。

StrBlob_ex55.h
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

#endif
```

ex55.cpp
```cpp
#include "StrBlob_ex55.h"
#include <iostream>

int main()
{
	StrBlob b1 = {"a", "an", "the"};
	StrBlob b2 = b1;

	return 0;
}
```

## 练习13.56

> 如果 sorted 定义如下，会发生什么？
```cpp
Foo Foo::sorted() const & {
	Foo ret(*this);
	return ret.sorted();
}
```

ret是一个左值，使用ret.sorted()时，调用的是左值sorted，还是本函数，这会导致进入死循环，堆栈溢出。  

## 练习13.57

> 如果 sorted定义如下，会发生什么：
```cpp
Foo Foo::sorted() const & { return Foo(*this).sorted(); }
```

可以使用，Foo(*this)是右值，会调用右值版本sorted。  

## 练习13.58

> 编写新版本的 Foo 类，其 sorted 函数中有打印语句，测试这个类，来验证你对前两题的答案是否正确。

Foo_ex58.h
```cpp
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
```

ex58.cpp
```cpp
#include "Foo_ex58.h"

int main()
{
	Foo foo;
	foo.sorted();

	return 0;
}
```

ex56运行结果:
```sh
$ ./ex58 
Foo Foo::sorted() const &
...
...
...
Foo Foo::sorted() const &
Foo Foo::sorted() const &
Segmentation fault (core dumped)
```

ex57运行结果:
```sh
$ ./ex58 
Foo Foo::sorted() const &
Foo Foo::sorted() &&
```