## 练习5.1

> 什么是空语句？什么时候会用到空语句？

最简单的语句是空语句，空语句只有一个单独的分号：  
;//null statement  
如果在程序的某个地方，语法上需要一条语句但逻辑上不需要，此时应该使用空语句。  
  
## 练习5.2

> 什么是块？什么时候会用到块？

复合语句是指用花括号括起来的语句和声明的序列，复合语句也被称作块。  
如果在程序的某个地方，语法上需要一条语句，但是逻辑上需要多条语句，则应使用复合语句。  
  
## 练习5.3

> 使用逗号运算符重写1.4.1节的 while 循环，使它不再需要块，观察改写之后的代码可读性提高了还是降低了。

```cpp
#include <iostream>
int main()
{
    int sum = 0, val = 1;
    while (val <= 10)
        sum += val, ++val;
    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;

    return 0;
}
```
可读性降低了
  
## 练习5.4

> 说明下列例子的含义，如果存在问题，试着修改它。
```cpp
(a) while (string::iterator iter != s.end()) { /* . . . */ }
(b) while (bool status = find(word)) { /* . . . */ }
        if (!status) { /* . . . */ }
```

（a）
```cpp
std::string::iterator iter = s.begin();
while (iter != s.end()) { /* . . . */ }
```
（b）
```cpp
bool status;
while (status = find(word)) {/* ... */}
if (!status) {/* ... */}
```
  
## [练习5.5](ex05.cpp)

> 写一段自己的程序，使用if else 语句实现把数字转换为字母成绩的要求。
  
## [练习5.6](ex06.cpp)

> 改写上一题的程序，使用条件运算符代替if else语句。
  
## 练习5.7

> 改写下列代码段中的错误。
```cpp
(a) if (ival1 != ival2) 
        ival1 = ival2
    else 
        ival1 = ival2 = 0;
(b) if (ival < minval) 
        minval = ival;
        occurs = 1;
(c) if (int ival = get_value())
        cout << "ival = " << ival << endl;
    if (!ival)
        cout << "ival = 0\n";
(d) if (ival = 0)
        ival = get_value();
```

改写如下：
```cpp
(a) if (ival1 != ival2)
        ival1 = ival2;
    else ival1 = ival2 = 0;
(b) if (ival < minval)
    {
        minval = ival;
        occurs = 1;
    }
(c) int val;
    if (ival = get_value())
        cout << "ival = " << ival << endl;
    if (!ival)
        cout << "ival = 0\n";
(d) if (ival == 0)
        ival = get_value();
```
  
## 练习5.8

> 什么是“悬垂else”？C++语言是如何处理else子句的？

当一个if语句嵌套在另一个if语句内部时，很可能if分支会多于else分支。这时候我们怎么知道某个给定的else是和哪个if匹配呢。这个问题通常称作悬垂else。就C++而言，它规定else与离它最近的尚未匹配的if匹配的if匹配，从而消除了程序的二义性。
  
## [练习5.9](ex09.cpp)

> 编写一段程序，使用一系列if语句统计从cin读入的文本中有多少元音字母。
  
## [练习5.10](ex10.cpp)

> 我们之前实现的统计元音字母的程序存在一个问题：如果元音字母以大写形式出现，不会被统计在内。编写一段程序，既统计元音字母的小写形式，也统计元音字母的大写形式，也就是说，新程序遇到'a'和'A'都应该递增 aCnt 的值，以此类推。
  
## [练习5.11](ex11.cpp)

> 修改统计元音字母的程序，使其也能统计空格、制表符、和换行符的数量。

改为：
```cpp
while (cin >> std::noskipws >> ch) 
```
  
## [练习5.12](ex12.cpp)

> 修改统计元音字母的程序，使其能统计含以下两个字符的字符序列的数量： ff、fl和fi。
  
## 练习5.13

