## 6.1
形参在函数的定义中声明；
实参是形参的初始值。
## 6.2
（a）返回类型为int，但是实际返回了字符串：
```cpp
string f() {  // return should be string, not int
          string s;
          // ...
          return s;
}
```
（b）需要加上函数声明：
```cpp
void f2(int i) { /* ... */ }  // function needs return type
```
（c）形参的名字不能相同：
```cpp
int calc(int v1, int v2) { /* ... */ }  // parameter list cannot use same name twice
```
（d）需要有大括号（块）：
```cpp
double square (double x) { return x * x; }  // function body needs braces
```
## 6.3
```cpp
#include <iostream>

int fact(int n)
{
	int ret = 1;
	for(int i = 1;i <= n;++i)
	{
		ret *= i;
	}
	return ret;
}

int main()
{
	std::cout << fact(5) << std::endl;

	return 0;
}
```

## 6.4
```cpp
#include <iostream>

int fact(int n)
{
	int ret = 1;
	for(int i = 1;i <= n;++i)
	{
		ret *= i;
	}
	return ret;
}

int main()
{
	int n;
	std::cin >> n;
	std::cout << fact(n) << std::endl;

	return 0;
}
```

## 6.5
```cpp
#include <iostream>

int absolute(int n)
{
	return (n > 0) ? n : -n;
}

int main()
{
	std::cout << absolute(5) << std::endl;

	return 0;
}
```

## 6.6
形参是局部变量的一种。
形参和函数体内部定义的变量统称为局部变量。
局部静态变量的生命周期贯穿函数调用及之后的时间。
```cpp
// example
size_t count_add(int n)       // n is a parameter and local variable.
{
    static size_t ctr = 0;    // ctr is a static variable.
    ctr += n;
    return ctr;
}

int main()
{
    for (size_t i = 0; i != 10; ++i)  // i is a local variable.
      cout << count_add(i) << endl;

    return 0;
}
```

## 6.7
```cpp
size_t generate()
{
    static size_t ctr = 0;
    return ctr++;
}
```

##　6.8
```cpp
#ifndef CHAPTER6_H
#define CHAPTER6_H

int fact(int n);
int absolute(int n);

#endif
```
## 6.9
fact.cpp
```cpp
#include "Chapter6.h"

int fact(int n)
{
	int ret = 1;
	for(int i = 1;i <= n;++i)
	{
		ret *= i;
	}
	return ret;
}

int absolute(int n)
{
	return (n > 0) ? n : -n;
}
```

factMain.cpp
```cpp
#include <iostream>
#include "Chapter6.h"

int main()
{
	std::cout << fact(5) << std::endl;

	return 0;
}
```
```linux
$ g++ -o ex09 factMain.cpp fact.cpp -std=c++11
$ ./ex09 
120
```

## 6.10
```cpp
#include <iostream>

void swap_int(int *i,int *j)
{
	int tmp = *i;
	*i = *j;
	*j = tmp;
}

int main()
{
	int i = 1,j = 2;

	std::cout << i << " " << j << std::endl;
	swap_int(&i,&j);
	std::cout << i << " " << j << std::endl;

	return 0;
}
```

## 6.11
```cpp
#include <iostream>

void reset(int &i)
{
	i = 0;
}

int main(int argc, char const *argv[])
{
	int i = 100;

	std::cout << i << std::endl;
	reset(i);
	std::cout << i << std::endl;

	return 0;
}
```

## 6.12
```cpp
#include <iostream>

void swap_int(int &i,int &j)
{
	int tmp = i;
	i = j;
	j = tmp;
}

int main()
{
	int i = 1,j = 2;

	std::cout << i << " " << j << std::endl;
	swap_int(i,j);
	std::cout << i << " " << j << std::endl;

	return 0;
}
```
引用更易于使用，不用考虑传递的是指针，避免语法错误；
使用引用避免拷贝。

## 6.13
void f(T)
将实参的值拷贝后赋给形参，不能通过改变形参的值来改变实参；
void f(&T)
使用引用将形参绑定到实参上，可以通过改变形参来改变实参。

## 6.14
应该是引用的例子:
```cpp
void reset(int &i)
{
        i = 0;
}
```

不能是引用的例子（有关容器的迭代器貌似都不能定义为引用，具体原因不清楚）:
```cpp
void print(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
        for (std::vector<int>::iterator iter = begin; iter != end; ++iter)
                std::cout << *iter << std::endl;
}
```

## 6.15
s不需要改变实参，occurs需要改变实参；s可能会很大，occurs需要改变实参，c没有上述两个需求；如果s是普通的引用可能改变实参；occurs是常量引用则不能改变实参，++occurs会报错

