## 练习6.1

> 实参和形参的区别的什么？

形参在函数的定义中声明；  
实参是形参的初始值。 

## 练习6.2

> 请指出下列函数哪个有错误，为什么？应该如何修改这些错误呢？
```cpp
(a) int f() {
          string s;
          // ...
          return s;
    }
(b) f2(int i) { /* ... */ }
(c) int calc(int v1, int v1) { /* ... */ }
(d) double square (double x)  return x * x; 
```

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

## [练习6.3](ex03.cpp)

> 编写你自己的fact函数，上机检查是否正确。


  
## [练习6.4](ex04.cpp)

> 编写一个与用户交互的函数，要求用户输入一个数字，计算生成该数字的阶乘。在main函数中调用该函数。


  
## [练习6.5](ex05.cpp)

> 编写一个函数输出其实参的绝对值。


  
## 练习6.6

> 说明形参、局部变量以及局部静态变量的区别。编写一个函数，同时达到这三种形式。

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
  
## 练习6.7

> 编写一个函数，当它第一次被调用时返回0，以后每次被调用返回值加1。

```cpp
size_t generate()
{
    static size_t ctr = 0;
    return ctr++;
}
```
  
## 练习6.8

> 编写一个名为 Chapter6.h 的头文件，令其包含6.1节练习中的函数声明。

[Chapter6.h](Chapter6.h)

## 练习6.9

> 编写你自己的fact.cc 和factMain.cc ，这两个文件都应该包含上一小节的练习中编写的 Chapter6.h 头文件。通过这些文件，理解你的编译器是如何支持分离式编译的。

[fact.cpp](fact.cpp)
  
[factMain.cpp](factMain.cpp)

```sh
$ g++ -o ex09 factMain.cpp fact.cpp -std=c++11
$ ./ex09 
120
```
  
## [练习6.10](ex10.cpp)

> 编写一个函数，使用指针形参交换两个整数的值。在代码中调用该函数并输出交换后的结果，以此验证函数的正确性。


  
## [练习6.11](ex11.cpp)

> 编写并验证你自己的reset函数，使其作用于引用类型的参数。


  
## [练习6.12](ex12.cpp)

> 改写6.2.1节练习中的程序，使其引用而非指针交换两个整数的值。你觉得哪种方法更易于使用呢？为什么？


引用更易于使用，不用考虑传递的是指针，避免语法错误；  
使用引用避免拷贝。  
  
## 练习6.13

> 假设 T 是某种类型的名字，说明以下两个函数声明的区别：一个是void f(T), 另一个是 void f(&T)。

void f(T)  
将实参的值拷贝后赋给形参，不能通过改变形参的值来改变实参；  
void f(&T)  
使用引用将形参绑定到实参上，可以通过改变形参来改变实参。  
  
## 练习6.14

> 举一个形参应该是引用类型的例子，再举一个形参不能是引用类型的例子。

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
  
## 练习6.15

> 说明find_char 函数中的三个形参为什么是现在的类型，特别说明为什么s是常量引用而occurs是普通引用？为什么s和occurs是引用类型而c不是？如果令s是普通引用会发生什么情况？如果令occurs是常量引用会发生什么情况？

s不需要改变实参，occurs需要改变实参；s可能会很大，occurs需要改变实参，c没有上述两个需求；如果s是普通的引用可能改变实参；occurs是常量引用则不能改变实参，++occurs会报错
  
## 练习6.16

> 下面的这个函数虽然合法，但是不算特别有用。指出它的局限性并设法改善。
```cpp
bool is_empty(string& s) { return s.empty(); }
```

该函数无需改变实参，故将其设置为const比较好，这样也可以传入const类型的字符串，或字符串字面值。
```cpp
bool is_empty(const string& s) { return s.empty(); }
```
  
## [练习6.17](ex17.cpp)

