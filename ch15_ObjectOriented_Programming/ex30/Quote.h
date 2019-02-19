#ifndef QUOTE_H_
#define QUOTE_H_

#include <string>
#include <iostream>

class Quote
{
friend bool operator!=(const Quote &lhs, const Quote &rhs) { return lhs.bookNo != rhs.bookNo && lhs.price != rhs.price; }
public:
	Quote() = default;
	Quote(const std::string &book, double sales_price) : bookNo(book), price(sales_price) {}
	Quote(const Quote&);
	Quote(Quote&&) noexcept;
	Quote& operator=(const Quote&);
	Quote& operator=(Quote&&) noexcept;
	std::string isbn() const { return bookNo; }
	virtual Quote* clone() const & { return new Quote(*this); }
	virtual Quote* clone() && { return new Quote(std::move(*this)); }
	virtual double net_price(std::size_t n) const { return n * price; }
	virtual void debug() const;
	virtual ~Quote();
private:
	std::string bookNo;
protected:
	double price = 0;
};

double print_total(std::ostream &os, const Quote &item, size_t n);

#endif