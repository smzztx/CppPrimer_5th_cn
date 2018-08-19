## 7.1
见习题2.41。

## 7.2
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
};

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

#endif
```

## 7.3
```cpp
#include <iostream>
#include <string>
#include "Sales_data.h"

int main()
{
    Sales_data total;
    double totalPrice;

    if (std::cin >> total.bookNo >> total.units_sold >> totalPrice)
    {
        total.revenue = total.units_sold * totalPrice;

        Sales_data trans;
        double transPrice;
        while (std::cin >> trans.bookNo >> trans.units_sold >> transPrice)
        {
            trans.revenue = trans.units_sold * transPrice;

            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                std::cout << total.bookNo << " " << total.units_sold << " " << total.revenue << " ";
                if (total.units_sold != 0)
                    std::cout << total.revenue / total.units_sold << std::endl;
                else
                    std::cout << "(no sales)" << std::endl;

                total = trans;
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

## 7.4
```cpp
#ifndef PERSON_H_
#define PERSON_H_

#include <string>

struct Person
{
    std::string name;
    std::string address;
};

#endif
```

## 7.5
应该是const，这两个成员函数只需读取成员对象，无需改变成员对象。
```cpp
#ifndef PERSON_H_
#define PERSON_H_

#include <string>

struct Person
{
    std::string name;
    std::string address;

    std::string get_name() const{return name;}
    std::string get_address() const{return address;}
};

#endif
```

## 7.6
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data
{
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;

    std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
};

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue / units_sold;
	else
		return 0;
}

std::istream &read(std::istream &is, Sales_data &item)
{
	double price = 0;

	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;

	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);

	return sum;
}

#endif
```

## 7.7
```cpp
#include <iostream>
#include <string>
#include "Sales_data_ex06.h"

int main()
{
    Sales_data total;

    if (read(std::cin, total))
    {
        Sales_data trans;

        while (read(std::cin, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(std::cout, total);
                std::cout << std::endl;
                total = trans;
            }
        }
        print(std::cout, total);
        std::cout << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```

## 7.8
因为read函数需要改变成员对象；而print只需读取成员对象。

## 7.9
```cpp
#ifndef PERSON_H_
#define PERSON_H_

#include <string>

struct Person
{
    std::string name;
    std::string address;

    std::string get_name() const{return name;}
    std::string get_address() const{return address;}
};

std::istream &read(std::istream &is, Person &item)
{
	return is >> item.name >> item.address;
}

std::ostream &print(std::ostream &os, const Person &item)
{
	return os << item.name << " " << item.address;
}

#endif
```

## 7.10
读入data1和data2，并判断返回是否为真。

## 7.11
Sales_data_ex11.cpp
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data
{
	Sales_data() = default;
	Sales_data(const std::string &s) : bookNo(s){}
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){}
	Sales_data(std::istream &);
	std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue / units_sold;
	else
		return 0;
}

std::istream &read(std::istream &is, Sales_data &item)
{
	double price = 0;

	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;

	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);

	return sum;
}

Sales_data::Sales_data(std::istream &is)
{
	read(is, *this);
}

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

#endif
```

ex11.cpp
```cpp
#include <string>
#include <iostream>
#include "Sales_data_ex11.h"

int main()
{
	Sales_data sales_data1;
	print(std::cout, sales_data1) << std::endl;

	Sales_data sales_data2("1-01");
	print(std::cout, sales_data2) << std::endl;

	Sales_data sales_data3("1-01", 1, 100);
	print(std::cout, sales_data3) << std::endl;

	Sales_data sales_data4(std::cin);
	print(std::cout, sales_data4) << std::endl;

	// Sales_data sales_data5();
	// print(std::cout, sales_data5) << std::endl;

	return 0;
}
```

## 7.12
Sales_data_ex12.cpp
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data;

std::istream &read(std::istream &is, Sales_data &item);
std::ostream &print(std::ostream &os, const Sales_data &item);
Sales_data add(const Sales_data &lhs, const Sales_data &rhs);

struct Sales_data
{
	Sales_data() = default;
	Sales_data(const std::string &s) : bookNo(s){}
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){}
	Sales_data(std::istream &is) {read(is, *this);}
	std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue / units_sold;
	else
		return 0;
}

std::istream &read(std::istream &is, Sales_data &item)
{
	double price = 0;

	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;

	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);

	return sum;
}

#endif
```

ex12.cpp
```cpp
#include <string>
#include <iostream>
#include "Sales_data_ex12.h"

int main()
{
	Sales_data sales_data1;
	print(std::cout, sales_data1) << std::endl;

	Sales_data sales_data2("1-01");
	print(std::cout, sales_data2) << std::endl;

	Sales_data sales_data3("1-01", 1, 100);
	print(std::cout, sales_data3) << std::endl;

	Sales_data sales_data4(std::cin);
	print(std::cout, sales_data4) << std::endl;

	// Sales_data sales_data5();
	// print(std::cout, sales_data5) << std::endl;

	return 0;
}
```

## 7.13
```cpp
#include <iostream>
#include <string>
#include "Sales_data_ex12.h"

int main()
{
    Sales_data total(std::cin);

    if (!total.isbn().empty())
    {
        Sales_data trans;

        while (read(std::cin, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(std::cout, total);
                std::cout << std::endl;
                total = trans;
            }
        }
        print(std::cout, total);
        std::cout << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```

## 7.14
```cpp
Sales_data() : bookNo(""), units_sold(0) , revenue(0){ }
```

## 7.15
```cpp
#ifndef PERSON_H_
#define PERSON_H_

#include <string>

struct Person;

std::istream &read(std::istream &is, Person &item);
std::ostream &print(std::ostream &os, const Person &item);

struct Person
{
	Person() : name(""), address(""){}
	Person(const std::string &sname, const std::string &saddress = "") : name(sname), address(saddress){}
	Person(std::istream &is){read(is, *this);}
    std::string get_name() const{return name;}
    std::string get_address() const{return address;}

    std::string name;
    std::string address;
};

std::istream &read(std::istream &is, Person &item)
{
	return is >> item.name >> item.address;
}

std::ostream &print(std::ostream &os, const Person &item)
{
	return os << item.name << " " << item.address;
}

#endif
```

## 7.16
一个类可以包含0个或多个访问说明符，而且对于某个访问说明符能出现多少次也没有严格的限定。  
public：成员在整个程序内可被访问，public成员定义类的接口；  
private：成员可以被类的成员函数访问，但是不能被使用该类的代码访问，private部分封装了（即隐藏了）类的实现细节。  

## 7.17
struct默认的访问权限是public；  
class默认的访问权限是private。  

## 7.18
封装是实现与接口的分离。它隐藏了类型的实现细节。（在C++中，封装是通过将实现放在一个类的私有部分来实现的）  
封装有两个重要的优点：  
1.确保用户代码不会无意间破坏封装对象的状态；  
2.被封装的类的具体实现细节可以随时改变，而无须调整用户级别的代码。  

## 7.19
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

## 7.20
类可以允许其他类或者函数访问它的非公有成员，方法是令其他类或者函数成为它的友元。  
优点：  
外部函数可以方便地使用类的成员，而不需要显示地给它们加上类名；  
可以方便地访问所有非公有成员；  
有时，对类的用户更容易读懂。  
缺点：  
减少封装和可维护性；  
代码冗长，类内的声明，类外函数声明。  

## 7.21
Sales_data_ex21.h
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data;

std::istream &read(std::istream &is, Sales_data &item);
std::ostream &print(std::ostream &os, const Sales_data &item);
Sales_data add(const Sales_data &lhs, const Sales_data &rhs);

struct Sales_data
{
friend std::istream &read(std::istream &is, Sales_data &item);
friend std::ostream &print(std::ostream &os, const Sales_data &item);
friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
public:
	Sales_data() = default;
	Sales_data(const std::string &s) : bookNo(s){}
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){}
	Sales_data(std::istream &is) {read(is, *this);}
	std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
private:
    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue / units_sold;
	else
		return 0;
}

std::istream &read(std::istream &is, Sales_data &item)
{
	double price = 0;

	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;

	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);

	return sum;
}

#endif
```

ex21.cpp
```cpp
#include <iostream>
#include <string>
#include "Sales_data_ex21.h"

int main()
{
    Sales_data total(std::cin);

    if (!total.isbn().empty())
    {
        Sales_data trans;

        while (read(std::cin, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(std::cout, total);
                std::cout << std::endl;
                total = trans;
            }
        }
        print(std::cout, total);
        std::cout << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```

## 7.22
Person_ex22.h
```cpp
#ifndef PERSON_H_
#define PERSON_H_

#include <string>

struct Person;

std::istream &read(std::istream &is, Person &item);
std::ostream &print(std::ostream &os, const Person &item);

struct Person
{
friend std::istream &read(std::istream &is, Person &item);
friend std::ostream &print(std::ostream &os, const Person &item);
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

std::istream &read(std::istream &is, Person &item)
{
	return is >> item.name >> item.address;
}

std::ostream &print(std::ostream &os, const Person &item)
{
	return os << item.name << " " << item.address;
}

#endif
```

ex22.cpp
```cpp
//test Person_ex15.h
#include <string>
#include <iostream>
#include "Person_ex15.h"

int main()
{
	Person person1;
	print(std::cout, person1) << std::endl;

	Person person2("tx", "hangzhou");
	print(std::cout, person2) << std::endl;
	std::cout << person2.get_name() << " " << person2.get_address() << std::endl;

	Person person3("tx");
	print(std::cout, person3) << std::endl;

	Person person4(std::cin);
	print(std::cout, person4) << std::endl;

	return 0;
}
```

## 7.23
```cpp
#ifndef SCREEN_EX23_H_
#define SCREEN_EX23_H_

#include <string>

class Screen {
    public:
        using pos = std::string::size_type;

        Screen() = default;
        Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

        char get() const { return contents[cursor]; }
        char get(pos r, pos c) const { return contents[r*width+c]; }

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};

#endif
```

## 7.24
```cpp
#ifndef SCREEN_EX23_H_
#define SCREEN_EX23_H_

#include <string>

class Screen {
    public:
        using pos = std::string::size_type;

        Screen() = default;
        Screen(pos ht, pos wd):height(ht), width(wd){ }
        Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

        char get() const { return contents[cursor]; }
        char get(pos r, pos c) const { return contents[r*width+c]; }

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
};

#endif
```

## 7.25
能，Screen类中只有内置类型和string可以使用拷贝和赋值操作，见7.15。  

## 7.26
Sales_data_ex26.h
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data;

std::istream &read(std::istream &is, Sales_data &item);
std::ostream &print(std::ostream &os, const Sales_data &item);
Sales_data add(const Sales_data &lhs, const Sales_data &rhs);

struct Sales_data
{
friend std::istream &read(std::istream &is, Sales_data &item);
friend std::ostream &print(std::ostream &os, const Sales_data &item);
friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
public:
	Sales_data() = default;
	Sales_data(const std::string &s) : bookNo(s){}
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){}
	Sales_data(std::istream &is) {read(is, *this);}
	std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
private:
	inline double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue / units_sold;
	else
		return 0;
}

std::istream &read(std::istream &is, Sales_data &item)
{
	double price = 0;

	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;

	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);

	return sum;
}

#endif
```

ex26.cpp
```cpp
#include <iostream>
#include <string>
#include "Sales_data_ex26.h"

int main()
{
    Sales_data total(std::cin);

    if (!total.isbn().empty())
    {
        Sales_data trans;

        while (read(std::cin, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(std::cout, total);
                std::cout << std::endl;
                total = trans;
            }
        }
        print(std::cout, total);
        std::cout << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```

## 2.27
Screen_ex27.h
```cpp
#ifndef SCREEN_EX23_H_
#define SCREEN_EX23_H_

#include <string>

class Screen {
    public:
        using pos = std::string::size_type;

        Screen() = default;
        Screen(pos ht, pos wd):height(ht), width(wd){ }
        Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

        char get() const { return contents[cursor]; }
        char get(pos r, pos c) const { return contents[r*width+c]; }
        Screen &move(pos r, pos c);
        Screen &set(char);
        Screen &set(pos, pos, char);
        Screen &display(std::ostream &os) {do_display(os); return *this;}
        const Screen &display(std::ostream &os) const {do_display(os); return *this;}

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
        void do_display(std::ostream &os) const {os << contents;}
};

inline Screen &Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

inline Screen &Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

inline Screen &Screen::set(pos r, pos col, char c)
{
	contents[r*width + col] = c;
	return *this;
}

#endif
```

ex27.cpp
```cpp
#include <string>
#include <iostream>
#include "Screen_ex27.h"

int main()
{
	Screen myScreen(5, 5, 'X');
	
	myScreen.move(4, 0).set('#').display(std::cout);
	std::cout << "\n";
	myScreen.display(std::cout);
	std::cout << "\n";

	return 0;
}
```

## 7.28
返回类型是Screen&的输出：  
XXXXXXXXXXXXXXXXXXXX#XXXX  
XXXXXXXXXXXXXXXXXXXX#XXXX  
返回类型是Screen的输出：  
XXXXXXXXXXXXXXXXXXXX#XXXX  
XXXXXXXXXXXXXXXXXXXXXXXXX  
因为这样的话move、set和display返回的是Screen的临时副本，后续set和display操作并不会改变myScreen。  

## 7.29
```linux
$ ./ex29
XXXXXXXXXXXXXXXXXXXX#XXXX
XXXXXXXXXXXXXXXXXXXXXXXXX
```

## 7.30
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

## 7.31
```cpp
//
//  ex7_31.h
//  Exercise 7.31
//
//  Created by pezy on 11/17/14.
//

#ifndef CP5_ex7_31_h
#define CP5_ex7_31_h

class Y;

class X {
    Y* y = nullptr;
};

class Y {
    X x;
};

#endif
```

## 7.32
```cpp
#ifndef SCREEN_EX23_H_
#define SCREEN_EX23_H_

#include <string>
#include <vector>

class Screen;

class Window_mgr
{
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens;
};

class Screen 
{
friend void Window_mgr::clear(ScreenIndex);
public:
    using pos = std::string::size_type;

    Screen() = default;
    Screen(pos ht, pos wd):height(ht), width(wd){ }
    Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

    char get() const { return contents[cursor]; }
    char get(pos r, pos c) const { return contents[r*width+c]; }
    Screen &move(pos r, pos c);
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream &os) {do_display(os); return *this;}
    const Screen &display(std::ostream &os) const {do_display(os); return *this;}

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    void do_display(std::ostream &os) const {os << contents;}
};



inline Screen &Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

inline Screen &Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

inline Screen &Screen::set(pos r, pos col, char c)
{
	contents[r*width + col] = c;
	return *this;
}

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

#endif
```

## 7.33
Screen_ex33.h
```cpp
#ifndef SCREEN_EX23_H_
#define SCREEN_EX23_H_

#include <string>
#include <vector>

class Screen;

class Window_mgr
{
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens;
};

class Screen 
{
friend void Window_mgr::clear(ScreenIndex);
public:
    using pos = std::string::size_type;

    Screen() = default;
    Screen(pos ht, pos wd):height(ht), width(wd){ }
    Screen(pos ht, pos wd, char c):height(ht), width(wd), contents(ht*wd, c){ }

    char get() const { return contents[cursor]; }
    char get(pos r, pos c) const { return contents[r*width+c]; }
    Screen &move(pos r, pos c);
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream &os) {do_display(os); return *this;}
    const Screen &display(std::ostream &os) const {do_display(os); return *this;}
    pos size() const;

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;
    void do_display(std::ostream &os) const {os << contents;}
};



inline Screen &Screen::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

inline Screen &Screen::set(char c)
{
	contents[cursor] = c;
	return *this;
}

inline Screen &Screen::set(pos r, pos col, char c)
{
	contents[r*width + col] = c;
	return *this;
}

Screen::pos Screen::size() const
{
    return height * width;
}

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

#endif
```

ex33.cpp
```cpp
#include <string>
#include <iostream>
#include "Screen_ex33.h"

int main()
{
	Screen myScreen(5, 5, 'X');
	
	myScreen.move(4, 0).set('#').display(std::cout);
	std::cout << "\n";
	myScreen.display(std::cout);
	std::cout << "\n";
	std::cout << myScreen.size() << std::endl;

	return 0;
}
```

## 7.34
dummy_fcn(pos height)中的pos未声明，将会报错。

## 7.35
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

## 7.36
成员的初始化顺序与它们在类定义中的出现顺序一致，所以会先初始化rem再初始化base，初始化rem时会用到base，故程序出错。  
可以改变定义的顺序：  
int base, rem;  

## 7.37
```cpp
Sales_data first_item(cin);   // use Sales_data(std::istream &is) ; its value are up to your input.

int main() {
  Sales_data next;  // use Sales_data(std::string s = ""); bookNo = "", cnt = 0, revenue = 0.0
  Sales_data last("9-999-99999-9"); // use Sales_data(std::string s = ""); bookNo = "9-999-99999-9", cnt = 0, revenue = 0.0
}
```

## 7.38
```cpp
Sales_data(std::istream &is = std::cin) { read(is, *this); }
```

## 7.39
非法。因为这样的话，重载构造函数Sale_data()将不明确。

## 7.40
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

## 7.41
Sales_data_ex41.h
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data;

std::istream &read(std::istream &is, Sales_data &item);
std::ostream &print(std::ostream &os, const Sales_data &item);
Sales_data add(const Sales_data &lhs, const Sales_data &rhs);

struct Sales_data
{
friend std::istream &read(std::istream &is, Sales_data &item);
friend std::ostream &print(std::ostream &os, const Sales_data &item);
friend Sales_data add(const Sales_data &lhs, const Sales_data &rhs);
public:
	Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){std::cout << "Sales_data(const std::string &s, unsigned n, double p)" << std::endl;}
	Sales_data() : Sales_data("", 0, 0){std::cout << "Sales_data() : Sales_data(\"\", 0, 0)" << std::endl;}
	Sales_data(const std::string &s) : Sales_data(s, 0, 0){std::cout << "Sales_data(const std::string &s) : Sales_data" << std::endl;}
	Sales_data(std::istream &is) : Sales_data(){read(is, *this);std::cout << "Sales_data(std::istream &is) : Sales_data()" << std::endl;}
	std::string isbn() const {return bookNo;}
    Sales_data& combine(const Sales_data&);
private:
	inline double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

Sales_data& Sales_data::combine(const Sales_data &rhs)
{
	units_sold += rhs.units_sold;
	revenue += rhs.revenue;

	return *this;
}

inline double Sales_data::avg_price() const
{
	if(units_sold)
		return revenue / units_sold;
	else
		return 0;
}

std::istream &read(std::istream &is, Sales_data &item)
{
	double price = 0;

	is >> item.bookNo >> item.units_sold >> price;
	item.revenue = price * item.units_sold;

	return is;
}

std::ostream &print(std::ostream &os, const Sales_data &item)
{
	os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

	return os;
}

Sales_data add(const Sales_data &lhs, const Sales_data &rhs)
{
	Sales_data sum = lhs;
	sum.combine(rhs);

	return sum;
}

#endif
```
ex41.cpp
```cpp
#include <iostream>
#include <string>
#include "Sales_data_ex41.h"

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2;
    Sales_data sales_data3("001-02");
    Sales_data sales_data4(std::cin);

    return 0;
}
```
执行结果如下：
```linux
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

## 7.42
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

## 7.43
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

## 7.44
非法，因为NoDefault没有默认构造函数。

## 7.45
合法，因为C有默认构造函数。

## 7.46
（a）不正确，没有构造函数时，有时可以生成默认构造函数；  
（b）不正确，默认构造函数是没有构造函数的情况下，由编译器生成的构造函数；  
（c）不正确，默认构造函数在一些情况下非常重要；  
（d）不正确，当类没有显示地定义构造函数时，编译器才会隐式地定义默认构造函数。  

## 7.47
优点：  
防止隐式转换的产生；  
可以只用作初始化。  
缺点：  
只有个单个参数的构造函数才有意义。  

## 7.48
都不会有问题，都显示构造了Sales_data对象。

## 7.49
（a）正确；  
（b）不正确，combine的参数是非常量的引用，所以我们不能将临时参数传递给它，改成Sales_data &combine(const Sales_data&);后正确；  
（c）不正确，后面的const不对，this需要可改变的。  

## 7.50
```cpp
#ifndef PERSON_H_
#define PERSON_H_

#include <string>

struct Person;

std::istream &read(std::istream &is, Person &item);
std::ostream &print(std::ostream &os, const Person &item);

struct Person
{
friend std::istream &read(std::istream &is, Person &item);
friend std::ostream &print(std::ostream &os, const Person &item);
public:
	Person() : name(""), address(""){}
	Person(const std::string &sname, const std::string &saddress = "") : name(sname), address(saddress){}
	explicit Person(std::istream &is){read(is, *this);}
    std::string get_name() const{return name;}
    std::string get_address() const{return address;}
private:
    std::string name;
    std::string address;
};

std::istream &read(std::istream &is, Person &item)
{
	return is >> item.name >> item.address;
}

std::ostream &print(std::ostream &os, const Person &item)
{
	return os << item.name << " " << item.address;
}

#endif
```

## 7.51
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

## 7.52
