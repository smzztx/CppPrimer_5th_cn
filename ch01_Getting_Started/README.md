## 练习1.1

> 查阅你使用的编译器文档，确定它所使用的文件命名约定。编译并运行第2页的main程序。

我使用g++，一般将C++程序命名为.cpp。  
g++ -o main main.cpp  
[代码](ex01_main.cpp)
```sh
$ g++ -o main main.cpp 
$ ls
main  main.cpp
```
参考：  
[GCC and File Extensions](http://labor-liber.org/en/gnu-linux/development/index.php?diapo=extensions)
  
## 练习1.2

> 改写程序，让它返回-1。返回值-1通常被当作程序错误的标识。重新编译并运行你的程序，观察你的系统如何处理main返回的错误标识。

将返回值改为-1后得到：
```sh
$ echo $?
255
```
参考：  
[Exit Codes With Special Meanings](http://www.tldp.org/LDP/abs/html/exitcodes.html)
  
## [练习1.3](ex03_helloworld.cpp)

> 编写程序，在标准输出上打印 Hello, World。
  
## [练习1.4](ex04_add_two_int.cpp)

> 我们的程序使用加法运算符+来将两个数相加。编写程序使用乘法运算符*，来打印两个数的积。
  
## [练习1.5](ex05.cpp)

> 我们将所有输出操作放在一条很长的语句中。重写程序，将每个运算对象的打印操作放在一条独立的语句中。
  
## 练习1.6

> 解释下面程序片段是否合法。
```
std::cout << "The sum of " << v1;
      << " and " << v2;
      << " is " << v1 + v2 << std::endl;
```
如果程序是合法的，它的输出是什么？如果程序不合法，原因何在？应该如何修正？

非法，修改为：
```cpp
std::cout << "The sum of " << v1
          << " and " << v2
          << " is " << v1 + v2 << std::endl;
```
  
## 练习1.7

> 编译一个包含不正确的嵌套注释的程序，观察编译器返回的错误信息。

[代码](ex07.cpp)
```sh
$ g++ -o ex07 ex07.cpp 
ex07.cpp: In function ‘int main()’:
ex07.cpp:5:3: error: expected primary-expression before ‘/’ token
  */
   ^
ex07.cpp:6:2: error: expected primary-expression before ‘return’
  return 0;
  ^
ex07.cpp:6:2: error: expected ‘;’ before ‘return’
```
  
## 练习1.8

> 指出下列哪些输出语句是合法的(如果有的话)：
```cpp
std::cout << "/*";
std::cout << "*/";
std::cout << /* "*/" */;
std::cout << /* "*/" /* "/*" */;
```
预测编译这些语句会产生什么样的结果，实际编译这些语句来验证你的答案(编写一个小程序，每次将上述一条语句作为其主体)，改正每个编译错误。

第三行非法，第三行改为：
```cpp
	std::cout << /* "*/" */";
```
[代码](ex08.cpp)
  
## [练习1.9](ex09.cpp)

> 编写程序，使用while循环将50到100的整数相加。
  
## [练习1.10](ex10.cpp)

> 除了++运算符将运算对象的值增加1之外，还有一个递减运算符（--）实现将值减少1。编写程序，使用递减运算符在循环中按递减顺序打印出10到0之间的整数。
  
## [练习1.11](ex11.cpp)

> 编写程序，提示用户输入两个整数，打印出这两个整数所指定的范围内的所有整数。
  
## 练习1.12

> 下面的for循环完成了什么功能？sum的终值是多少？
```cpp
int sum = 0;
for (int i = -100; i <= 100; ++i)
  sum += i;
```

求从-100加到100的和，最终值为0。  
[测试代码](ex12.cpp)
  
## 练习1.13

> 使用for循环重做1.4.1节中的所有练习（第11页）。

Ex1.9:
```cpp
#include <iostream>

int main()
{
    int sum = 0;
    for (int i = 50; i <= 100; ++i) sum += i;
    std::cout << "the sum is: " << sum << std::endl;

    return 0;
}
```

Ex1.10:
```cpp
#include <iostream>

int main()
{
    for (int i = 10; i >= 0; --i)
        std::cout << i << std::endl;
    return 0;
}
```

Ex1.11:
```cpp
#include <iostream>

int main()
{
    std::cout << "please input two integers:\n";
    int small = 0, big = 0;
    std::cin >> small >> big;

    if (small > big)
    {
        int tmp = small;
        small = big;
        big = tmp;
    }

    for (int i = small; i != big; ++i)
        std::cout << i << std::endl;

    return 0;
}
```
  
## 练习1.14

> 对比for循环和while循环，两种形式的优缺点各是什么？

已知迭代次数时，使用for循环比较简洁；不知道迭代次数时使用while。  
参考：  
[A similar question on Stack Overflow](http://stackoverflow.com/questions/2950931/for-vs-while-in-c-programming)
  
## 练习1.15

> 编写程序，包含第14页“再探编译”中讨论的常见错误。熟悉编译器生成的错误信息。

请自行尝试。
  
## [练习1.16](ex16_sum_of_cin.cpp)

> 编写程序，从cin读取一组数，输出其和。

数字输入完成后，Ctrl+d结束输入。
  
## 练习1.17

> 如果输入的所有值都是相等的，本节的程序会输出什么？如果没有重复值，输出又会是怎样的？

如果输入的所有值都是相等的，Ctrl+d后，才有输出统计的个数；如果没有重复输出，输入与前个不同的数即打印一行，Ctrl+d后，才输出最后一行统计的个数。  
[本节程序](ex17.cpp)
  
## 练习1.18

> 编译并运行本节的程序，给它输入全都相等的值。再次运行程序，输入没有重复的值。

```sh
$ ./ex17 
1 1 1 1 1 
1 occurs 5 times
$ ./ex17 
1 2 3 4 5 
1 occurs 1 times
2 occurs 1 times
3 occurs 1 times
4 occurs 1 times
5 occurs 1 times
```
  
## 练习1.19

> 修改你为1.4.1节练习1.11（第11页）所编写的程序（打印一个范围内的数），使其能处理用户输入的第一个数比第二个数小的情况。

见1.11。
  
## [练习1.20](ex20_Sales_item.cpp)

> 在网站http://www.informit.com/title/032174113 上，第1章的代码目录包含了头文件 Sales_item.h。将它拷贝到你自己的工作目录中。用它编写一个程序，读取一组书籍销售记录，将每条记录打印到标准输出上。

测试：

```sh
$ ./ex20 
2-01 2 20
2-01 2 40 20
```
  
## [练习1.21](ex21.cpp)

> 编写程序，读取两个 ISBN 相同的 Sales_item 对象，输出他们的和。

测试：

```sh
$ ./ex21
1-01 2 100
1-01 3 100
1-01 5 500 100
```
  
## [练习1.22](ex22.cpp)

> 编写程序，读取多个具有相同 ISBN 的销售记录，输出所有记录的和。

测试：

```sh
$ ./ex22
1-01 2 100
1-01 2 100
1-01 3 100
1-01 7 700 100
```
需要初始化sum_item：
std::cin >> sum_item;
  
## [练习1.23](ex23.cpp)

> 编写程序，读取多条销售记录，并统计每个 ISBN（每本书）有几条销售记录。
  
## 练习1.24

> 输入表示多个 ISBN 的多条销售记录来测试上一个程序，每个 ISBN 的记录应该聚在一起。

测试：

```sh
$ ./ex23
1-01 2 100
1-01 3 100
1-01 1 100
1-02 1 150
1-01 6 600 100
1-02 1 150 150
```
  
## [练习1.25](ex25.cpp)

> 借助网站上的 Sales_item.h 头文件，编译并运行本节给出的书店程序。

测试：

```sh
$ ./ex25 
1-01 2 100                      # 输入后回车
1-01 3 100                      # 输入后回车
1-01 1 100                      # 输入后回车
1-02 1 150                      # 输入后回车
1-01 6 600 100                  # 程序输出
1-02 1 150 150                  # ctrl + D 终止输入后，程序输出
```
