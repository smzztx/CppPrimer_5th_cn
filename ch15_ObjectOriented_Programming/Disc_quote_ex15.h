#ifndef DISC_QUOTE_H_
#define DISC_QUOTE_H_

#include "Quote_ex11.h"
#include <string>

class Disc_quote : public Quote
{
public:
	Disc_quote() = default;
	Disc_quote(const std::string &book, double price, std::size_t qty, double disc)
	: Quote(book, price), quantity(qty), discount(disc) { }
	double net_price(std::size_t) const = 0;
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};


#endif