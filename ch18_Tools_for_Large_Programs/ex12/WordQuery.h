#ifndef WORDQUERY_H_
#define WORDQUERY_H_

#include <string>
#include <iostream>
#include "Query_base.h"
#include "Query.h"

namespace chapter15
{
	class WordQuery : public Query_base
	{
		friend class Query;
	public:
		WordQuery(const std::string &s) : query_word(s) { std::cout << "WordQuery(const std::string &s)" << std::endl; }
		chapter10::QueryResult eval(const chapter10::TextQuery &t) const { return t.query(query_word); }
		std::string rep() const { std::cout << "WordQuery::rep()" << std::endl; return query_word; }
		std::string query_word;
	};
}

#endif