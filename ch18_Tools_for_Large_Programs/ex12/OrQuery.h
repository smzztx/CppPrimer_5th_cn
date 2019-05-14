#ifndef ORQUERY_H_
#define ORQUERY_H_

#include <string>
#include <iostream>
#include <set>
#include "BinaryQuery.h"
#include "Query.h"

namespace chapter15
{
	class OrQuery : public BinaryQuery
	{
		friend Query operator|(const Query&, const Query&);
		OrQuery(const Query &left, const Query &right) : BinaryQuery(left, right, "|") { std::cout << "OrQuery(const Query &left, const Query &right)" << std::endl; }
		chapter10::QueryResult eval(const chapter10::TextQuery&) const;
	};
	inline Query operator|(const Query &lhs, const Query &rhs)
	{
		return std::shared_ptr<Query_base>(new OrQuery(lhs, rhs));
	}

	chapter10::QueryResult OrQuery::eval(const chapter10::TextQuery &text) const
	{
		auto right = rhs.eval(text), left = lhs.eval(text);
		auto ret_lines = std::make_shared<std::set<line_no>>(left.begin(), left.end());
		ret_lines->insert(right.begin(), right.end());
		return chapter10::QueryResult(rep(), ret_lines, left.get_file());
	}
}

#endif