#include <set>
#include <iostream>
#include <string>
#include "../ch07_Classes/Sales_data_ex26.h"

bool compareIsbn(const Sales_data &sales_data1, const Sales_data &sales_data2)
{
	return sales_data1.isbn() < sales_data2.isbn();
}

int main()
{
	using COMPAREISBN = bool (*)(const Sales_data&, const Sales_data&);
	// std::multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
	std::multiset<Sales_data, COMPAREISBN> bookstore(compareIsbn);
	// std::multiset<Sales_data, bool (*)(const Sales_data&, const Sales_data&)> bookstore(compareIsbn);

	return 0;
}