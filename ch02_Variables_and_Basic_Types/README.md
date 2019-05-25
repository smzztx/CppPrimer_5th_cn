## 练习2.1

> 类型 int、long、long long 和 short 的区别是什么？无符号类型和带符号类型的区别是什么？float 和 double的区别是什么？

C++语言规定一个int至少和一个short一样大，一个long至少和一个int一样大，一个long long至少和一个long一样大。每个的最小尺寸分别为：short，16位；int，16位；long，32位；long long，64位。  
除去布尔型和扩展的字符型外，其他整形可以划分为带符号的和无符号的两种。带符号类型可以表示正数、负数或0，无符号类型则仅能表示大于等于0的值。  
float最小尺寸为6位有效值，double最小尺寸为10位有效值。
  
## 练习2.2

> 计算按揭贷款时，对于利率、本金和付款分别应选择何种数据类型？说明你的理由。

都选用double，利率4.5%=0.045,本金和付款金额都是以元为单位，钱的最小金额是分，需要精确到小数点后两位，所以都选用double。
  
## 练习2.3

> 读程序写结果。
```cpp
unsigned u = 10, u2 = 42;
std::cout << u2 - u << std::endl;
std::cout << u - u2 << std::endl;
int i = 10, i2 = 42;
std::cout << i2 - i << std::endl;
std::cout << i - i2 << std::endl;
std::cout << i - u << std::endl;
std::cout << u - i << std::endl;
```

```
4294967264
32
32
-32
0
0
```
  
## [练习2.4](ex04.cpp)

> 编写程序检查你的估计是否正确，如果不正确，请仔细研读本节直到弄明白问题所在。

## 练习2.5

> 指出下述字面值的数据类型并说明每一组内几种字面值的区别：
- (a) 'a', L'a', "a", L"a"
- (b) 10, 10u, 10L, 10uL, 012, 0xC
- (c) 3.14, 3.14f, 3.14L
- (d) 10, 10u, 10., 10e-2

（a）字符字面值，宽字符字面值，字符串字面值，宽字符串字面值；  
（b）整形字面值，无符号整形字面值，长整形字面值，无符号长整形字面值，八进制整形字面值，十六进制整形字面值；  
（c）浮点型字面值，单精度浮点型字面值，扩展精度浮点型字面值；  
（d）整形字面值，无符号整形字面值，浮点型字面值，浮点型字面值。

## 练习2.6

> 下面两组定义是否有区别，如果有，请叙述之：
```cpp
int month = 9, day = 7;
int month = 09, day = 07;
```

（a）十进制整形；  
（b）八进制整形，八进制总没有09。  

## 练习2.7

> 下述字面值表示何种含义？它们各自的数据类型是什么？
- (a) "Who goes with F\145rgus?\012"
- (b) 3.14e1L
- (c) 1024f
- (d) 3.14L

(a)string；  
(b)long double；  
(c)非法，整形字面值不可加后缀f；  
(d)long double。

## [练习2.8](ex08.cpp)

> 请利用转义序列编写一段程序，要求先输出 2M，然后转到新一行。修改程序使其先输出 2，然后输出制表符，再输出 M，最后转到新一行。

## 练习2.9

> 解释下列定义的含义，对于非法的定义，请说明错在何处并将其改正。
- (a) std::cin >> int input_value;
- (b) int i = { 3.14 };
- (c) double salary = wage = 9999.99;
- (d) int i = 3.14;

（编译时记得使用C++11标准编译"-std=c++11”）  
(a)非法，>>运算符后不能定义；  
(b)非法，不能执行强制转换；  
(c)非法，同一语句的初始化应该分别进行；  
(d)合法，已强制转换。

## 练习2.10

> 下列变量的初值分别是什么？
```cpp
std::string global_str;
int global_int;
int main()
{
    int local_int;
    std::string local_str;
}
```

global_str,local_str为空字符串；  
global_int为0；  
local_int未初始化，没有初始值（测试下来也是0，最好都初始化掉）。

## 练习2.11

> 指出下面的语句是声明还是定义：
- (a) extern int ix = 1024;
- (b) int iy;
- (c) extern int iz;

（a）定义；  
（b）定义；  
（c）声明。

## 练习2.12

> 请指出下面的名字中哪些是非法的？
- (a) int double = 3.14;
- (b) int _;
- (c) int catch-22;
- (d) int 1_or_2 = 1;
- (e) double Double = 3.14;

（a）非法，关键词；  
（b）合法；  
（c）非法；  
（d）非法，字母、下划线开头；  
（e）合法。

## 练习2.13

> 下面程序中 j 的值是多少？
```cpp
int i = 42;
int main()
{
    int i = 100;
    int j = i;
}
```

100

## 练习2.14

> 下面的程序合法吗？如果合法，它将输出什么？
```cpp
    int i = 100, sum = 0;
    for (int i = 0; i != 10; ++i)
        sum += i;
    std::cout << i << " " << sum << std::endl;
```