> 下面显示的每个程序都含有一个常见的编码错误，指出错误在哪里，然后修改它们。
```cpp
(a) unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
    char ch = next_text();
    switch (ch) {
        case 'a': aCnt++;
        case 'e': eCnt++;
        default: iouCnt++;
    }
(b) unsigned index = some_value();
    switch (index) {
        case 1:
            int ix = get_value();
            ivec[ ix ] = index;
            break;
        default:
            ix = ivec.size()-1;
            ivec[ ix ] = index;
    }
(c) unsigned evenCnt = 0, oddCnt = 0;
    int digit = get_num() % 10;
    switch (digit) {
        case 1, 3, 5, 7, 9:
            oddcnt++;
            break;
        case 2, 4, 6, 8, 10:
            evencnt++;
            break;
    }
(d) unsigned ival=512, jval=1024, kval=4096;
    unsigned bufsize;
    unsigned swt = get_bufCnt();
    switch(swt) {
        case ival:
            bufsize = ival * sizeof(int);
            break;
        case jval:
            bufsize = jval * sizeof(int);
            break;
        case kval:
            bufsize = kval * sizeof(int);
            break;
    }
```

（a）加上break：  
```cpp
    unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
    char ch = next_text();
    switch (ch) {
        case 'a': aCnt++; break;
        case 'e': eCnt++; break;
        default : iouCnt++; break;
    }
```
  
（b）case 1处可能被略过，default处又使用到变量ix，所以需要将ix定义到switch case之外：  
```cpp
    unsigned index = some_value();
    int ix;
    switch (index) {
        case 1:
            ix = get_value();
            ivec[ ix ] = index;
            break;
        default:
            ix = static_cast<int>(ivec.size())-1;
            ivec[ ix ] = index;
    }
```
  
（c）switch case语法不对：  
```cpp
    unsigned evenCnt = 0, oddCnt = 0;
    int digit = get_num() % 10;
    switch (digit) {
        case 1: case 3: case 5: case 7: case 9:
            oddcnt++;
            break;
        case 2: case 4: case 6: case 8: case 0:
            evencnt++;
            break;
    }
```
  
（d）case标签必须是整形常量表达式：  
```cpp
    const unsigned ival=512, jval=1024, kval=4096;
    unsigned bufsize;
    unsigned swt = get_bufCnt();
    switch(swt) {
        case ival:
            bufsize = ival * sizeof(int);
            break;
        case jval:
            bufsize = jval * sizeof(int);
            break;
        case kval:
            bufsize = kval * sizeof(int);
            break;
    }
```
[部分测试代码](ex13.cpp)
  
## [练习5.14](ex14.cpp)

> 编写一段程序，从标准输入中读取若干string对象并查找连续重复出现的单词，所谓连续重复出现的意思是：一个单词后面紧跟着这个单词本身。要求记录连续重复出现的最大次数以及对应的单词。如果这样的单词存在，输出重复出现的最大次数；如果不存在，输出一条信息说明任何单词都没有连续出现过。例如：如果输入是：
```
how now now now brown cow cow
```
那么输出应该表明单词now连续出现了3次。
  
## 练习5.15

> 说明下列循环的含义并改正其中的错误。
```cpp
(a) for (int ix = 0; ix != sz; ++ix) { /* ... */ }
    if (ix != sz)
        // . . .
(b) int ix;
    for (ix != sz; ++ix) { /* ... */ }
(c) for (int ix = 0; ix != sz; ++ix, ++sz) { /*...*/ }
```

（a）ix只能在for循环内部使用，如果要在外部使用，需要定义在for循环外：  
```cpp
int ix;
    for (ix = 0; ix != sz; ++ix)  { /* ... */ }
    if (ix != sz)
    // . . .
```
  
（b）没有初始化语句：  
```cpp
int ix;
    for (; ix != sz; ++ix) { /* ... */ }
```
  
（c）如果sz的初始值为0，则不进入循环；如果sz的初始值不为0，则需要循环体内需要有语句退出循环，否则会无休止地执行下去。  
  
## 练习5.16

> while 循环特别适用于那种条件不变、反复执行操作的情况，例如，当未达到文件末尾时不断读取下一个值。for 循环更像是在按步骤迭代，它的索引值在某个范围内一次变化。根据每种循环的习惯各自编写一段程序，然后分别用另一种循环改写。如果只能使用一种循环，你倾向于哪种？为什么？

