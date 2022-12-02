## 练习7.1

> 使用2.6.1节定义的Sales_data类为1.6节的交易处理程序编写一个新版本。

见习题2.41。
  
## [练习7.2](Sales_data_ex02)

> 曾在2.6.2节的练习中编写了一个Sales_data类，请向这个类添加combine函数和isbn成员。


  
## [练习7.3](ex03.cpp)

> 修改7.1.1节的交易处理程序，令其使用这些成员。


  
## [练习7.4](Person_ex04.h)

> 编写一个名为Person的类，使其表示人员的姓名和地址。使用string对象存放这些元素，接下来的练习将不断充实这个类的其他特征。


  
## [练习7.5](Person_ex05.h)

> 在你的Person类中提供一些操作使其能够返回姓名和地址。这些函数是否应该是const的呢？解释原因。

应该是const，这两个成员函数只需读取成员对象，无需改变成员对象。

  
## [练习7.6](Sales_data_ex06.h)

> 对于函数add、read和print，定义你自己的版本。


  
## [练习7.7](ex07.cpp)

> 使用这些新函数重写7.1.2节练习中的程序。


  
## 练习7.8

> 为什么read函数将其Sales_data参数定义成普通的引用，而print函数将其参数定义成常量引用？

因为read函数需要改变成员对象；而print只需读取成员对象。
  
## [练习7.9](Person_ex09.h)

> 对于7.1.2节练习中代码，添加读取和打印Person对象的操作。


  
## 练习7.10

> 在下面这条if语句中，条件部分的作用是什么？
```cpp
if (read(read(cin, data1), data2))
```

读入data1和data2，并判断返回是否为真。
  
## 练习7.11

> 在你的Sales_data类中添加构造函数，然后编写一段程序令其用到每个构造函数。

[Sales_data_ex11.h](Sales_data_ex11.h)


[ex11.cpp](ex11.cpp)

  
## 练习7.12

> 把只接受一个istream 作为参数的构造函数移到类的内部。

[Sales_data_ex12.h](Sales_data_ex12.h)


[ex12.cpp](ex12.cpp)

  
## [练习7.13](ex13.cpp)

> 使用istream构造函数重写第229页的程序。


  
## 练习7.14

> 编写一个构造函数，令其用我们提供的类内初始值显式地初始化成员。

```cpp
Sales_data() : bookNo(""), units_sold(0) , revenue(0){ }
```
  
## [练习7.15](Person_ex15.h)

> 为你的 Person 类添加正确的构造函数。


  
## 练习7.16

> 在类的定义中对于访问说明符出现的位置和次数有限定吗？如果有，是什么？什么样的成员应该定义在public 说明符之后？什么样的成员应该定义在private 说明符之后？

一个类可以包含0个或多个访问说明符，而且对于某个访问说明符能出现多少次也没有严格的限定。  
public：成员在整个程序内可被访问，public成员定义类的接口；  
private：成员可以被类的成员函数访问，但是不能被使用该类的代码访问，private部分封装了（即隐藏了）类的实现细节。  
  
## 练习7.17

> 使用class 和 struct 时有区别吗？如果有，是什么？

struct默认的访问权限是public；  
class默认的访问权限是private。  
  
## 练习7.18

> 封装是何含义？它有什么用处？

封装是实现与接口的分离。它隐藏了类型的实现细节。（在C++中，封装是通过将实现放在一个类的私有部分来实现的）  
封装有两个重要的优点：  
1.确保用户代码不会无意间破坏封装对象的状态；  
2.被封装的类的具体实现细节可以随时改变，而无须调整用户级别的代码。  
  
## 练习7.19

> 在你的Person 类中，你将把哪些成员声明成public 的？哪些声明成private 的？解释你这样做的原因。

```cpp
struct Person
{
public:
    Person() : name(""), address(""){}
    Person(const std::string &sname, const std::string &saddress = "") : name(sname), address(saddress){}
    Person(std::istream &is){read(is, *this);}
    std::string get_name() const{return name;}
    std::string get_address() const{return address;}
private:
    std::string name;
    std::string address;
};
```
接口应该被定义为公共的，数据不应该暴露在类之外。
  
## 练习7.20

> 友元在什么时候有用？请分别举出使用友元的利弊。

类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元。  
优点：  
外部函数可以方便地使用类的成员，而不需要显示地给它们加上类名；  
可以方便地访问所有非公有成员；  
有时，对类的用户更容易读懂。  
缺点：  
减少封装和可维护性；  
代码冗长，类内的声明，类外函数声明。  
  
## 练习7.21

> 修改你的Sales_data 类使其隐藏实现的细节。你之前编写的关于Sales_data操作的程序应该继续使用，借助类的新定义重新编译该程序，确保其正常工作。