100 45

## 练习2.15

> 下面的哪个定义是不合法的？为什么？
- (a) int ival = 1.01;
- (b) int &rval1 = 1.01;
- (c) int &rval2 = ival;
- (d) int &rval3;

（a）合法；（b）不合法，引用类型的初始值必须是一个对象；  
（c）合法；（d）不合法，引用类型必须初始化。

## 练习2.16

> 考察下面的所有赋值然后回答：哪些赋值是不合法的？为什么？哪些赋值是合法的？它们执行了哪些操作？
```
int i = 0, &r1 = i; double d = 0, &r2 = d;
- (a) r2 = 3.14159;
- (b) r2 = r1;
- (c) i = r2;
- (d) r1 = d;
```

（a）合法；  
（b）合法；  
（c）合法；  
（d）合法。

## 练习2.17

> 执行下面的代码段将输出什么结果？
```cpp
int i, &ri = i;
i = 5; ri = 10;
std::cout << i << " " << ri << std::endl;
```

10 10

## 练习2.18

> 编写代码分别改变指针的值以及指针所指对象的值。

```cpp
int a = 0, b = 1;
int *p1 = &a, *p2 = p1;

// change the value of a pointer.
p1 = &b;
// change the value to which the pointer points
*p2 = b;
```

## 练习2.19

> 说明指针和引用的主要区别

1.指针本身就是一个对象，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象；2.指针无须在定义时赋初值。

## 练习2.20

> 请叙述下面这段代码的作用。
```cpp
int i = 42;
int *p1 = &i; 
*p1 = *p1 * *p1;
```

p指向i，i最后的值为1746（42*42）。

## 练习2.21

> 请解释下述定义。在这些定义中有非法的吗？如果有，为什么？
```
int i = 0;
(a) double* dp = &i;
(b) int *ip = i;
(c) int *p = &i;
```

（a）非法，一个是double*，一个是int*；
（b）非法，一个是int*，一个是int；
（c）合法。

## 练习2.22

> 假设 p 是一个 int 型指针，请说明下述代码的含义。
```cpp
if (p) // ...
if (*p) // ...
```

指针是不是空指针；  
指针所指的对象是不是0。

## 练习2.23

> 给定指针 p，你能知道它是否指向了一个合法的对象吗？如果能，叙述判断的思路；如果不能，也请说明原因。

不能，不能判断指针是否有效。

## 练习2.24

> 在下面这段代码中为什么 p 合法而 lp 非法？
```cpp
int i = 42;
void *p = &i;
long *lp = &i;
```

类型不一样，void*可以表示任何类型的对象。

## 练习2.25

> 说明下列变量的类型和值。
- (a) int* ip, i, &r = i;
- (b) int i, *ip = 0;
- (c) int* ip, ip2;

（a）指向int的指针，int类型，int的引用；  
（b）int类型，int类型的指针；  
（c）int类型指针，int类型。

## 练习2.26

> 下面哪些语句是合法的？如果不合法，请说明为什么？
```cpp
const int buf;
int cnt = 0;
const int sz = cnt;
++cnt; ++sz;
```

（a）不合法，const int必须初始化；  
（b）合法；  
（c）合法；  
（d）++cnt，合法；++sz，不合法，const int不能改变。

## 练习2.27

> 下面的哪些初始化是合法的？请说明原因。
```cpp
int i = -1, &r = 0;
int *const p2 = &i2;
const int i = -1, &r = 0;
const int *const p3 = &i2;
const int *p1 = &i2;
const int &const r2;
const int i2 = i, &r = i;
```

（a）0是常量，&r不是对常量的引用，所以可以改变，这显然是不对的；  
（b）如果i2是const int，这是不对的；  
（c）合法；  
（d）合法；  
（e）合法；  
（f）不合法，没有初始化；  
（g）合法。
## 练习2.28

> 说明下面的这些定义是什么意思，挑出其中不合法的。
```cpp
int i, *const cp;
int *p1, *const p2;
const int ic, &r = ic;
const int *const p3;
const int *p;
```

（a）不合法，常量指针未初始化；  
（b）不合法，常量指针未初始化；  
（c）不合法，常量ic未初始化；  
（d）不合法，常量指针未初始化；  
（e）合法，指向常量的指针可以不初始化。

## 练习2.29

> 假设已有上一个练习中定义的那些变量，则下面的哪些语句是合法的？请说明原因。
```cpp
i = ic;
p1 = p3;
p1 = &ic;
p3 = &ic;
p2 = p1;
ic = *p3;
```

（a）合法；  
（b）非法，p3是指向const int的指针；  
（c）非法，ic是const int；  
（d）非法，p3是常量指针，不能再次赋值；  
（e）非法，p2是常量指针，不能再次赋值；  
（f）非法，ic是const int。

## 练习2.30

