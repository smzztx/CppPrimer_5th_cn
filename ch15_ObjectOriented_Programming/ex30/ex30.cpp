#include "Quote.h"
#include "Bulk_quote.h"
#include "Limit_quote.h"
#include "Basket.h"
#include <iostream>
#include <functional>
#include <vector>
#include <memory>

int main()
{
	Bulk_quote bq("A1-001", 80, 5, 0.2);
	print_total(std::cout, bq, 10);

	std::vector<std::shared_ptr<Quote>> basket;
	basket.push_back(std::make_shared<Bulk_quote>(bq));

	// double total_price = 0;
	// for (const auto &vq : basket)
	// 	total_price += vq->net_price(10);
	// std::cout << "total_price:" << total_price << std::endl;

	Basket basket_object;
	for (int i = 0; i < 10; ++i)
	{
		basket_object.add_item(bq);
	}
	basket_object.total_receipt(std::cout);

	return 0;
}