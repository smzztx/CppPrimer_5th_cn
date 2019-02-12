#ifndef LIMIT_QUOTE_H_
#define LIMIT_QUOTE_H_

#include "Disc_quote_ex15.h"
#include <string>
#include <iostream>

class Limit_quote : public Disc_quote
{
public:
	Limit_quote() = default;
	Limit_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }
	double net_price(std::size_t) const override;
	void debug() const override;
};

double Limit_quote::net_price(size_t cnt) const
{
	if(cnt > quantity) return quantity * (1 - discount) * price + (cnt - quantity)*price;
	else return cnt * price;
}

void Limit_quote::debug() const
{
	Quote::debug();
	std::cout << "; quantity: " << quantity
	<< "; discount: " << discount;
}

#endif