#include "Quote.h"
#include "Bulk_quote.h"
#include "Limit_quote.h"
#include <iostream>
#include <functional>
#include <vector>
#include <memory>

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

	std::vector<std::shared_ptr<Quote>> basket;
	// basket.push_back(std::make_shared<Quote>(q));
	basket.push_back(std::make_shared<Bulk_quote>(bq));
	// basket.push_back(std::make_shared<Limit_quote>(lq));

	double total_price = 0;
	for (const auto &vq : basket)
		total_price += vq->net_price(10);
	std::cout << "total_price:" << total_price << std::endl;

	return 0;
}