## 6.16
该函数无需改变实参，故将其设置为const比较好，这样也可以传入const类型的字符串，或字符串字面值。
```cpp
bool is_empty(const string& s) { return s.empty(); }
```

## 6.17
```cpp
#include <iostream>
#include <string>

bool is_upper(const std::string &s)
{
	for(auto c : s)
	{
		if(isupper(c)) return true;
	}
	return false;
}

void to_upper(std::string &s)
{
	for(auto &c : s) c = tolower(c);
}

int main(int argc, char const *argv[])
{
	std::string s("abcdABCD");

	std::cout << (is_upper(s) ? "is upper" : "is not upper") << std::endl;
	std::cout << s << std::endl;
	to_upper(s);
	std::cout << s << std::endl;

	return 0;
}
```

## 6.18
```cpp
（a）bool compare(matrix &m1,matrix &m2);
（b）vector<int>::iterator change_val(int i,vector<int>::iterator);
```

## 6.19
（a）不合法，只能一个形参；
（b）合法；
（c）合法；
（d）合法。

## 6.20
无需改变实参的时候应该用常量引用；可能会改变常亮实参，从而导致出错。

## 6.21
```cpp
#include <iostream>

int compare(int j, int *i)
{
	return j > *i ? j : *i; 
}

int main()
{
	int j = 0, i = 1;
	
	std::cout << compare(j, &i) << std::endl;

	return 0;
}
```

## 6.22
```cpp
#include <iostream>

void swap_intp(int *&i, int *&j)
{
	int *tmp;
	tmp = i;
	i = j;
	j = tmp;
}

int main()
{
	int i = 0, j = 1;
	int *pi = &i, *pj = &j;

	std::cout << pi << " " << pj << std::endl;
	swap_intp(pi, pj);
	std::cout << pi << " " << pj << std::endl;

	return 0;
}
```

## 6.23
```cpp
#include <iostream>

using std::cout;
using std::endl;
using std::begin;
using std::end;

void print(const int* pi)
{
	cout << *pi << endl;
}

void print(const int *beg, const int *end)
{
	while(beg != end)
		cout << *beg++ << " ";
	cout << endl;
}

void print(const int ia[], size_t size)
{
	for(size_t i = 0; i != size; ++i)
		cout << ia[i] << " ";
	cout << endl;
}

void print(const int (&arr)[2])
{
	for(auto e : arr)
		cout << e << " ";
	cout << endl;
}

int main()
{
	int i = 0, j[2] = {0, 1};

	print(&i);
	print(begin(j), end(j));
	print(j, end(j) - begin(j));
	print(j);

	return 0;
}
```

## 6.24
该函数传递的不是数组是const int*，如果实参不是含10个元素的int数组，可能导致for循环数组越界。修改为：
```cpp
void print(const int (&ia)[10]) { /*...*/ }
```

## 6.25
```cpp
#include <iostream>

int main(int argc, char const *argv[])
{
	const std::string s1 = argv[1], s2 = argv[2];

	std::cout << s1 + s2 << std::endl;

	return 0;
}
```
```linux
$ ./ex25 hel lo
hello
```

## 6.26
```cpp
#include <iostream>

int main(int argc, char const *argv[])
{
	std::string s;

	for(int i = 0; i != argc; ++i)
		s += std::string(argv[i]) + " ";
	std::cout << s << std::endl;

	return 0;
}
```
```linux
$ ./ex26 -d -o ofile data0
./ex26 -d -o ofile data0 
$ ./ex26 
./ex26 
```

## 6.27
```cpp
#include <iostream>
#include <initializer_list>

int counter_int(std::initializer_list<int> il)
{
	int cnt_i = 0;
	for(auto e : il)
		cnt_i += e;
	return cnt_i;
}

int main(int argc, char const *argv[])
{
	std::cout << counter_int({1,2,3,4,5}) << std::endl;

	return 0;
}
```

## 6.28
const std::string&

## 6.29
如果拷贝代价小，则无需设置成引用类型；如果拷贝代价大，可以设置成引用类型。（具体的我也不太理解）

## 6.36
```cpp
std::string (&fun(std::string (&arrs)[10]))[10];
```

## 6.37
```cpp
using ARRS = std::string[10];
ARRS &fun(ARRS &arrs);
 
auto fun(std::string (&arrs)[10]) -> std::string (&)[10]);
 
std::string arrs1[10];
decltype(arrs1) &fun(decltype(arrs1) &arrs);
```
个人觉得using最好，最简洁。

## 6.38
```cpp
decltype(arrStr)& arrPtr(int i)
{
          return (i % 2) ? odd : even;
}
```

## 6.39