[Sales_data_ex21.h](Sales_data_ex21.h)


[ex21.cpp](ex21.cpp)

  
## 练习7.22

> 修改你的Person 类使其隐藏实现的细节。

[Person_ex22.h](Person_ex22.h)


[ex22.cpp](ex22.cpp)

  
## [练习7.23](Screen_ex23.h)

> 编写你自己的Screen 类型。


  
## [练习7.24](Screen_ex24.h)

> 给你的Screen 类添加三个构造函数：一个默认构造函数；另一个构造函数接受宽和高的值，然后将contents 初始化成给定数量的空白；第三个构造函数接受宽和高的值以及一个字符，该字符作为初始化后屏幕的内容。


  
## 练习7.25

> Screen 能安全地依赖于拷贝和赋值操作的默认版本吗？如果能，为什么？如果不能？为什么？

能，Screen类中只有内置类型和string可以使用拷贝和赋值操作，见7.15。  
  
## 练习7.26

> 将Sales_data::avg_price 定义成内联函数。

[Sales_data_ex26.h](Sales_data_ex26.h)


[ex26.cpp](ex26.cpp)

  
## 练习7.27

> 给你自己的Screen 类添加move、set 和display 函数，通过执行下面的代码检验你的类是否正确。
```cpp
Screen myScreen(5, 5, 'X');
myScreen.move(4, 0).set('#').display(cout);
cout << "\n";
myScreen.display(cout);
cout << "\n";
```

[Screen_ex27.h](Screen_ex27.h)

  
[ex27.cpp](ex27.cpp)

  
## 练习7.28

> 如果move、set和display函数的返回类型不是Screen& 而是Screen，则在上一个练习中奖会发生什么？

返回类型是Screen&的输出：  
XXXXXXXXXXXXXXXXXXXX#XXXX  
XXXXXXXXXXXXXXXXXXXX#XXXX  
返回类型是Screen的输出：  
XXXXXXXXXXXXXXXXXXXX#XXXX  
XXXXXXXXXXXXXXXXXXXXXXXXX  
因为这样的话move、set和display返回的是Screen的临时副本，后续set和display操作并不会改变myScreen。  
  
## 练习7.29

> 修改你的Screen 类，令move、set和display函数返回Screen并检查程序的运行结果，在上一个练习中你的推测正确吗？

[Screen_ex29.h](Screen_ex29.h)

[ex29.cpp](ex29.cpp)

```sh
$ ./ex29
XXXXXXXXXXXXXXXXXXXX#XXXX
XXXXXXXXXXXXXXXXXXXXXXXXX
```
  
## 练习7.30

> 通过this指针使用成员的做法虽然合法，但是有点多余。讨论显示使用指针访问成员的优缺点。

优点：  
更明确，减少误读的可能性；  
可以使用名称与成员名相同的形参。  
```cpp
void setAddr(const std::string &addr) { this->addr = addr; }
```

缺点：  
冗余代码增加。  
```cpp
std::string getAddr() const { return this->addr; } // unnecessary
```
  
## 练习7.31

> 定义一对类X 和Y，其中X 包含一个指向 Y 的指针，而Y 包含一个类型为 X 的对象。

[ex31.h](ex31.h)
  
## [练习7.32](Screen_ex32.h)

> 定义你自己的Screen 和 Window_mgr，其中clear是Window_mgr的成员，是Screen的友元。


  
## 练习7.33

> 如果我们给Screen 添加一个如下所示的size成员将发生什么情况？如果出现了问题，请尝试修改它。
```cpp
pos Screen::size() const
{
    return height * width;
}
```

[Screen_ex33.h](Screen_ex33.h)


[ex33.cpp](ex33.cpp)

  
## 练习7.34

> 如果我们把第256页Screen类的pos的typedef放在类的最后一行会发生什么情况？

这样做会导致编译出错，因为对 pos 的使用出现在它的声明之前，此时编译器并不知道 pos 到底是什么含义。
  
## 练习7.35

> 解释下面代码的含义，说明其中的Type和initVal分别使用了哪个定义。如果代码存在错误，尝试修改它。
```cpp
typedef string Type;
Type initVal(); 
class Exercise {
public:
    typedef double Type;
    Type setVal(Type);
    Type initVal(); 
private:
    int val;
};
Type Exercise::setVal(Type parm) { 
    val = parm + initVal();     
    return val;
}
```

```cpp
typedef string Type;
Type initVal(); // use `string`
class Exercise {
public:
    typedef double Type;
    Type setVal(Type); // use `double`
    Type initVal(); // use `double`
private:
    int val;
};

Type Exercise::setVal(Type parm) {  // first is `string`, second is `double`
    val = parm + initVal();     // Exercise::initVal()
    return val;
}
```

