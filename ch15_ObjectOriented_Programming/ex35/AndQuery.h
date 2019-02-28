#ifndef ANDQUERY_H_
#define ANDQUERY_H_

#include <string>
#include <iostream>
#include <memory>
#include <set>
#include "BinaryQuery.h"
#include "Query.h"

class AndQuery : public BinaryQuery
{
	friend Query operator&(const Query&, const Query&);
	AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") { std::cout << "AndQuery(const Query &left, const Query &right)" << std::endl; }
	QueryResult eval(const TextQuery&) const;
};

inline Query operator&(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
}

QueryResult AndQuery::eval(const TextQuery &text) const
{
	// auto right = rhs.eval(text), left = lhs.eval(text);
	// auto ret_lines = std::make_shared<std::set<line_no>>();
	// set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));
	// return QueryResult(rep(), ret_lines, left.get_file());
}

#endif