> 编写一个函数，判断string对象中是否含有大写字母。编写另一个函数，把string对象全部改写成小写形式。在这两个函数中你使用的形参类型相同吗？为什么？


  
## 练习6.18

> 为下面的函数编写函数声明，从给定的名字中推测函数具备的功能。
* (a) 名为 compare 的函数，返回布尔值，两个参数都是 matrix 类的引用。 
* (b) 名为 change_val 的函数，返回vector<int>的迭代器，有两个参数：一个是int，另一个是vector<int>的迭代器。

```cpp
（a）bool compare(matrix &m1,matrix &m2);
（b）vector<int>::iterator change_val(int i,vector<int>::iterator);
```
  
## 练习6.19

> 假定有如下声明，判断哪个调用合法、哪个调用不合法。对于不合法的函数调用，说明原因。
```cpp
double calc(double);
int count(const string &, char);
int sum(vector<int>::iterator, vector<int>::iterator, int);
vector<int> vec(10);
(a) calc(23.4, 55.1);
(b) count("abcda",'a');
(c) calc(66);
(d) sum(vec.begin(), vec.end(), 3.8);
```

（a）不合法，只能一个形参；  
（b）合法；  
（c）合法；  
（d）合法。  
  
## 练习6.20

> 引用形参什么时候应该是常量引用？如果形参应该是常量引用，而我们将其设为了普通引用，会发生什么情况？

无需改变实参的时候应该用常量引用；可能会改变常亮实参，从而导致出错。  
  
## [练习6.21](ex21.cpp)

> 编写一个函数，令其接受两个参数：一个是int型的数，另一个是int指针。函数比较int的值和指针所指的值，返回较大的那个。在该函数中指针的类型应该是什么？


  
## [练习6.22](ex22.cpp)

> 编写一个函数，令其交换两个int指针。


  
## [练习6.23](ex23.cpp)

> 参考本节介绍的几个print函数，根据理解编写你自己的版本。依次调用每个函数使其输入下面定义的i和j:
```cpp
int i = 0, j[2] = { 0, 1 };
```


  
## 练习6.24

> 描述下面这个函数的行为。如果代码中存在问题，请指出并改正。
```cpp
void print(const int ia[10])
{
	for (size_t i = 0; i != 10; ++i)
		cout << ia[i] << endl;
}
```

该函数传递的不是数组是const int*，如果实参不是含10个元素的int数组，可能导致for循环数组越界。修改为：
```cpp
void print(const int (&ia)[10]) { /*...*/ }
```
  
## [练习6.25](ex25.cpp)

> 编写一个main函数，令其接受两个实参。把实参的内容连接成一个string对象并输出出来。


```sh
$ ./ex25 hel lo
hello
```
  
## [练习6.26](ex26.cpp)

> 编写一个程序，使其接受本节所示的选项；输出传递给main函数的实参内容。


```sh
$ ./ex26 -d -o ofile data0
./ex26 -d -o ofile data0 
$ ./ex26 
./ex26 
```
  
## [练习6.27](ex27.cpp)

> 编写一个函数，它的参数是initializer_list<int>类型的对象，函数的功能是计算列表中所有元素的和。


  
## 练习6.28

> 在error_msg函数的第二个版本中包含ErrCode类型的参数，其中循环内的elem是什么类型？

const std::string&
  
## 练习6.29

> 在范围for循环中使用initializer_list对象时，应该将循环控制变量声明成引用类型吗？为什么？

如果拷贝代价小，则无需设置成引用类型；如果拷贝代价大，可以设置成引用类型。（具体的我也不太理解）  
  
## 练习6.30

> 编译第200页的str_subrange函数，看看你的编译器是如何处理函数中的错误的。

g++
```sh
错误#1：error: return-statement with no value, in function returning ‘bool’ [-fpermissive]
错误#2：检查不出，返回true
```
  
## 练习6.31

> 什么情况下返回的引用无效？什么情况下返回常量的引用无效？

