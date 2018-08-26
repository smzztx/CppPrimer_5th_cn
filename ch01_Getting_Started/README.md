#ch01 Getting Started
## 1.1
我使用g++，一般将C++程序命名为.cpp。  
g++ -o main main.cpp  
[代码](ex01_main.cpp)
```bash
$ g++ -o main main.cpp 
$ ls
main  main.cpp
```
参考：  
[GCC and File Extensions](http://labor-liber.org/en/gnu-linux/development/index.php?diapo=extensions)

## 1.2
将返回值改为-1后得到：
```linux
$ echo $?
255
```
参考：  
[Exit Codes With Special Meanings](http://www.tldp.org/LDP/abs/html/exitcodes.html)

## [1.3](ex03_helloworld.cpp)
## [1.4](ex04_add_two_int.cpp)
## [1.5](ex05.cpp)
## 1.6
非法，修改为：
```cpp
std::cout << "The sum of " << v1
          << " and " << v2
          << " is " << v1 + v2 << std::endl;
```

## 1.7
[代码](ex07.cpp)
```linux
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

## 1.8
第三行非法，第三行改为：
```cpp
	std::cout << /* "*/" */";
```
[代码](ex08.cpp)

## [1.9](ex09.cpp)
## [1.10](ex10.cpp)
## [1.11](ex11.cpp)
## 1.12
求从-100加到100的和，最终值为0。  
[测试代码](ex12.cpp)

## 1.13

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

## 1.14
已知迭代次数时，使用for循环比较简洁；不知道迭代次数时使用while。  
参考：  
[A similar question on Stack Overflow](http://stackoverflow.com/questions/2950931/for-vs-while-in-c-programming)

## 1.15
请自行尝试。

## [1.16](ex16_sum_of_cin.cpp)
数字输入完成后，Ctrl+d结束输入。

## 1.17
如果输入的所有值都是相等的，Ctrl+d后，才有输出统计的个数；如果没有重复输出，输入与前个不同的数即打印一行，Ctrl+d后，才输出最后一行统计的个数。  
[本节程序](ex17.cpp)

## 1.18

```linux
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

## 1.19
见1.11。

## [1.20](ex20_Sales_item.cpp)
测试：

```
$ ./ex20 
2-01 2 20
2-01 2 40 20
```

## [1.21](ex21.cpp)
测试：

```linux
$ ./ex21
1-01 2 100
1-01 3 100
1-01 5 500 100
```

## [1.22](ex22.cpp)

```
#include <iostream>
#include "Sales_item.h"
测试：

```linux
$ ./ex22
1-01 2 100
1-01 2 100
1-01 3 100
1-01 7 700 100
```
需要初始化sum_item：
std::cin >> sum_item;

## [1.23](ex23.cpp)
## 1.24
测试：

```
$ ./ex23
1-01 2 100
1-01 3 100
1-01 1 100
1-02 1 150
1-01 2 200 100 occurs 3 times 

```

## [1.25](ex25.cpp)
测试：

```linux
$ ./ex25 
1-01 2 100
1-01 3 100
1-01 1 100
1-02 1 150
1-01 6 600 100
1-02 1 150 150

```
