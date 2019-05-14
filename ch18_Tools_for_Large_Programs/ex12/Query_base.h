#ifndef QUERY_BASE_H_
#define QUERY_BASE_H_

#include <string>
#include <iostream>
#include "TextQuery.h"
#include "Query.h"
namespace chapter15
{
	class Query_base
	{
		friend class Query;
	protected:
		using line_no = chapter10::TextQuery::line_no;
		virtual ~Query_base() = default;
	private:
		virtual chapter10::QueryResult eval(const chapter10::TextQuery&) const = 0;
		virtual std::string rep() const = 0;
	};
}

#endif