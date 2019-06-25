## 练习12.1

> 在此代码的结尾，b1 和 b2 各包含多少个元素？
```cpp
StrBlob b1;
{
	StrBlob b2 = {"a", "an", "the"};
	b1 = b2;
	b2.push_back("about");
}
```

b1包含4个元素；  
b2被销毁。  

## 练习12.2

> 编写你自己的StrBlob 类，包含const 版本的 front 和 back。

[strblob.h](StrBlob_ex02.h)

[ex02.cpp](ex02.cpp)


## 练习12.3

> StrBlob 需要const 版本的push_back 和 pop_back吗？如需要，添加进去。否则，解释为什么不需要。

不需要，添加进去虽然编译器不会报错，但是这样不符合类使用者的使用习惯。  

## 练习12.4

> 在我们的 check 函数中，没有检查 i 是否大于0。为什么可以忽略这个检查？

可以忽略，本身i就是大于0的。  

## 练习12.5

> 我们未编写接受一个 initializer_list explicit 参数的构造函数。讨论这个设计策略的优点和缺点。

使用explicit之后  
优点：我们可以清楚地知道使用的是哪种类型；  
缺点：不易使用，需要显示地初始化。  

## [练习12.6](ex06.cpp)

> 编写函数，返回一个动态分配的 int 的vector。将此vector 传递给另一个函数，这个函数读取标准输入，将读入的值保存在 vector 元素中。再将vector传递给另一个函数，打印读入的值。记得在恰当的时刻delete vector。



## [练习12.7](ex07.cpp)

> 重做上一题，这次使用 shared_ptr 而不是内置指针。



## 练习12.8

> 下面的函数是否有错误？如果有，解释错误原因。
```cpp
bool b() {
	int* p = new int;
	// ...
	return p;
}
```

指针p被转换成bool值，new的内存没有被delete，内存没有被释放。  

## 练习12.9

> 解释下面代码执行的结果。
```cpp
int *q = new int(42), *r = new int(100);
r = q;
auto q2 = make_shared<int>(42), r2 = make_shared<int>(100);
r2 = q2;
```

r=q后r所指的内存没有释放，应该先delete r，再r=q；  
第二段代码内存会自动释放。  

## [练习12.10](ex10.cpp)

> 下面的代码调用了第413页中定义的process 函数，解释此调用是否正确。如果不正确，应如何修改？
```cpp
shared_ptr<int> p(new int(42));
process(shared_ptr<int>(p));
```

正确。

## 练习12.11

> 如果我们像下面这样调用 process，会发生什么？
```cpp
process(shared_ptr<int>(p.get()));
```

离开process时，p指向的内存会被释放，再使用p指针时会出现错误。  

## 练习12.12

> p 和 sp 的定义如下，对于接下来的对 process 的每个调用，如果合法，解释它做了什么，如果不合法，解释错误原因：
```cpp
auto p = new int();
auto sp = make_shared<int>();
(a) process(sp);
(b) process(new int());
(c) process(p);
(d) process(shared_ptr<int>(p));
```

（a）合法，将智能指针赋值给process；  
（b）不合法，shared_ptr初始化内置指针时需要使用直接初始化的形式；  
（c）不合法，shared_ptr初始化内置指针时需要使用直接初始化的形式；  
（d）合法。  

## 练习12.13

> 如果执行下面的代码，会发生什么？
```cpp
auto sp = make_shared<int>();
auto p = sp.get();
delete p;
```

sp和p指向的是同一个内存，释放了p所指向的内存后，再使用sp调用对象时可能会出错。  

## [练习12.14](ex14.cpp)

> 编写你自己版本的用 shared_ptr 管理 connection 的函数。



## [练习12.15](ex15.cpp)

> 重写第一题的程序，用 lambda 代替end_connection 函数。



## [练习12.16](ex16.cpp)

> 如果你试图拷贝或赋值 unique_ptr，编译器并不总是能给出易于理解的错误信息。编写包含这种错误的程序，观察编译器如何诊断这种错误。


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

## 练习12.17

> 下面的 unique_ptr 声明中，哪些是合法的，哪些可能导致后续的程序错误？解释每个错误的问题在哪里。
```cpp
int ix = 1024, *pi = &ix, *pi2 = new int(2048);
typedef unique_ptr<int> IntP;
(a) IntP p0(ix);
(b) IntP p1(pi);
(c) IntP p2(pi2);
(d) IntP p3(&ix);
(e) IntP p4(new int(2048));
(f) IntP p5(p2.get());
```

