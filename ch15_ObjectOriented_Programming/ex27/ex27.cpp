#include "Quote.h"
#include "Bulk_quote.h"
#include "Limit_quote.h"
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
	Bulk_quote bq("A1-001", 80, 5, 0.2);
	Limit_quote lq("A1-001", 80, 5, 0.2);
	print_total(std::cout, q, 10);
	print_total(std::cout, bq, 10);
	print_total(std::cout, lq, 10);

	{
		Bulk_quote bq1(bq);
	}

	// q.debug();
	// std::cout << std::endl;
	// bq.debug();
	// std::cout << std::endl;

	return 0;
}