```cpp
// while idiomatic
int i;
while ( cin >> i )
    // ...
 
// same as for
for (int i = 0; cin >> i;)
    // ...
 
// for idiomatic
for (int i = 0; i != size; ++i)
    // ...
 
// same as while
int i = 0;
while (i != size)
{
    // ...
    ++i;
}
```
我更趋向于while，因为只需要判断条件，更加简洁。  
  
## [练习5.17](ex17.cpp)

> 假设有两个包含整数的vector对象，编写一段程序，检验其中一个vector对象是否是另一个的前缀。为了实现这一目标，对于两个不等长的vector对象，只需挑出长度较短的那个，把它的所有元素和另一个vector对象比较即可。例如，如果两个vector对象的元素分别是0、1、1、2 和 0、1、1、2、3、5、8，则程序的返回结果为真。
  
## 练习5.18

> 说明下列循环的含义并改正其中的错误。
```cpp
(a) do { // 应该添加花括号
        int v1, v2;
        cout << "Please enter two numbers to sum:" ;
        if (cin >> v1 >> v2)
            cout << "Sum is: " << v1 + v2 << endl;
    }while (cin);
(b) int ival;
    do {
        // . . .
    } while (ival = get_response()); // 应该将ival 定义在循环外
(c) int ival = get_response();
    do {
        ival = get_response();
    } while (ival); // 应该将ival 定义在循环外
```

（a）加上花括号：  
```cpp
do { // added bracket.
        int v1, v2;
        cout << "Please enter two numbers to sum:" ;
        if (cin >> v1 >> v2)
            cout << "Sum is: " << v1 + v2 << endl;
    }while (cin);
```
  
（b）condition使用的变量必须定义在循环体外：  
```cpp
int ival;
    do {
        // . . .
    } while (ival = get_response());
```
  
（c）condition使用的变量必须定义在循环体外：  
```cpp
int ival;
    do {
        ival = get_response();
    } while (ival);
```
  
## [练习5.19](ex19.cpp)

> 编写一段程序，使用do while 循环重复地执行下述任务：首先提示用户输入两个string对象，然后挑出较短的那个并输出它。
  
## [练习5.20](ex20.cpp)

> 编写一段程序，从标准输入中读取string对象的序列直到连续出现两个相同的单词或者所有的单词都读完为止。使用while循环一次读取一个单词，当一个单词连续出现两次时使用break语句终止循环。输出连续重复出现的单词，或者输出一个消息说明没有任何单词是连续重复出现的。
  
## [练习5.21](ex21.cpp)

> 修改5.5.1节练习题的程序，使其找到的重复单词必须以大写字母开头。
  
## 练习5.22

> 本节的最后一个例子跳回到 begin，其实使用循环能更好的完成该任务，重写这段代码，注意不再使用goto语句。
```cpp
// 向后跳过一个带初始化的变量定义是合法的
begin:
    int sz = get_size();
    if (sz <= 0) {
        goto begin;
    }
```

```cpp
do
｛
 int sz = get_size();
｝while(sz <= 0);
```
  
## [练习5.23](ex23.cpp)

> 编写一段程序，从标准输入读取两个整数，输出第一个数除以第二个数的结果。

运行结果：

```sh
$ ./ex23 
1 0
Floating point exception (core dumped)
```
  
## [练习5.24](ex24.cpp)

> 修改你的程序，使得当第二个数是0时抛出异常。先不要设定catch子句，运行程序并真的为除数输入0，看看会发生什么？

运行结果：  
```sh
$ ./ex24 
1 0
terminate called after throwing an instance of 'std::runtime_error'
  what():  divisor can't be 0
Aborted (core dumped)
```
  
## [练习5.25](ex25.cpp)

> 修改上一题的程序，使用try语句块去捕获异常。catch子句应该为用户输出一条提示信息，询问其是否输入新数并重新执行try语句块的内容。

运行结果：
```sh
$ ./ex25 
1 0
divisor can't be 0
try again? enter y or n
y
1 0
divisor can't be 0
try again? enter y or n
n
```