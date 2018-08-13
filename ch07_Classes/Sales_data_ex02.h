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