#include "Quote.h"
#include <iostream>

void Quote::debug() const
{
	std::cout << "bookNo: " << bookNo 
	<< "; price: " << price;
}

Quote::Quote(const Quote &q) : bookNo(q.bookNo) , price(q.price)
{
	std::cout << "Quote::Quote(const Quote &q)" << std::endl;
}

Quote::Quote(Quote &&q) noexcept : bookNo(std::move(q.bookNo)) , price(std::move(q.price))
{
	std::cout << "Quote::Quote(Quote &&q)" << std::endl;
}

Quote& Quote::operator=(const Quote &rhs)
{
	if(*this != rhs)
	{
		bookNo = rhs.bookNo;
		price = rhs.price;
	}

	std::cout << "Quote& Quote::operator=(const Quote &rhs)" << std::endl;
	return *this;
}

Quote& Quote::operator=(Quote &&rhs) noexcept
{
	if(*this != rhs)
	{
		bookNo = std::move(rhs.bookNo);
		price = std::move(rhs.price);
	}

	std::cout << "Quote& Quote::operator=(Quote &&rhs)" << std::endl;
	return *this;
}

Quote::~Quote()
{
	std::cout << "~Quote::Quote()" << std::endl;
}

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}