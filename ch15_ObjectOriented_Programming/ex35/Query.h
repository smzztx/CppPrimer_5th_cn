#ifndef QUERY_H_
#define QUERY_H_

#include <string>
#include "Query_base.h"
#include "WordQuery.h"
#include "NotQuery.h"
#include "AndQuery.h"
#include "OrQuery.h"

class Query
{
	friend Query operator~(const Query&);
	friend Query operator|(const Query&, cosnt Query&);
	friend Query operator&(const Query&, cosnt Query&);
public:
	Query(cosnt std::string &s) : q(new WordQuery(s)) { }
	QueryResult eval(const TextQuery &t) const { return q->eval(t); }
	std::string rep() const { return q->rep(); }
private:
	Query(std::shared_ptr<Query_base> query) : q(query) { }
	std::shared_ptr<Query_base> q;
};

std::ostream& operator<<(std::ostream &os, const Query &query)
{
	return os << query.rep();
}

#endif