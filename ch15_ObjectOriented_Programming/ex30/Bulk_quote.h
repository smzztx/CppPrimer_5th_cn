#ifndef BULK_QUOTE_H_
#define BULK_QUOTE_H_

#include "Disc_quote.h"
#include <string>
#include <iostream>

class Bulk_quote : public Disc_quote
{
public:
	Bulk_quote() = default;
	using Disc_quote::Disc_quote;
	Bulk_quote(Bulk_quote&);
	Bulk_quote(Bulk_quote&&) noexcept;
	Bulk_quote& operator=(Bulk_quote&);
	Bulk_quote& operator=(Bulk_quote&&) noexcept;
	Bulk_quote* clone() const & { return new Bulk_quote(*this); }
	// Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }
	double net_price(std::size_t) const override;
	void debug() const override;
	~Bulk_quote() override;
};

#endif