## 2.1
C++语言规定一个int至少和一个short一样大，一个long至少和一个int一样大，一个long long至少和一个long一样大。每个的最小尺寸分别为：short，16位；int，16位；long，32位；long long，64位。
除去布尔型和扩展的字符型外，其他整形可以划分为带符号的和无符号的两种。带符号类型可以表示正数、负数或0，无符号类型则仅能表示大于等于0的值。
float最小尺寸为6位有效值，double最小尺寸为10位有效值。

## 2.2
都选用double，利率4.5%=0.045,本金和付款金额都是以元为单位，钱的最小金额是分，需要精确到小数点后两位，所以都选用double。

## 2.3
```
4294967264
32
32
-32
0
0
```

## 2.4

```cpp
#include <iostream>

int main()
{
    unsigned int u = 10, u2 = 42;
    std::cout << u - u2 << std::endl;
    std::cout << u2 - u << std::endl;

    int i = 10, i2 = 42;
    std::cout << i2 - i << std::endl;
    std::cout << i - i2 << std::endl;
    std::cout << i - u << std::endl;
    std::cout << u - i << std::endl;

    return 0;
}
```

## 2.5
（a）字符字面值，宽字符字面值，字符串字面值，宽字符串字面值；
（b）整形字面值，无符号整形字面值，长整形字面值，无符号长整形字面值，八进制整形字面值，十六进制整形字面值；
（c）浮点型字面值，单精度浮点型字面值，扩展精度浮点型字面值；
（d）整形字面值，无符号整形字面值，浮点型字面值，浮点型字面值。

## 2.6
（a）十进制整形；
（b）八进制整形，八进制总没有09。

## 2.7
(a)string
(b)long double
(c)非法，整形字面值不可加后缀f
(d)long double

## 2.8
```cpp
#include <iostream>

int main()
{
    std::cout << 2 << "\115\012";
    std::cout << 2 << "\011\115\012";
    
    return 0;
}
```

## 2.9
（编译时记得使用C++11标准编译"-std=c++11”）
(a)非法，>>运算符后不能定义；
(b)非法，不能执行强制转换；
(c)非法，同一语句的初始化应该分别进行；
(d)合法，已强制转换。

## 2.10
global_str,local_str为空字符串
global_int为0
local_int未初始化，没有初始值（测试下来也是0，最好都初始化掉）

## 2.11
（a）定义；
（b）定义；
（c）声明。

## 2.12
（a）非法，关键词；
（b）合法；
（c）非法；
（d）非法，字母、下划线开头；
（e）合法。

## 2.13
100

## 2.14
100 45

## 2.15
（a）合法；（b）不合法，引用类型的初始值必须是一个对象；
（c）合法；（d）不合法，引用类型必须初始化。

## 2.16
（a）合法
（b）合法
（c）合法
（d）合法

## 2.17
10 10

## 2.18
```cpp
int a = 0, b = 1;
int *p1 = &a, *p2 = p1;

// change the value of a pointer.
p1 = &b;
// change the value to which the pointer points
*p2 = b;
```

## 2.19
1.指针本身就是一个对象，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象；2.指针无须在定义时赋初值。

## 2.20
p指向i，i最后的值为1746（42*42）。

## 2.21
（a）非法，一个是double*，一个是int*；
（b）非法，一个是int*，一个是int；
（c）合法。

## 2.22
指针是不是空指针
指针所指的对象是不是0

## 2.23
不能，不能判断指针是否有效

## 2.24
类型不一样，void*可以表示任何类型的对象

## 2.25
（a）指向int的指针，int类型，int的引用；
（b）int类型，int类型的指针；
（c）int类型指针，int类型。

## 2.26
（a）不合法，const int必须初始化；
（b）合法；
（c）合法；
（d）++cnt，合法；++sz，不合法，const int不能改变。

## 2.27
（a）0是常量，&r不是对常量的引用，所以可以改变，这显然是不对的；
（b）如果i2是const int，这是不对的；
（c）合法；
（d）合法；
（e）合法；
（f）不合法，没有初始化；
（g）合法。

