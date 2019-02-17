#include "Limit_quote.h"
#include <iostream>

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

Limit_quote::Limit_quote(const Limit_quote &lq) : Disc_quote(lq)
{
	std::cout << "Limit_quote::Limit_quote(Limit_quote &lq)" << std::endl;
}

Limit_quote::Limit_quote(Limit_quote &&lq) noexcept : Disc_quote(std::move(lq))
{
	std::cout << "Limit_quote::Limit_quote(Limit_quote &&lq)" << std::endl;
}

Limit_quote& Limit_quote::operator=(const Limit_quote &rhs)
{
	Disc_quote::operator=(rhs);

	std::cout << "Limit_quote& Limit_quote::operator=(const Limit_quote &rhs)" << std::endl;
	return *this;
}

Limit_quote& Limit_quote::operator=(Limit_quote &&rhs) noexcept
{
	Disc_quote::operator=(std::move(rhs));

	std::cout << "Limit_quote& Limit_quote::operator=(Limit_quote &&rhs) noexcept" << std::endl;
	return *this;
}

Limit_quote::~Limit_quote()
{
	std::cout << "Limit_quote::~Limit_quote()" << std::endl;
}