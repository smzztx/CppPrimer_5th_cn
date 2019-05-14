#ifndef ANDQUERY_H_
#define ANDQUERY_H_

#include <string>
#include <iostream>
#include <memory>
#include <set>
#include "BinaryQuery.h"
#include "Query.h"

namespace chapter15
{
	class AndQuery : public BinaryQuery
	{
		friend Query operator&(const Query&, const Query&);
		AndQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "&") { std::cout << "AndQuery(const Query &left, const Query &right)" << std::endl; }
		chapter10::QueryResult eval(const chapter10::TextQuery&) const;
	};

	inline Query operator&(const Query &lhs, const Query &rhs)
	{
		return std::shared_ptr<Query_base>(new AndQuery(lhs, rhs));
	}

	chapter10::QueryResult AndQuery::eval(const chapter10::TextQuery &text) const
	{
		auto right = rhs.eval(text), left = lhs.eval(text);
		auto ret_lines = std::make_shared<std::set<line_no>>();
		set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(*ret_lines, ret_lines->begin()));
		return chapter10::QueryResult(rep(), ret_lines, left.get_file());
	}
}

#endif