（a）非法，初始化错误；  
（b）编译时合法，运行时会报错，因为pi不是new出来的，销毁时使用默认的delete会出错；  
（c）编译时合法，但是运行时会导致空悬指针，unique_ptr释放空间时，使用pi2指针会出错；  
（d）编译时合法，运行时会报错，因为指针不是new出来的，销毁时使用默认的delete会出错；  
（e）合法；  
（f）编译时合法，但是会导致两次delete或者一个delete后另一个变为空悬指针。  

## 练习12.18

> shared_ptr 为什么没有 release 成员？

多个shared_ptr可以指向同一个对象，直接赋值即可，无需release成员。  

## 练习12.19

> 定义你自己版本的 StrBlobPtr，更新 StrBlob 类，加入恰当的 friend 声明以及 begin 和 end 成员。

[StrBlob_ex19.h](StrBlob_ex19.h)

[ex19.cpp](ex19.cpp)


## 练习12.20

> 编写程序，逐行读入一个输入文件，将内容存入一个 StrBlob 中，用一个 StrBlobPtr 打印出 StrBlob 中的每个元素。

[StrBlob_ex20.h](StrBlob_ex20.h)

[ex20.cpp](ex20.cpp)


## 练习12.21

> 也可以这样编写 StrBlobPtr 的 deref 成员：
```cpp
std::string& deref() const {
	return (*check(curr, "dereference past end"))[curr];
}
```
你认为哪个版本更好？为什么？

之前的版本更好，更容易读懂。

## 练习12.22

> 为了能让 StrBlobPtr 使用 const StrBlob，你觉得应该如何修改？定义一个名为ConstStrBlobPtr 的类，使其能够指向 const StrBlob。

[StrBlob_ex22.h](StrBlob_ex22.h)

[ex22.cpp](ex20.cpp)


## 练习12.23

> 编写一个程序，连接两个字符串字面常量，将结果保存在一个动态分配的char数组中。重写这个程序，连接两个标准库string对象。

[ex23_1.cpp](ex23_1.cpp)

[ex23_2.cpp](ex23_2.cpp)


## [练习12.24](ex24.cpp)

> 编写一个程序，从标准输入读取一个字符串，存入一个动态分配的字符数组中。描述你的程序如何处理变长输入。测试你的程序，输入一个超出你分配的数组长度的字符串。



## 练习12.25

> 给定下面的new表达式，你应该如何释放pa？
```cpp
int *pa = new int[10];
```

```cpp
delete [] pa;
```

## [练习12.26](ex26.cpp)

> 用 allocator 重写第427页中的程序。



## 练习12.27

> TextQuery 和 QueryResult 类只使用了我们已经介绍过的语言和标准库特性。不要提前看后续章节内容，只用已经学到的知识对这两个类编写你自己的版本。

[TextQuery_ex27.h](TextQuery_ex27.h)


[ex27.cpp](ex27.cpp)


## 练习12.28

> 编写程序实现文本查询，不要定义类来管理数据。你的程序应该接受一个文件，并与用户交互来查询单词。使用vector、map 和 set 容器来保存来自文件的数据并生成查询结果。

略。

## 练习12.29

> 我们曾经用do while 循环来编写管理用户交互的循环。用do while 重写本节程序，解释你倾向于哪个版本，为什么？

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

## 练习12.30

> 定义你自己版本的 TextQuery 和 QueryResult 类，并执行12.3.1节中的runQueries 函数。

见12.27。

## 练习12.31

> 如果用vector 代替 set 保存行号，会有什么差别？哪个方法更好？为什么？

vector不能确保元素的唯一性，所以这里set更好。

## 练习12.32

> 重写 TextQuery 和 QueryResult类，用StrBlob 代替 vector<string> 保存输入文件。

[TextQuery_ex32.h](TextQuery_ex32.h)


[ex32.cpp](ex32.cpp)


## 练习12.33

> 在第15章中我们将扩展查询系统，在 QueryResult 类中将会需要一些额外的成员。添加名为 begin 和 end 的成员，返回一个迭代器，指向一个给定查询返回的行号的 set 中的位置。再添加一个名为 get_file 的成员，返回一个 shared_ptr，指向 QueryResult 对象中的文件。

[TextQuery_ex33.h](TextQuery_ex33.h)

[ex33.cpp](ex33.cpp)