修改为：
```cpp
Exercise::Type Exercise::setVal(Type parm) {
    val = parm + initVal();
    return val;
}
```
测试代码：  

[ex35.h](ex35.h)

[ex35.cpp](ex35.cpp)
  
## 练习7.36

> 下面的初始值是错误的，请找出问题所在并尝试修改它。
```cpp
struct X {
    X (int i, int j): base(i), rem(base % j) {}
    int rem, base;
};
```

成员的初始化顺序与它们在类定义中的出现顺序一致，所以会先初始化rem再初始化base，初始化rem时会用到base，故程序出错。  
可以改变定义的顺序：  
int base, rem;  
  
## 练习7.37

> 使用本节提供的Sales_data类，确定初始化下面的变量时分别使用了哪个构造函数，然后罗列出每个对象所有的数据成员的值。

```cpp
Sales_data first_item(cin);   // use Sales_data(std::istream &is) ; its value are up to your input.

int main() {
  Sales_data next;  // use Sales_data(std::string s = ""); bookNo = "", cnt = 0, revenue = 0.0
  Sales_data last("9-999-99999-9"); // use Sales_data(std::string s = ""); bookNo = "9-999-99999-9", cnt = 0, revenue = 0.0
}
```
  
## 练习7.38

> 有些情况下我们希望提供cin作为接受istream& 参数的构造函数的默认实参，请声明这样的构造函数。

```cpp
Sales_data(std::istream &is = std::cin) { read(is, *this); }
```
  
## 练习7.39

> 如果接受string 的构造函数和接受 istream& 的构造函数都使用默认实参，这种行为合法吗？如果不，为什么？

非法。因为这样的话，重载构造函数Sale_data()将不明确。
  
## 练习7.40

> 从下面的抽象概念中选择一个（或者你自己指定一个），思考这样的类需要哪些数据成员，提供一组合理的构造函数并阐明这样做的原因。
```cpp
(a) Book
(b) Data
(c) Employee
(d) Vehicle
(e) Object
(f) Tree
```

```cpp
//by Mooophy
#include <iostream>
#include <string>

class Book 
{
public:
    Book(unsigned isbn, std::string const& name, std::string const& author, std::string const& pubdate)
        :isbn_(isbn), name_(name), author_(author), pubdate_(pubdate)
    { }

    explicit Book(std::istream &in) 
    { 
        in >> isbn_ >> name_ >> author_ >> pubdate_;
    }

private:
    unsigned isbn_;
    std::string name_;
    std::string author_;
    std::string pubdate_;
};
```
  
## 练习7.41

> 使用委托构造函数重新编写你的Sales_data 类，给每个构造函数体添加一条语句，令其一旦执行就打印一条信息。用各种可能的方式分别创建 Sales_data 对象，认真研究每次输出的信息直到你确实理解了委托构造函数的执行顺序。

[Sales_data_ex41.h](Sales_data_ex41.h)

[ex41.cpp](ex41.cpp)

执行结果如下：
```sh
$ ./ex41 
Sales_data(const std::string &s, unsigned n, double p)
Sales_data(const std::string &s, unsigned n, double p)
Sales_data() : Sales_data("", 0, 0)
Sales_data(const std::string &s, unsigned n, double p)
Sales_data(const std::string &s) : Sales_data
Sales_data(const std::string &s, unsigned n, double p)
Sales_data() : Sales_data("", 0, 0)
001-03 1 100
Sales_data(std::istream &is) : Sales_data()
```
  
## 练习7.42

> 对于你在练习7.40中编写的类，确定哪些构造函数可以使用委托。如果可以的话，编写委托构造函数。如果不可以，从抽象概念列表中重新选择一个你认为可以使用委托构造函数的，为挑选出的这个概念编写类定义。

```cpp
#include <iostream>
#include <string>

class Book 
{
public:
    Book(unsigned isbn, std::string const& name, std::string const& author, std::string const& pubdate)
        :isbn_(isbn), name_(name), author_(author), pubdate_(pubdate)
    { }

    explicit Book(std::istream &in) 
    { 
        in >> isbn_ >> name_ >> author_ >> pubdate_;
    }

private:
    unsigned isbn_;
    std::string name_;
    std::string author_;
    std::string pubdate_;
};
```
  
## 练习7.43

> 假定有一个名为 NoDefault 的类，它有一个接受 int 的构造函数，但是没有默认构造函数。定义类 C，C 有一个 NoDefault 类型的成员，定义C 的默认构造函数。

```cpp
class NoDefault {
public:
    NoDefault(int i) { }
};

class C {
public:
    C() : def(0) { } // define the constructor of C.
private:
    NoDefault def;
};
```
  
## 练习7.44

> 下面这条声明合法吗？如果不，为什么？
```cpp
vector<NoDefault> vec(10);
```

非法，因为NoDefault没有默认构造函数。
  