返回的引用时局部对象的引用，返回的常量引用是局部常量对象的引用时。
  
## 练习6.32

> 下面的函数合法吗？如果合法，说明其功能；如果不合法，修改其中的错误并解释原因。
```cpp
int &get(int *array, int index) { return array[index]; }
int main()
{
    int ia[10];
    for (int i = 0; i != 10; ++i)
        get(ia, i) = i;
}
```

合法，返回数组ia[0]-ia[9]
  
## [练习6.33](ex33.cpp)

> 编写一个递归函数，输出vector对象的内容。


  
## 练习6.34

> 如果factorial 函数的停止条件如下所示，将发生什么？
```cpp
if (val != 0)
```

如果实参为大于等于0，函数将会多乘以一个1，比如factorial(5)，等价于5 * 4 * 3 * 2 * 1 * 1;  
如果实参小于0，函数将会不断地调用它自身直到程序栈空间耗尽为止。  
  
## 练习6.35

> 在调用`factorial`函数时，为什么我们传入的值是 `val-1` 而非 `val--`？

`val--`会返回未修改的`val`内容，使程序陷入无限循环；`val--`会修改`val`的内容，程序运行结果将不符合预期。  
  
## 练习6.36

> 编写一个函数声明，使其返回数组的引用并且该数组包含10个string对象。不用使用尾置返回类型、decltype或者类型别名。

```cpp
std::string (&fun(std::string (&arrs)[10]))[10];
```
  
## 练习6.37

> 为上一题的函数再写三个声明，一个使用类型别名，另一个使用尾置返回类型，最后一个使用decltype关键字。你觉得哪种形式最好？为什么？

```cpp
using ARRS = std::string[10];
ARRS &fun(ARRS &arrs);
 
auto fun(std::string (&arrs)[10]) -> std::string (&)[10]);
 
std::string arrs1[10];
decltype(arrs1) &fun(decltype(arrs1) &arrs);
```
个人觉得using最好，最简洁。  
  
## 练习6.38

> 修改arrPtr函数，使其返回数组的引用。

```cpp
decltype(arrStr)& arrPtr(int i)
{
          return (i % 2) ? odd : even;
}
```
  
## 练习6.39

> 说明在下面的每组声明中第二条语句是何含义。如果有非法的声明，请指出来。
```cpp
(a) int calc(int, int);
	int calc(const int, const int);
(b) int get();
	double get();
(c) int *reset(int *);
	double *reset(double *);
```

（a）合法，重复声明可以，重复定义不行；  
（b）非法，仅返回值不同；  
（c）合法。  
  
## 练习6.40

> 下面的哪个声明是错误的？为什么？
```cpp
(a) int ff(int a, int b = 0, int c = 0);
(b) char *init(int ht = 24, int wd, char bckgrnd);		
```

（a）正确；  
（b）错误。  
  
## 练习6.41

> 下面的哪个调用是非法的？为什么？哪个调用虽然合法但显然与程序员的初衷不符？为什么？
```cpp
char *init(int ht, int wd = 80, char bckgrnd = ' ');
(a) init();
(b) init(24,10);
(c) init(14,'*');
```

（a）非法，函数第一个形参没有默认实参，必须给实参；  
（b）合法；  
（c）合法，但与初衷不符，char '*'转换成整形了。  
  
## [练习6.42](ex42.cpp)

> 给make_plural函数的第二个形参赋予默认实参's', 利用新版本的函数输出单词success和failure的单数和复数形式。


  
## 练习6.43

> 你会把下面的哪个声明和定义放在头文件中？哪个放在源文件中？为什么？
```cpp
(a) inline bool eq(const BigInt&, const BigInt&) {...}
(b) void putValues(int *arr, int size);
```

（a）放在头文件中，内联函数在程序中可以多次定义，它的多个定义必须完全一致，所以放在头文件中比较好；  
（b）放在头文件中，声明放在头文件中。  
  
