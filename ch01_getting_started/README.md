## 1.1
我使用g++，一般将C++程序命名为.cpp。
g++ -o main main.cpp 
```linux
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

## 1.3

```cpp
#include <iostream>

int main()
{
	std::cout << "Hello,World" << std::endl;

	return 0;
}
```

## 1.4

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The product is " << v1 * v2 << std::endl;

    return 0;
}
```

## 1.5

```cpp
#include <iostream>

int main()
{
    std::cout << "Enter two numbers:" << std::endl;
    int v1 = 0, v2 = 0;
    std::cin >> v1 >> v2;
    std::cout << "The product of ";
    std::cout << v1;
    std::cout << " and ";
    std::cout << v2;
    std::cout << " is ";
    std::cout << v1 * v2;
    std::cout << std::endl;
    return 0;
}
```

## 1.6
非法，修改为：

```cpp
std::cout << "The sum of " << v1
          << " and " << v2
          << " is " << v1 + v2 << std::endl;
```

## 1.7

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

## 1.9

```cpp
#include <iostream>

int main()
{
	int i = 50 ,sum = 0;

	while(i <= 100)
	{
		sum += i;
		++i;
	}
	std::cout << sum << std::endl;

	return 0;
}
```

## 1.10

```cpp
#include <iostream>

int main()
{
	int i = 10 ,sum = 0;

	while(i >= 0)
	{
		sum += i;
		--i;
	}
	std::cout << sum << std::endl;

	return 0;
}
```

## 1.11

```cpp
#include <iostream>

int main()
{
    int small = 0, big = 0;
    std::cout << "please input two integers:";
    std::cin >> small >> big;

    if (small > big) {
        int tmp = small;
        small = big;
        big = tmp;
    }

    while (small <= big) {
        std::cout << small << " ";
        ++small;
    }
    std::cout << std::endl;

    return 0;
}
```

## 1.12
求从-100加到100的和，最终值为0。
测试代码如下：
```cpp
#include <iostream>

int main()
{
    int sum = 0;
    for(int i = -100;i <= 100; i++ )
    {
        sum += i;
        std::cout << i << std::endl;
    }
    std::cout << sum << std::endl;

    return 0;
}
```

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

## 1.16

```cpp
#include <iostream>

int main()
{
    int sum = 0, value = 0;
    while(std::cin >> value)
    {
        sum += value;
    }
    std::cout << sum << std::endl;
    return 0;
}
```
数字输入完成后，Ctrl+d结束输入。

## 1.17
如果输入的所有值都是相等的，Ctrl+d后，才有输出统计的个数；如果没有重复输出，输入与前个不同的数即打印一行，Ctrl+d后，才输出最后一行统计的个数。

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

## 1.20

```cpp
#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item item;
    std::cin >> item;
    std::cout << item <<std::endl;

    return 0;
}
```
测试：

```
$ ./ex20 
2-01 2 20
2-01 2 40 20
```

## 1.21

```cpp
#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item item1,item2;
    std::cin >> item1 >> item2;
    std::cout << item1 + item2 <<std::endl;
    
    return 0;
}
```
测试：

```linux
$ ./ex21
1-01 2 100
1-01 3 100
1-01 5 500 100
```

## 1.22

```
#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item item,sum_item;
    std::cin >> sum_item;
    while(std::cin >> item)
    {
    	sum_item += item;
    }
    std::cout << sum_item << std::endl;
    
    return 0;
}
```
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

## 1.23

```cpp
#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item currItem, valItem;
    if (std::cin >> currItem) {
        int cnt = 1;
        while (std::cin >> valItem) {
            if (valItem.isbn() == currItem.isbn())
                ++cnt;
            else {
                std::cout << currItem << " occurs " << cnt << " times "
                          << std::endl;
                currItem = valItem;
                cnt = 1;
            }
        }

        std::cout << currItem << " occurs " << cnt << " times " << std::endl;
    }
    return 0;
}
```

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

## 1.25

```cpp
#include <iostream>
#include "Sales_item.h"

int main() 
{
    Sales_item total; // variable to hold data for the next transaction

    // read the first transaction and ensure that there are data to process
    if (std::cin >> total) {
		Sales_item trans; // variable to hold the running sum
        // read and process the remaining transactions
        while (std::cin >> trans) {
			// if we're still processing the same book
            if (total.isbn() == trans.isbn()) 
                total += trans; // update the running total 
            else {              
		        // print results for the previous book 
                std::cout << total << std::endl;  
                total = trans;  // total now refers to the next book
            }
		}
        std::cout << total << std::endl; // print the last transaction
    } else {
        // no input! warn the user
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }

    return 0;
}

```
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