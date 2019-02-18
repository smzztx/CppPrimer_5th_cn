#ifndef BASKET_H_
#define BASKET_H_

#include "Quote.h"
#include <iostream>
#include <memory>
#include <set>

class Basket
{
public:
	void add_item(const std::shared_ptr<Quote> &sale) { items.insert(sale); }
	void add_item(const Quote &sale);
	void add_item(Quote &&sale);
	double total_receipt(std::ostream&) const;
private:
	static bool compare(const std::shared_ptr<Quote> &lhs, const std::shared_ptr<Quote> &lhs) { return lhs->isbn() < rhs->isbn(); }
	std::multiset<std::shared_ptr<Quote>, decltype(compare) *> items{compare};
};

#endif