## [练习6.44](ex44.cpp)

> 将6.2.2节的isShorter函数改写成内联函数。


  
## 练习6.45

> 回顾在前面的练习中你编写的那些函数，它们应该是内联函数吗？如果是，将它们改写成内联函数；如果不是，说明原因。

6.38和6.42应该是内联函数；6.4不应该是，规模不小，调用不频繁。  
  
## 练习6.46

> 能把isShorter函数定义成constexpr函数吗？如果能，将它改写成constxpre函数；如果不能，说明原因。

不能，因为std::string::size()；  不是一个constexpr函数，s1.size() == s2.size()；  不是一个常量表达式。  
  
## [练习6.47](ex47.cpp)

> 改写6.3.2节练习中使用递归输出vector内容的程序，使其有条件地输出与执行过程有关的信息。例如，每次调用时输出vector对象的大小。分别在打开和关闭调试器的情况下编译并执行这个程序。


  
## 练习6.48

> 说明下面这个循环的含义，它对assert的使用合理吗？
```cpp
string s;
while (cin >> s && s != sought) { } //空函数体
assert(cin);
```

合理，当输入结束时终止程序。  
  
## 练习6.49

> 什么是候选函数？什么是可行函数？

候选函数具备两个特征：一是与被调用的函数同名，二是其声明在调用点可见。  
可行函数是从候选函数中选出的，有两个特征：一是其形参数量与本次调用提供的实参数量相等，二是每个实参的类型与对应的形参类型相同，或者能转换成形参的类型。  
  
## 练习6.50

> 已知有第217页对函数 f 的声明，对于下面的每一个调用列出可行函数。其中哪个函数是最佳匹配？如果调用不合法，是因为没有可匹配的函数还是因为调用具有二义性？
```cpp
(a) f(2.56, 42)
(b) f(42)
(c) f(42, 0)
(d) f(2.56, 3.14)
```

（a）二义性；（b）最佳匹配void f(int)；（c）最佳匹配void f(int, int)；（d）最佳匹配void f(double, double = 3.14)。  
  
## [练习6.51](ex51.cpp)

> 编写函数f的4版本，令其各输出一条可以区分的消息。验证上一个练习的答案，如果你的回答错了，反复研究本节内容直到你弄清自己错在何处。


  
## 练习6.52

> 已知有如下声明：
```cpp
void manip(int ,int);
double dobj;
```
请指出下列调用中每个类型转换的等级。
```cpp
(a) manip('a', 'z');
(b) manip(55.4, dobj);
```

（a）3等级，通过类型提升实现的匹配；  
（b）4等级，通过算数类型转换。  
  
## 练习6.53

> 说明下列每组声明中的第二条语句会产生什么影响，并指出哪些不合法（如果有的话）。
```cpp
(a) int calc(int&, int&); 
	int calc(const int&, const int&); 
(b) int calc(char*, char*);
	int calc(const char*, const char*);
(c) int calc(char*, char*);
	int calc(char* const, char* const);
```

（a）合法，实参可以为const int；  
（b）合法，实参可以为const char*；  
（c）合法，顶层const，声明重复（可以重复声明，不可重复定义）。  
  
## 练习6.54

> 编写函数的声明，令其接受两个int形参并返回类型也是int；然后声明一个vector对象，令其元素是指向该函数的指针。

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
  
## 练习6.55

> 编写4个函数，分别对两个int值执行加、减、乘、除运算；在上一题创建的vector对象中保存指向这些函数的指针。

```cpp
int add(int a, int b) { return a + b; }
int subtract(int a, int b) { return a - b; }
int multiply(int a, int b) { return a * b; }
int divide(int a, int b) { return b != 0 ? a / b : 0; }
```
  
## [练习6.56](ex56.cpp)

> 调用上述vector对象中的每个元素并输出结果。