## 2.28
（a）不合法，常量指针未初始化；
（b）不合法，常量指针未初始化；
（c）不合法，常量ic未初始化；
（d）不合法，常量指针未初始化；
（e）合法，指向常量的指针可以不初始化。

## 2.29
（a）合法；
（b）非法，p3是指向const int的指针；
（c）非法，ic是const int；
（d）非法，p3是常量指针，不能再次赋值；
（e）非法，p2是常量指针，不能再次赋值；
（f）非法，ic是const int。

## 2.30
v2不能改变，是顶层const；v1都不是；p1都不是，r1都不是；p2所指的对象不能改变，底层const；p3既是顶层，又是底层；r2底层。

## 2.31
```cpp
r1 = v2; // 合法，v2为顶层const
p1 = p2; // 非法，p2为底层const
p2 = p1; // 合法
p1 = p3; // 非法
p2 = p3; // 合法
```

## 2.32
非法，int null = 0, *p = &null;

## 2.33
a=42; // 合法
b=42; // 合法
c=42; // 合法
d=42; // 非法
e=42; // 非法
g=42; // 非法

## 2.34
```cpp
#include <iostream>

int main()
{
    int i = 0, &r = i;
    auto a = r;   // a is an int (r is an alias for i, which has type int)

    const int ci = i, &cr = ci;
    auto b = ci; // b is an int (top-level const in ci is dropped)
    auto c = cr; // c is an int (cr is an alias for ci whose const is top-level)
    auto d = &i; // d is an int* (& ofan int objectis int*)
    auto e = &ci; // e is const int*(& of a const object is low-level const)

    const auto f = ci; // deduced type of ci is int; f has type const int
    auto &g = ci; // g is a const int& that is bound to ci

    a = 42; b = 42; c = 42; *d = 42; e = &c;

    return 0;
}
```

## 2.35
j int；k 常量int的引用；常量int的指针；j2 常量int；k2常量 int的引用

## 2.36
a int；b int；c int；d int &
4；4；4；4

## 2.37
a int 3
b int 4
c int 3
d int & 3

## 2.38
如果使用引用类型，auto会识别为其引用对象的类型，
decltype会识别为引用的类型。
decltype(())的差别。
顶层const差异

## 2.39
```cpp
struct Foo { /* empty  */ } // Note: no semicolon
int main()
{
    return 0;
}
```
Error message: [Error] expected ';' after struct definition

## 2.40
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

## 2.41

### 1.5.1
```cpp
#include <iostream>
#include <string>

struct Sale_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

int main()
{
    Sale_data book;
    double price;
    std::cin >> book.bookNo >> book.units_sold >> price;
    book.revenue = book.units_sold * price;
    std::cout << book.bookNo << " " << book.units_sold << " " << book.revenue << " " << price;

    return 0;
}
```

### 1.5.2
```cpp
#include <iostream>
#include <string>

struct Sale_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

int main()
{
    Sale_data book1, book2;
    double price1, price2;
    std::cin >> book1.bookNo >> book1.units_sold >> price1;
    std::cin >> book2.bookNo >> book2.units_sold >> price2;
    book1.revenue = book1.units_sold * price1;
    book2.revenue = book2.units_sold * price2;

    if (book1.bookNo == book2.bookNo)
    {
        unsigned totalCnt = book1.units_sold + book2.units_sold;
        double totalRevenue = book1.revenue + book2.revenue;
        std::cout << book1.bookNo << " " << totalCnt << " " << totalRevenue << " ";
        if (totalCnt != 0)
            std::cout << totalRevenue / totalCnt << std::endl;
        else
            std::cout << "(no sales)" << std::endl;
        return 0;
    }
    else
    {
        std::cerr << "Data must refer to same ISBN" << std::endl;
        return -1;  // indicate failure
    }
}
```

