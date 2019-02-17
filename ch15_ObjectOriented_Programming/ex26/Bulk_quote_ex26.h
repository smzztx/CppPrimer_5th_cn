#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Disc_quote_ex26.h"
#include <string>
#include <iostream>

class Bulk_quote : public Disc_quote
{
public:
	Bulk_quote() = default;
	Bulk_quote(const std::string &book, double price, std::size_t qty, double disc) : Disc_quote(book, price, qty, disc) { }
	Bulk_quote(Bulk_quote&);
	Bulk_quote(Bulk_quote&&) noexcept;
	Bulk_quote& operator=(Bulk_quote&);
	Bulk_quote& operator=(Bulk_quote&&) noexcept;
	double net_price(std::size_t) const override;
	void debug() const override;
	~Bulk_quote() override;
};

#endif