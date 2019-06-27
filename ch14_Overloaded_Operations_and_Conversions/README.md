## 练习14.1

> 在什么情况下重载的运算符与内置运算符有所区别？在什么情况下重载的运算符又与内置运算符一样？

有所区别：  
当一个重载运算符是成员函数时，this绑定到左侧的运算对象；  
逻辑与运算符、逻辑或运算符和逗号运算符的运算对象求值顺序规则无法保留下来；  
&&和||运算符的重载版本也无法保留内置运算符的短路求值属性，两个运算对象总是会被求值。  
一样：  
对于一个重载的运算符来说，其优先级和结合律与对应的内置运算保持一致。  

## 练习14.2

> 为 Sales_data 编写重载的输入、输出、加法和复合赋值运算符。

[Sales_data_ex02.h](Sales_data_ex02.h)


[ex02.cpp](ex02.cpp)


## 练习14.3

> string 和 vector 都定义了重载的==以比较各自的对象，假设 svec1 和 svec2 是存放 string 的 vector，确定在下面的表达式中分别使用了哪个版本的==？
```cpp
(a) "cobble" == "stone"
(b) svec1[0] == svec2[0]
(c) svec1 == svec2
(d) "svec1[0] == "stone"
``` 

（a）没有哪个版本；  
（b）string；  
（c）vector；  
（d）string。  

## 练习14.4

> 如何确定下列运算符是否应该是类的成员？
```cpp
(a) %
(b) %=
(c) ++
(d) ->
(e) <<
(f) &&
(g) ==
(h) ()
```

（a）不应该；（b）应该；（c）应该；（d）必须是成员；（e）不应该；（f）不应该；（g）不应该；（h）必须是成员。  

## 练习14.5

> 在7.5.1节中的练习7.40中，编写了下列类中某一个的框架，请问在这个类中应该定义重载的运算符吗？如果是，请写出来。
```cpp
(a) Book
(b) Date
(c) Employee
(d) Vehicle
(e) Object
(f) Tree
```

[book_ex05.h](book_ex05.h)


[book_ex05.cpp](book_ex05.cpp)


[ex05.cpp](ex05.cpp)


## 练习14.6

> 为你的 Sales_data 类定义输出运算符。

参见14.2。  

## 练习14.7

> 你在13.5节的练习中曾经编写了一个String类，为它定义一个输出运算符。

[String_ex07.h](String_ex07.h)


[ex07.cpp](ex07.cpp)


## 练习14.8

> 你在7.5.1节中的练习中曾经选择并编写了一个类，为它定义一个输出运算符。

参见14.5。  

## 练习14.9

> 为你的 Sales_data 类定义输入运算符。

参见14.2。  

## 练习14.10

> 对于 Sales_data 的输入运算符来说如果给定了下面的输入将发生什么情况？
```cpp
(a) 0-201-99999-9 10 24.95
(b) 10 24.95 0-210-99999-9
```

（a）正确格式；（b）错误格式，但是.95被保存到price，10是ISBN，最终输出为：10 24 22.8 0.95。  

## 练习14.11

> 下面的 Sales_data 输入运算符存在错误吗？如果有，请指出来。对于这个输入运算符如果仍然给定上个练习的输入将会发生什么情况？
```cpp
istream& operator>>(istream& in, Sales_data& s)
{
	double price;
	in >> s.bookNo >> s.units_sold >> price;
	s.revence = s.units_sold >> price;
	return in;
}
```

没有输入检查，与上题结果一样。  

## 练习14.12

> 你在7.5.1节的练习中曾经选择并编写了一个类，为它定义一个输入运算符并确保该运算符可以处理输入错误。

参见14.5。  

## 练习14.13

> 你认为 Sales_data 类还应该支持哪些其他算术运算符？如果有的话，请给出它们的定义。

添加加法和减法。  
  
[Sales_data_ex13.h](Sales_data_ex13.h)

  
[ex13.cpp](ex13.cpp)

  
## 练习14.14

> 你觉得为什么调用 operator+= 来定义operator+ 比其他方法更有效？

operator+需要创建新对象；operator+=只使用一个对象。调用operator+=为用户重载的运算符，更简洁，更符合实际逻辑。  

## 练习14.15

> 你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有其他算术运算符吗？如果是，请实现它们；如果不是，解释原因。

参见14.5，暂不添加。

## 练习14.16

> 为你的 StrBlob 类、StrBlobPtr 类、StrVec 类和 String 类分别定义相等运算符和不相等运算符。

[StrBlob_ex16.h](StrBlob_ex16.h)

  
[ex16_1.cpp](ex16_1.cpp)  


[StrVec_ex16.h](StrVec_ex16.h)

  
[ex16_2.cpp](ex16_2.cpp)  

  
[String_ex16.h](String_ex16.h)  

  
[ex16_3.cpp](ex16_3.cpp)


