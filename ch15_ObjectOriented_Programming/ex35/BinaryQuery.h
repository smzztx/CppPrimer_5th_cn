#ifndef BINARYQUERY_H_
#define BINARYQUERY_H_

#include <string>
#include <iostream>
#include "Query_base.h"
#include "Query.h"

class BinaryQuery : public Query_base
{
protected:
	BinaryQuery(const Query &l, const Query &r, std::string s) : lhs(l), rhs(r), opSym(s) { std::cout << "BinaryQuery(const Query &l, const Query &r, std::string s)" << std::endl; }
	std::string rep() const { std::cout << "BinaryQuery::rep()" << opSym << std::endl; return "(" + lhs.rep() + " " + opSym + " " + rhs.rep() + ")"; }
	Query lhs, rhs;
	std::string opSym;
};

#endif