## 练习7.45

> 如果在上一个练习中定义的vector的元素类型是C，则声明合法吗？为什么？

合法，因为C有默认构造函数。
  
## 练习7.46

> 下面哪些论断是不正确的？为什么？
```cpp
(a) 一个类必须至少提供一个构造函数。
(b) 默认构造函数是参数列表为空的构造函数。
(c) 如果对于类来说不存在有意义的默认值，则类不应该提供默认构造函数。
(d) 如果类没有定义默认构造函数，则编译器将为其生成一个并把每个数据成员初始化成相应类型的默认值。
```

（a）不正确，没有构造函数时，有时可以生成默认构造函数；  
（b）不正确，如果某个构造函数包含若干形参，但是同时为这些形参都提供了默认实参，则该构造函数也具备默认构造函数的功能；  
（c）不正确，默认构造函数在一些情况下非常重要；  
（d）不正确，当类没有显式地定义构造函数时，编译器才会隐式地定义默认构造函数。  
  
## 练习7.47

> 说明接受一个string 参数的Sales_data构造函数是否应该是explicit的，并解释这样做的优缺点。

优点：  
防止隐式转换的产生；  
可以只用作初始化。  
缺点：  
只有个单个参数的构造函数才有意义。  
  
## 练习7.48

> 假定Sales_data 的构造函数不是explicit的，则下述定义将执行什么样的操作？
```cpp
string null_isbn("9-999-9999-9");
Sales_data item1(null_isbn);
Sales_data item2("9-999-99999-9");
```

都不会有问题。
  
## 练习7.49

> 对于combine 函数的三种不同声明，当我们调用i.combine(s) 时分别发生什么情况？其中 i 是一个 Sales_data，而 s 是一个string对象。

（a）正确；  
（b）不正确，combine的参数是非常量的引用，所以我们不能将临时参数传递给它，改成Sales_data &combine(const Sales_data&);后正确；  
（c）不正确，后面的const不对，this需要可改变的。  
  
## [练习7.50](Person_ex50.h)

> 确定在你的Person 类中是否有一些构造函数应该是 explicit 的。


  
## 练习7.51

> vector 将其单参数的构造函数定义成 explicit 的，而string则不是，你觉得原因何在？

以下函数：

```cpp
int getSize(const std::vector<int>&);
```

如果vector的构造函数没有explicit，

```cpp
getSize(34);
```
我们就会不明白上述函数的意思。

stirng则不同，下述函数我们就很清楚。

```cpp
void setYourName(std::string); // declaration.
setYourName("pezy"); // just fine.
```
  
## 练习7.52

> 使用2.6.1节的 Sales_data 类，解释下面的初始化过程。如果存在问题，尝试修改它。
```cpp
    Sales_data item = {"987-0590353403", 25, 15.99};
```

该初始化使用花括号括起来的成员初始值列表来初始化聚合类的数据成员。所以我们需要定义聚合类：
```cpp
struct Sales_data {
    std::string bookNo;
    unsigned units_sold;
    double revenue;
};
```
  
## 练习7.53

> 定义你自己的 Debug。

[Debug_ex53.h](Debug_ex53.h)

[ex53.cpp](ex53.cpp)

  
## 练习7.54

> Debug中以 set_ 开头的成员应该被声明成 constexpr 吗？如果不，为什么？

在C++11中，constexpr函数时隐式的const，将不能更改数据成员；C++14中没有这个特点。
  
## 练习7.55

> 7.5.5节的 Data 类是字面值常量类吗？请解释原因。

不是，std::string不是字面值类型。
```cpp
#include <string>
#include <iostream>
#include <type_traits>

struct Data {
    int ival;
    std::string s;
};

int main()
{
    std::cout << std::boolalpha;
    std::cout << std::is_literal_type<Data>::value << std::endl;
    // output: false
}
```
  
## 练习7.56

> 什么是类的静态成员？它有何优点？静态成员与普通成员有何区别？

类的静态成员与类本身直接相关，而不是与类的各个对象保持关联。
每个对象不需要存储公共数据，如果数据被改变，则每个对象都可以使用新值。
静态数据成员可以是不完全类型；
可以使用静态成员作为默认实参。
  
## 练习7.57

> 编写你自己的 Account 类。

[account_ex57.h](account_ex57.h)

[ex57.cpp](ex57.cpp)
  
## 练习7.58

> 下面的静态数据成员的声明和定义有错误吗？请解释原因。
```cpp
//example.h
class Example {
public:
    static double rate = 6.5;
    static const int vecSize = 20;
    static vector<double> vec(vecSize);
};
//example.c
#include "example.h"
double Example::rate;
vector<double> Example::vec;
```

[ex58.h](ex58.h)

[ex58.cpp](ex58.cpp)
