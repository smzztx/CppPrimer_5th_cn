#ifndef ORQUERY_H_
#define ORQUERY_H_

#include <string>
#include <iostream>
#include <set>
#include "BinaryQuery.h"
#include "Query.h"

class OrQuery : public BinaryQuery
{
	friend Query operator|(const Query&, const Query&);
	OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") { std::cout << "OrQuery(const Query &left, const Query &right)" << std::endl; }
	QueryResult eval(const TextQuery&) const;
};
inline Query operator|(const Query &lhs, const Query &rhs)
{
	return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
	auto right = rhs.eval(text), left = lhs.eval(text);
	auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
	ret_lines->insert(right.begin(), right.end());
	return QueryResult(rep(), ret_lines, left.get_file());
}

#endif