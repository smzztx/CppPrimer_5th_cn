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
