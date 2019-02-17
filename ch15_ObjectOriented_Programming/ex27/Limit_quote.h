#ifndef LIMIT_QUOTE_H_
#define LIMIT_QUOTE_H_

#include "Disc_quote.h"
#include <string>
#include <iostream>

class Limit_quote : public Disc_quote
{
public:
	Limit_quote() = default;
	Limit_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }
	Limit_quote(const Limit_quote&);
	Limit_quote(Limit_quote&&) noexcept;
	Limit_quote& operator=(const Limit_quote&);
	Limit_quote& operator=(Limit_quote&&) noexcept;
	double net_price(std::size_t) const override;
	void debug() const override;
	~Limit_quote();
};

#endif