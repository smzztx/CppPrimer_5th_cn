#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Disc_quote_ex15.h"
#include <string>
#include <iostream>

class Bulk_quote : public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }
	double net_price(std::size_t) const override;
	void debug() const override;
};

double Bulk_quote::net_price(size_t cnt) const
{
	if(cnt >= quantity) return cnt * (1 - discount) * price;
	else return cnt * price;
}

void Bulk_quote::debug() const
{
	Quote::debug();
	std::cout << "; quantity: " << quantity
	<< "; discount: " << discount;
}

#endif