## 练习14.17

> 你在7.5.1节中的练习7.40中曾经选择并编写了一个类，你认为它应该含有相等运算符吗？如果是，请实现它；如果不是，解释原因。

参见14.5。  

## 练习14.18

> 为你的 StrBlob 类、StrBlobPtr 类、StrVec 类和 String 类分别定义关系运算符。

[StrBlob_ex18.h](StrBlob_ex18.h)

  
[ex18_1.cpp](ex18_1.cpp)

  
[StrVec_ex18.h](StrVec_ex18.h)

  
[ex18_2.cpp](ex18_2.cpp)

  
[String_ex18.h](String_ex18.h)

  
[ex18_3.cpp](ex18_3.cpp)


## 练习14.19

> 你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有关系运算符吗？如果是，请实现它；如果不是，解释原因。

[book_ex19.h](book_ex19.h)

  
[book_ex19.cpp](book_ex19.cpp)

  
[ex19.cpp](ex19.cpp)


## 练习14.20

> 为你的 Sales_data 类定义加法和复合赋值运算符。

参见14.20。  

## 练习14.21

> 编写 Sales_data 类的+ 和+= 运算符，使得 + 执行实际的加法操作而 += 调用+。相比14.3节和14.4节对这两个运算符的定义，本题的定义有何缺点？试讨论之。

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

## 练习14.22

> 定义赋值运算符的一个新版本，使得我们能把一个表示 ISBN 的 string 赋给一个 Sales_data 对象。

[Sales_data_ex22.h](Sales_data_ex22.h)

  
[ex22.cpp](ex22.cpp)


## 练习14.23

> 为你的StrVec 类定义一个 initializer_list 赋值运算符。

[StrVec_ex23.h](StrVec_ex23.h)

  
[ex23.cpp](ex23.cpp)


## 练习14.24

> 你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有拷贝赋值和移动赋值运算符吗？如果是，请实现它们。

[book_ex24.h](book_ex24.h)

  
[book_ex24.cpp](book_ex24.cpp)

  
[ex24.cpp](ex24.cpp)

  
## 练习14.25

> 上题的这个类还需要定义其他赋值运算符吗？如果是，请实现它们；同时说明运算对象应该是什么类型并解释原因。

参见14.24。  
  
## 练习14.26

> 为你的 StrBlob 类、StrBlobPtr 类、StrVec 类和 String 类定义下标运算符。

[StrBlob_ex26.h](StrBlob_ex26.h)

  
[ex26_1.cpp](ex26_1.cpp)

  
[StrVec_ex26.h](StrVec_ex26.h)

  
[ex26_2.cpp](ex26_2.cpp)

  
[String_ex26.h](String_ex26.h)

  
[ex26_3.cpp](ex26_3.cpp)

  
## 练习14.27

> 为你的 StrBlobPtr 类添加递增和递减运算符。
[StrBlob_ex27.h](StrBlob_ex27.h)
  
[ex27.cpp](ex27.cpp)

  
## 练习14.28

> 为你的 StrBlobPtr 类添加加法和减法运算符，使其可以实现指针的算术运算。

参见14.27。
  
## 练习14.29

> 为什么不定义const 版本的递增和递减运算符？

const的StrBlob不能改变成员变量，而递增和递减运算符需要改变其状态，本身就是矛盾的。
  
## 练习14.30

> 为你的 StrBlobPtr 类和在12.1.6节练习12.22中定义的 ConstStrBlobPtr 的类分别添加解引用运算符和箭头运算符。注意：因为 ConstStrBlobPtr 的数据成员指向const vector，所以ConstStrBlobPtr 中的运算符必须返回常量引用。

[StrBlob_ex30.h](StrBlob_ex30.h)

  
[ex30.cpp](ex30.cpp)

  
## 练习14.31
> 我们的 StrBlobPtr 类没有定义拷贝构造函数、赋值运算符和析构函数，为什么？

StrBlobPtr的数据成员的类型为std::weak_ptr<std::vector<std::string>>和内置类型，前者有自己的三个函数，后者也无需定义，使用默认的即可。
  
## 练习14.32
> 定义一个类令其含有指向 StrBlobPtr 对象的指针，为这个类定义重载的建投运算符。

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
  
## 练习14.33
> 一个重载的函数调用运算符应该接受几个运算对象？

可以接受的对象为0-256个。

## [练习14.34](ex34.cpp)
> 定义一个函数对象类，令其执行 if-then-else 的操作：该类的调用运算符接受三个形参，它首先检查第一个形参，如果成功返回第二个形参的值，如果不成功返回第三个形参的值。


  
## [练习14.35](ex35.cpp)
> 编写一个类似 PrintString 的类，令其从 istream 中读取一行输入，然后返回一个表示我们所读内容的 string 。如果读取失败，返回空 string 。


  
## [练习14.36](ex36.cpp)
> 使用前一个练习定义的类读取标准输入，将每一行保存为 vector 的一个元素。


  
## [练习14.37](ex37.cpp)
> 编写一个类令其检查两个值是否相等。使用该对象及标准库算法编写程序，令其替换某个序列中具有给定值的所有实例。


