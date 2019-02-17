#ifndef DISC_QUOTE_H_
#define DISC_QUOTE_H_

#include "Quote.h"
#include <string>

class Disc_quote : public Quote
{
friend bool operator!=(const Disc_quote &lhs, const Disc_quote &rhs) { return Quote(lhs) != Quote(rhs) && lhs.quantity != rhs.quantity && lhs.discount != rhs.discount; }
public:
	Disc_quote() = default;
	Disc_quote(const std::string &book, double price, std::size_t qty, double disc)
	: Quote(book, price), quantity(qty), discount(disc) { }
	Disc_quote(const Disc_quote &dq) : Quote(dq) , quantity(dq.quantity) , discount(dq.discount)
	{
		std::cout << "Disc_quote(const Disc_quote &dq)" << std::endl;
	}
	Disc_quote(Disc_quote &&dq) noexcept : Quote(std::move(dq)) , quantity(std::move(dq.quantity)) , discount(std::move(dq.discount))
	{
		std::cout << "Disc_quote(Disc_quote &&dq)" << std::endl;
	}
	double net_price(std::size_t) const = 0;
	Disc_quote& operator=(const Disc_quote &rhs)
	{
		if(*this != rhs)
		{
			Quote::operator=(rhs);
			quantity = rhs.quantity;
			discount = rhs.discount;
		}

		std::cout << "Disc_quote& operator=(const Disc_quote &rhs)" << std::endl;
		return *this;
	}
	Disc_quote& operator=(const Disc_quote &&rhs) noexcept
	{
		if(*this != rhs)
		{
			Quote::operator=(std::move(rhs));
			quantity = std::move(rhs.quantity);
			discount = std::move(rhs.discount);
		}

		std::cout << "Disc_quote& operator=(const Disc_quote &&rhs) noexcept" << std::endl;
		return *this;
	}
	~Disc_quote() override { std::cout << "~Disc_quote()" << std::endl; }
protected:
	std::size_t quantity = 0;
	double discount = 0.0;
};


#endif