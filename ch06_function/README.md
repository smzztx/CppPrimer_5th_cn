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

## 6.8
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

## 6.30
g++
```linux
错误#1：error: return-statement with no value, in function returning ‘bool’ [-fpermissive]
错误#2：检查不出，返回true
```

## 6.31
返回的引用时局部对象的引用，返回的常量引用是局部常量对象的引用时。

## 6.32
合法，返回数组ia[0]-ia[9]

## 6.33
```cpp
#include <iostream>
#include <vector>

void read_vi(std::vector<int>::const_iterator iterator_begin, std::vector<int>::const_iterator iterator_end)
{
	if(iterator_begin != iterator_end)
	{
		std::cout << *iterator_begin << " ";
		return read_vi(++iterator_begin, iterator_end);
	}else
	{
		std::cout << std::endl;
		return;
	}
}

int main()
{
	std::vector<int> v{1,2,3,4,5};

	read_vi(v.begin(), v.end());

	return 0;
}
```

## 6.34
如果实参为大于等于0，函数将会多乘以一个1，比如factorial(5)，等价于5 * 4 * 3 * 2 * 1 * 1;
如果实参小于0，函数将会不断地调用它自身直到程序栈空间耗尽为止。

## 6.35
val--会返回val，使程序陷入无限循环

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
（a）合法，重复声明可以，重复定义不行；
（b）非法，仅返回值不同；
（c）合法。

## 6.40
（a）正确；
（b）错误。

## 6.41
（a）非法，函数第一个形参没有默认实参，必须给实参；
（b）合法；
（c）合法，但与初衷不符，char '*'转换成整形了。

## 6.42
```cpp
#include <iostream>
#include <string>

using std::string;

string make_plural(size_t ctr, const string &word, const string &ending = "s")
{
	return (ctr > 1) ? word + ending : word;
}

int main()
{
	std::cout << make_plural(2, "success", "es") << std::endl;
	std::cout << make_plural(2, "failure") << std::endl;
}
```

## 6.43
（a）放在头文件中，内联函数在程序中可以多次定义，它的多个定义必须完全一致，所以放在头文件中比较好；
（b）放在头文件中，声明放在头文件中。

## 6.44
```cpp
#include <iostream>
#include <string>

using std::string;

inline bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

int main()
{
	string s1("aabb"), s2("aabbcc");

	std::cout << isShorter(s1, s2) << std::endl;

	return 0;
}
```

## 6.45
6.38和6.42应该是内联函数；6.4不应该是，规模不小，调用不频繁。

## 6.46
不能，因为std::string::size()不是一个constexpr函数，s1.size() == s2.size()不是一个常量表达式。

## 6.47
```cpp
#include <iostream>
#include <vector>
#include <cassert>

// #define NDEBUG	//this is not work for assert(), we should use $ g++ -o ex47 ex47.cpp -D NDEBUG -std=c++11

void read_vi(std::vector<int>::const_iterator iterator_begin, std::vector<int>::const_iterator iterator_end)
{
	#ifndef NDEBUG
		std::cerr << iterator_end - iterator_begin << __func__ << " " << __FILE__ << " " 
		<< __LINE__ << " " << __TIME__ << " " << __DATE__ << std::endl;
	#endif
	assert(0);

	if(iterator_begin != iterator_end)
	{
		std::cout << *iterator_begin << " ";
		return read_vi(++iterator_begin, iterator_end);
	}else
	{
		std::cout << std::endl;
		return;
	}
}

int main()
{
	std::vector<int> v{1,2,3,4,5};

	read_vi(v.begin(), v.end());

	return 0;
}
```

## 6.48
合理，当输入结束时终止程序。

## 6.49
候选函数具备两个特征：一是与被调用的函数同名，二是其声明在调用点可见。
可行函数是从候选函数中选出的，有两个特征：一是其形参数量与本次调用提供的实参数量相等，二是每个实参的类型与对应的形参类型相同，或者能转换成形参的类型。

## 6.50
（a）二义性；（b）最佳匹配void f(int)；（c）最佳匹配void f(int, int)；（d）最佳匹配void f(double, double = 3.14)。

## 6.51
```cpp
#include <iostream>
using std::cout; using std::endl;

void f()
{
    cout << "f()" << endl;
}

void f(int)
{
    cout << "f(int)" << endl;
}

void f(int, int)
{
    cout << "f(int, int)" << endl;
}

void f(double, double)
{
    cout << "f(double, double)" << endl;
}

int main()
{
    //f(2.56, 42); // error: 'f' is ambiguous.
    f(42);
    f(42, 0);
    f(2.56, 3.14);
    
    return 0;
}
```

## 6.52
（a）3等级，通过类型提升实现的匹配；
（b）4等级，通过算数类型转换。

## 6.53
（a）合法，实参可以为const int；
（b）合法，实参可以为const char*；
（c）合法，顶层const，声明重复（可以重复声明，不可重复定义）。

## 6.54
```cpp
vector<int (*)(int, int)> vf;

//others:
int func(int a, int b);

using pFunc1 = decltype(func) *;
typedef decltype(func) *pFunc2;
using pFunc3 = int (*)(int a, int b);
using pFunc4 = int(int a, int b);
typedef int(*pFunc5)(int a, int b);
using pFunc6 = decltype(func);

std::vector<pFunc1> vec1;
std::vector<pFunc2> vec2;
std::vector<pFunc3> vec3;
std::vector<pFunc4*> vec4;
std::vector<pFunc5> vec5;
std::vector<pFunc6*> vec6;
```

## 6.55
```cpp
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }
```

## 6.56
```cpp
#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::cout;
using std::endl;
using std::vector;

int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }

int main()
{
	vector<int (*)(int, int)> vf{add, subtract, multiply, divide};

	for(const auto &e : vf) cout << e(4, 2) << endl;

	return 0;
}
```