## [练习14.38](ex38.cpp)

> 编写一个类令其检查某个给定的 string 对象的长度是否与一个阈值相等。使用该对象编写程序，统计并报告在输入的文件中长度为1的单词有多少个，长度为2的单词有多少个、......、长度为10的单词有多少个。


  
## [练习14.39](ex39.cpp)

> 修改上一题的程序令其报告长度在1到9之间的单词有多少个、长度在10以上的单词有多少个。



## [练习14.40](ex40.cpp)

> 重新编写10.3.2节的biggies 函数，使用函数对象替换其中的 lambda 表达式。


  
## 练习14.41

> 你认为 C++ 11 标准为什么要增加 lambda？对于你自己来说，什么情况下会使用 lambda，什么情况下会使用类？

当传递的函数使用次数少且实现简单时，使用lambda；反之则使用类。  
  
## [练习14.42](ex42.cpp)

> 使用标准库函数对象及适配器定义一条表达式，令其
```
(a) 统计大于1024的值有多少个。 
(b) 找到第一个不等于pooh的字符串。
(c)将所有的值乘以2。
```


  
## [练习14.43](ex43.cpp)

> 使用标准库函数对象判断一个给定的int值是否能被 int 容器中的所有元素整除。


  
## [练习14.44](ex44.cpp)

> 编写一个简单的桌面计算器使其能处理二元运算。


  
## 练习14.45

> 编写类型转换运算符将一个 Sales_data 对象分别转换成 string 和 double，你认为这些运算符的返回值应该是什么？

转换成string的返回值应该是bookNo；转换成double的返回值应该是revenue。
  
## 练习14.46

> 你认为应该为 Sales_data 类定义上面两种类型转换运算符吗？应该把它们声明成 explicit 的吗？为什么？

不应该，类类型与转换类型之间不存在明显的映射关系，这样的类型转换可能具有误导性。应该声明成explicit，可以防止异常发生。
  
## 练习14.47

> 说明下面这两个类型转换运算符的区别。
```cpp
struct Integral {
	operator const int();
	operator int() const;
}
```

前者没什么意义，会被编译器忽略；后者不能改变对象。
  
## 练习14.48

> 你在7.5.1节的练习7.40中曾经选择并编写了一个类，你认为它应该含有向 bool 的类型转换运算符吗？如果是，解释原因并说明该运算符是否应该是 explicit的；如果不是，也请解释原因。

应该含有向bool的类型转换运算符，应该是explicit，可以防止自动转换。
  
## 练习14.49

> 为上一题提到的类定义一个转换目标是 bool 的类型转换运算符，先不用在意这么做是否应该。

[book_ex49.h](book_ex49.h)

  
[book_ex49.cpp](book_ex49.cpp)

  
[ex49.cpp](ex49.cpp)


  
## 练习14.50

> 在初始化 ex1 和 ex2 的过程中，可能用到哪些类类型的转换序列呢？说明初始化是否正确并解释原因。
```cpp
struct LongDouble {
	LongDouble(double = 0.0);
	operator double();
	operator float();
};
LongDouble ldObj;
int ex1 = ldObj;
float ex2 = ldObj;
```

前者转换具有二义性，可能用到operator double()和operator float()；后者正确。
  
## 练习14.51

> 在调用 calc 的过程中，可能用到哪些类型转换序列呢？说明最佳可行函数是如何被选出来的。
```cpp
void calc(int);
void calc(LongDouble);
double dval;
calc(dval);  //哪个calc？
```

void calc(int);
实参类型转换到形参类型有如下几个等级：
1.精确匹配；
2.通过const转换实现匹配；
3.通过类型提升实现的匹配；
4.通过算数类型转换或指针转换实现的匹配；
5.通过类类型转换实现的匹配。
详见6.6.1实参类型转换。
  
## 练习14.52

> 在下面的加法表达式中分别选用了哪个operator+？列出候选函数、可行函数及为每个可行函数的实参执行的类型转换：
```cpp
struct Longdouble {
	//用于演示的成员operator+;在通常情况下是个非成员
	LongDouble operator+(const SmallInt&);
	//其他成员与14.9.2节一致
};
LongDouble operator+(LongDouble&, double);
SmallInt si;
LongDouble ld;
ld = si + ld;
ld = ld + si;
```

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
  
## [练习14.53](ex53.cpp)

> 假设我们已经定义了如第522页所示的SmallInt，判断下面的加法表达式是否合法。如果合法，使用了哪个加法运算符？如果不合法，应该怎样修改代码才能使其合法？
```cpp
SmallInt si;
double d = si + 3.14;
```

