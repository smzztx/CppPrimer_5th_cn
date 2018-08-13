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