### 1.6
```cpp
#include <iostream>
#include <string>

struct Sale_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

int main()
{
    Sale_data total;
    double totalPrice;
    if (std::cin >> total.bookNo >> total.units_sold >> totalPrice)
    {
        total.revenue = total.units_sold * totalPrice;

        Sale_data trans;
        double transPrice;
        while (std::cin >> trans.bookNo >> trans.units_sold >> transPrice)
        {
            trans.revenue = trans.units_sold * transPrice;

            if (total.bookNo == trans.bookNo)
            {
                total.units_sold += trans.units_sold;
                total.revenue += trans.revenue;
            }
            else
            {
                std::cout << total.bookNo << " " << total.units_sold << " " << total.revenue << " ";
                if (total.units_sold != 0)
                    std::cout << total.revenue / total.units_sold << std::endl;
                else
                    std::cout << "(no sales)" << std::endl;

                total.bookNo = trans.bookNo;
                total.units_sold = trans.units_sold;
                total.revenue = trans.revenue;
            }
        }

        std::cout << total.bookNo << " " << total.units_sold << " " << total.revenue << " ";
        if (total.units_sold != 0)
            std::cout << total.revenue / total.units_sold << std::endl;
        else
            std::cout << "(no sales)" << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```

## 2.42
ex2_42.h
```cpp
#ifndef CH02_EX2_42_H_
#define CH02_EX2_42_H_

#include <string>
#include <iostream>

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    void CalcRevenue(double price);
    double CalcAveragePrice();
    void SetData(Sales_data data);
    void AddData(Sales_data data);
    void Print();
};

void Sales_data::CalcRevenue(double price)
{
    revenue = units_sold * price;
}

void Sales_data::SetData(Sales_data data)
{
    bookNo = data.bookNo;
    units_sold = data.units_sold;
    revenue = data.revenue;
}

void Sales_data::AddData(Sales_data data)
{
    if (bookNo != data.bookNo) return;
    units_sold += data.units_sold;
    revenue += data.revenue;
}

double Sales_data::CalcAveragePrice()
{
    if (units_sold != 0)
        return revenue / units_sold;
    else
        return 0.0;
}

void Sales_data::Print()
{
    std::cout << bookNo << " " << units_sold << " " << revenue << " ";
    double averagePrice = CalcAveragePrice();
    if (averagePrice != 0.0)
        std::cout << averagePrice << std::endl;
    else
        std::cout << "(no sales)" << std::endl;
}

#endif // CH02_EX2_42_H_
```
### 1.5.1
```cpp
#include <iostream>
#include "ex2_42.h"

int main()
{
    Sales_data book;
    double price;
    std::cin >> book.bookNo >> book.units_sold >> price;
    book.CalcRevenue(price);
    book.Print();

    return 0;
}
```

### 1.5.2
```cpp
#include <iostream>
#include "ex2_42.h"

int main()
{
    Sales_data book1, book2;
    double price1, price2;
    std::cin >> book1.bookNo >> book1.units_sold >> price1;
    std::cin >> book2.bookNo >> book2.units_sold >> price2;
    book1.CalcRevenue(price1);
    book2.CalcRevenue(price2);

    if (book1.bookNo == book2.bookNo)
    {
        book1.AddData(book2);
        book1.Print();
        return 0;
    }
    else
    {
        std::cerr << "Data must refer to same ISBN" << std::endl;
        return -1;  // indicate failure
    }
}
```

### 1.6
```cpp
#include <iostream>
#include "ex2_42.h"

int main()
{
    Sales_data total;
    double totalPrice;
    if (std::cin >> total.bookNo >> total.units_sold >> totalPrice)
    {
        total.CalcRevenue(totalPrice);
        Sales_data trans;
        double transPrice;
        while (std::cin >> trans.bookNo >> trans.units_sold >> transPrice)
        {
            trans.CalcRevenue(transPrice);
            if (total.bookNo == trans.bookNo)
            {
                total.AddData(trans);
            }
            else
            {
                total.Print();
                total.SetData(trans);
            }
        }
        total.Print();
        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```