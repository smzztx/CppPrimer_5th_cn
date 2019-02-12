#include "Quote_ex11.h"
#include "Limit_quote_ex16.h"
#include <iostream>
#include <functional>

double print_total(std::ostream &os, const Quote &item, size_t n)
{
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn() << " # sold: " << n << " total due: " << ret << std::endl;
	return ret;
}

int main()
{
	Quote q("A1-001", 80);
	Limit_quote bq("A1-001", 80, 5, 0.2);
	print_total(std::cout, q, 10);
	print_total(std::cout, bq, 10);

	// q.debug();
	// std::cout << std::endl;
	// bq.debug();
	// std::cout << std::endl;

	return 0;
}