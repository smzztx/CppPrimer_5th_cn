#include <iostream>
#include <string>
#include "Sales_data.h"
#include <unordered_set>
#include <algorithm>
#include <tuple>

namespace std
{
	template <>
	struct hash<Sales_data>
	{
		typedef size_t result_type;
		typedef Sales_data argument_type;
		size_t operator()(const Sales_data &s) const;
	};
	size_t hash<Sales_data>::operator()(const Sales_data &s) const
	{
		return hash<std::string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
	}
}

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}

typedef std::tuple<std::vector<Sales_data>::size_type, std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator> matches;

std::vector<matches> findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book)
{
	std::vector<matches> ret;
	for(auto it = files.cbegin(); it != files.cend(); ++it)
	{
		auto found = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);
		if(found.first != found.second)
			ret.push_back(std::make_tuple(it - files.cbegin(), found.first, found.second));
	}
	return ret;
}

void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
	std::string s;
	while(in >> s)
	{
		auto trans = findBook(files, s);
		if(trans.empty())
		{
			std::cout << s << " not found in any stores" << std::endl;
			continue;
		}
		for(const auto &store : trans)
			os << "store " << std::get<0>(store) << " sales: " << std::accumulate(std::get<1>(store), std::get<2>(store), Sales_data(s)) << std::endl;
	}
}

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2("001-01", 2, 100);
    Sales_data sales_data3("001-02", 2, 80);

    std::vector<Sales_data> vs1 = {sales_data1, sales_data3};
    std::vector<Sales_data> vs2 = {sales_data2};
    std::vector<std::vector<Sales_data>> vvs;

    reportResults(std::cin, std::cout, vvs);

 //    std::cout << std::hex << std::hash<std::string>()("001-01") << std::endl;
 //    std::cout << std::hex << std::hash<unsigned>()(1) << std::endl;
 //    std::cout << std::hex << std::hash<double>()(100) << std::endl;

 //    std::unordered_multiset<Sales_data> SDset;
 //    SDset.emplace(sales_data1);
 //    SDset.emplace("001-03", 1, 200);
 //    SDset.emplace(sales_data3);

	// for(const auto &item : SDset)
	// 	std::cout << "the hash code of " << item.isbn() <<":\n0x" << std::hex << std::hash<Sales_data>()(item) << "\n";

    return 0;
}