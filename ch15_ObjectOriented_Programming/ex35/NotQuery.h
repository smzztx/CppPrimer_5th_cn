#ifndef NOTQUERY_H_
#define NOTQUERY_H_

#include <string>
#include <iostream>
#include <memory>
#include <set>
#include "Query_base.h"
#include "Query.h"

class NotQuery : public Query_base
{
	friend Query operator~(const Query&);
	NotQuery(const Query &q) : query(q) { std::cout << "NotQuery(const Query &q)" << std::endl; }
	std::string rep() const { return "~(" + query.rep() + ")"; }
	QueryResult eval(const TextQuery&) const;
	Query query;
};

inline Query operator~(const Query &operand)
{
	return std::shared_ptr<Query_base>(new NotQuery(operand));
}

QueryResult NotQuery::eval(const TextQuery &text) const
{
// 	auto result = query.eval(text);
// 	auto ret_lines = std::make_shared<std::set<line_no>>();
// 	auto beg = result.begin(), end = result.end();
// 	auto sz = result.get_file()->size();
// 	for(size_t n = 0; n != sz; ++n)
// 	{
// 		if(beg == end || *beg != n)
// 			ret_lines->insert(n);
// 		else if(beg != end)
// 			++beg;
// 	}
// 	return QueryResult(rep(), ret_lines, result.get_file());
}

#endif