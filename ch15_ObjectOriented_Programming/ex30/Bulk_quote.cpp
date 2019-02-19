#include "Bulk_quote.h"
#include <iostream>

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

Bulk_quote::Bulk_quote(const Bulk_quote &bq) : Disc_quote(bq)
{
	std::cout << "Bulk_quote::Bulk_quote(Bulk_quote &bq)" << std::endl;
}

Bulk_quote::Bulk_quote(Bulk_quote &&bq) noexcept : Disc_quote(std::move(bq))
{
	std::cout << "Bulk_quote::Bulk_quote(Bulk_quote &&bq)" << std::endl;
}

Bulk_quote& Bulk_quote::operator=(Bulk_quote &rhs)
{
	Disc_quote::operator=(rhs);

	std::cout << "Bulk_quote& Bulk_quote::operator=(Bulk_quote &rhs)" << std::endl;
	return *this;
}

Bulk_quote& Bulk_quote::operator=(Bulk_quote &&rhs) noexcept
{
	Disc_quote::operator=(std::move(rhs));

	std::cout << "Bulk_quote& Bulk_quote::operator=(Bulk_quote &&rhs)" << std::endl;
	return *this;
}

Bulk_quote::~Bulk_quote()
{
	std::cout << "Bulk_quote::~Bulk_quote()" << std::endl;
}