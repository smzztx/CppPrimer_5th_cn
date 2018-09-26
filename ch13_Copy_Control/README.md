## 13.1
如果一个构造函数的第一个参数是自身类类型的引用，且任何额外的参数都有默认值，则次构造函数是拷贝构造函数。  
1) 一个对象作为函数参数，以值传递的方式传入函数体；  
2) 一个对象作为函数返回值，以值传递的方式从函数返回；  
3) 一个对象用于给另外一个对象进行初始化（常称为赋值初始化）；  
4) 用花括号列表初始化一个数组中的元素或一个聚合类成员。  

## 13.2
永远也不会调用成功，为了调用拷贝构造函数，我们需要拷贝它的实参，但为了拷贝实参，我们又需要调用拷贝构造函数，如此无限循环。  

## 13.3
拷贝StrBlob时shared_ptr+1，拷贝StrBlobPtr不会。  

## 13.4
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

## 13.5
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

## 13.6
拷贝赋值运算符是一个名为operator=的函数，它接受与类相同类型的参数；  
当赋值发生时使用该运算符；  
将右侧运算对象的每个非static成员赋予左侧运算对象的对应成员，对于数组类型的成员，逐个赋值数组元素，合成拷贝赋值运算符返回一个指向其左侧运算对象的引用；  
如果一个类未定义自己的拷贝赋值运算符。  

## 13.7
同13.3一样，赋值StrBlob时shared_ptr+1，赋值StrBlobPtr不会。  

## 13.8
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

## 13.9
析构函数是类的一个成员函数，名字由波浪号接类名构成，它没有返回值，也不接受参数，用于释放对象所使用的资源，并销毁对象的非static数据成员；  
类似拷贝构造函数和拷贝赋值运算符，对于某些类，和合成析构函数被用来阻止该类型的对象被销毁，如果不是这种情况，合成析构函数的函数体就为空；  
当一个类未定义自己的析构函数时，编译器会为它定义一个合成析构函数。  

## 13.10
销毁StrBlob时shared_ptr-1，直到为0时，对象销毁，销毁StrBlobPtr不会销毁对象。  

## 13.11
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

## 13.12
离开后accum、item1和item2销毁。  

## 13.13
```cpp
#include <iostream>
#include <string>

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
	delete x2;
	std::cout << "delete x2" << std::endl;

	return 0;
}
```

## 13.14
