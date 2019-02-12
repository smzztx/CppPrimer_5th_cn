#ifndef LIMIT_QUOTE_H_
#define LIMIT_QUOTE_H_

#include "Quote_ex03.h"
#include <string>

class Limit_quote : public Quote
{
public:
	Limit_quote() = default;
	Limit_quote(const std::string &book, double p, std::size_t qty, double disc) : Quote(book, p), max_qty(qty), discount(disc) { }
	double net_price(std::size_t) const override;
private:
	std::size_t max_qty = 0;
	double discount = 0.0;
};

double Limit_quote::net_price(size_t cnt) const
{
	if(cnt > max_qty) return max_qty * (1 - discount) * price + (cnt - max_qty)*price;
	else return cnt * price;
}

#endif