> 对于下面的这些语句，请说明对象被声明成了顶层const还是底层const？
```cpp
const int v2 = 0; int v1 = v2;
int *p1 = &v1, &r1 = v1;
const int *p2 = &v2, *const p3 = &i, &r2 = v2;
```

v2不能改变，是顶层const；v1都不是；p1都不是，r1都不是；p2所指的对象不能改变，底层const；p3既是顶层，又是底层；r2底层。

## 练习2.31

> 假设已有上一个练习中所做的那些声明，则下面的哪些语句是合法的？请说明顶层const和底层const在每个例子中有何体现。
```cpp
r1 = v2;
p1 = p2;
p2 = p1;
p1 = p3;
p2 = p3;
```

```cpp
r1 = v2; // 合法，v2为顶层const
p1 = p2; // 非法，p2为底层const
p2 = p1; // 合法
p1 = p3; // 非法
p2 = p3; // 合法
```

## 练习2.32

> 下面的代码是否合法？如果非法，请设法将其修改正确。
```
int null = 0, *p = null;
```

非法，int null = 0, *p = &null;。

## 练习2.33

> 利用本节定义的变量，判断下列语句的运行结果。
```cpp
a=42;
b=42;
c=42;
d=42;
e=42;
g=42;
```

a=42; // 合法  
b=42; // 合法  
c=42; // 合法  
d=42; // 非法  
e=42; // 非法  
g=42; // 非法

## [练习2.34](ex34.cpp)

> 基于上一个练习中的变量和语句编写一段程序，输出赋值前后变量的内容，你刚才的推断正确吗？如果不对，请反复研读本节的示例直到你明白错在何处为止。

## 练习2.35

> 判断下列定义推断出的类型是什么，然后编写程序进行验证。
```cpp
const int i = 42;
auto j = i; const auto &k = i; auto *p = &i; 
const auto j2 = i, &k2 = i;
```

j int；k 常量int的引用；常量int的指针；j2 常量int；k2常量 int的引用

## 练习2.36

> 关于下面的代码，请指出每一个变量的类型以及程序结束时它们各自的值。
```cpp
int a = 3, b = 4;
decltype(a) c = a;
decltype((b)) d = a;
++c;
++d;
```

a int；b int；c int；d int &。  
4；4；4；4。

## 练习2.37

> 赋值是会产生引用的一类典型表达式，引用的类型就是左值的类型。也就是说，如果 i 是 int，则表达式 i=x 的类型是 int&。根据这一特点，请指出下面的代码中每一个变量的类型和值。
```cpp
int a = 3, b = 4;
decltype(a) c = a;
decltype(a = b) d = a;
```

a int 3；  
b int 4；  
c int 3；  
d int & 3。

## 练习2.38

> 说明由decltype 指定类型和由auto指定类型有何区别。请举一个例子，decltype指定的类型与auto指定的类型一样；再举一个例子，decltype指定的类型与auto指定的类型不一样。

如果使用引用类型，auto会识别为其引用对象的类型；  
decltype会识别为引用的类型；  
decltype(())的差别；  
顶层const差异。  

## 练习2.39

> 编译下面的程序观察其运行结果，注意，如果忘记写类定义体后面的分号会发生什么情况？记录下相关的信息，以后可能会有用。
```cpp
struct Foo { /* 此处为空  */ } // 注意：没有分号
int main()
{
    return 0;
}
```

```cpp
struct Foo { /* empty  */ } // Note: no semicolon
int main()
{
    return 0;
}
```
Error message: [Error] expected ';' after struct definition

## 练习2.40

> 根据自己的理解写出 Sales_data 类，最好与书中的例子有所区别。

```cpp
struct Sale_data
{
    std::string bookNo;
    std::string bookName;
    unsigned units_sold = 0;
    double revenue = 0.0;
    double price = 0.0;
    //...
}
```

## 练习2.41

> 使用你自己的Sale_data类重写1.5.1节（第20页）、1.5.2节（第21页）和1.6节（第22页）的练习。眼下先把Sales_data类的定义和main函数放在一个文件里。

### [1.5.1（这里有３题，我这里只简单实现该类型的输入、相加和输出）](ex41_1.cpp)
### [1.5.2和1.6（这里也有３题，我这里只实现读取多条销售记录，并统计每个ISBN有几条销售记录，每个ISBN的记录聚在一起）](ex41_2.cpp)

## 练习2.42

> 根据你自己的理解重写一个Sales_data.h头文件，并以此为基础重做2.6.2节（第67页）的练习。

[Sales_data.h](Sales_data.h)
### [1.5.1（这里有３题，我这里只简单实现该类型的输入、相加和输出）](ex42_1.cpp)
### [1.5.2和1.6（这里也有３题，我这里只实现读取多条销售记录，并统计每个ISBN有几条销售记录，每个ISBN的记录聚在一起）](ex42_2.cpp)