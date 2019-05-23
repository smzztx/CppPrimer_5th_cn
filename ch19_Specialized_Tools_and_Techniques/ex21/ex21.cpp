#include <string>
#include "Sales_data.h"
#include <iostream>

class Token
{
public:
	Token() : tok(INT), ival{0} { std::cout << "Token() : tok(INT), ival{0}" << std::endl; }
	Token(const Token &t) : tok(t.tok) { std::cout << "Token(const Token &t) : tok(t.tok)" << std::endl; copyUnion(t); }
	Token &operator=(const Token&);
	Token(Token &&t) noexcept : tok(t.tok)
	{
		std::cout << "Token(Token &&t) noexcept : tok(t.tok)" << std::endl;
		switch(t.tok)
		{
			case INT: ival = t.ival;break;
			case DBL: dval = t.dval;break;
			case CHAR: cval = t.cval;break;
			case STR: sval = t.sval;break;
			case SD: sdval = t.sdval;break;
		}
	}
	Token &operator=(Token&&) noexcept;
	~Token() { if(tok == STR) sval.std::string::~string(); }
	Token &operator=(const std::string&);
	Token &operator=(char);
	Token &operator=(int);
	Token &operator=(double);
	Token &operator=(const Sales_data &sd);
private:
	enum{INT, CHAR, DBL, STR, SD} tok;
	union{
		char cval;
		int ival;
		double dval;
		std::string sval;
		Sales_data sdval;
	};
	void copyUnion(const Token&);
};

Token &Token::operator=(int i)
{
	std::cout << "Token &Token::operator=(int i)" << std::endl;
	if(tok == STR) sval.std::string::~string();
	else if(tok == SD) sdval.Sales_data::~Sales_data();
	ival = i;
	tok = INT;
	return *this;
}

Token &Token::operator=(char c)
{
	std::cout << "Token &Token::operator=(char c)" << std::endl;
	if(tok == STR) sval.std::string::~string();
	else if(tok == SD) sdval.Sales_data::~Sales_data();
	cval = c;
	tok = CHAR;
	return *this;
}

Token &Token::operator=(double d)
{
	std::cout << "Token &Token::operator=(double d)" << std::endl;
	if(tok == STR) sval.std::string::~string();
	else if(tok == SD) sdval.Sales_data::~Sales_data();
	dval = d;
	tok = DBL;
	return *this;
}

Token &Token::operator=(const std::string &s)
{
	std::cout << "Token &Token::operator=(const std::string &s)" << std::endl;
	if(tok == SD) sdval.Sales_data::~Sales_data();
	if(tok == STR) sval = s;
	else new(&sval) std::string(s);
	tok = STR;
	return *this;
}

Token &Token::operator=(const Sales_data &sd)
{
	std::cout << "Token &Token::operator=(const Sales_data &sd)" << std::endl;
	if(tok == STR) sval.std::string::~string();
	if(tok == SD) sdval = sd;
	else new(&sval) Sales_data(sd);
	tok = SD;
	return *this;
}

void Token::copyUnion(const Token &t)
{
	switch(t.tok)
	{
		case INT: ival = t.ival;break;
		case DBL: dval = t.dval;break;
		case CHAR: cval = t.cval;break;
		case STR: new(&sval) std::string(t.sval);break;
		case SD: new(&sdval) Sales_data(t.sdval);break;
	}
	
}

Token &Token::operator=(const Token &t)
{
	std::cout << "Token &Token::operator=(const Token &t)" << std::endl;
	if(tok == STR && t.tok != STR) sval.std::string::~string();
	else if(tok == STR && t.tok == STR) sval = t.sval;
	else if(tok == SD && t.tok != SD) sdval.Sales_data::~Sales_data();
	else if(tok == SD && t.tok == SD) sdval = t.sdval;
	else copyUnion(t);
	tok = t.tok;
	return *this;
}

Token &Token::operator=(Token&& t) noexcept
{
	std::cout << "Token &Token::operator=(Token&& t) noexcept" << std::endl;
	tok = t.tok;
	switch(t.tok)
	{
		case INT: ival = t.ival;break;
		case DBL: dval = t.dval;break;
		case CHAR: cval = t.cval;break;
		case STR: sval = t.sval;break;
		case SD: sdval = t.sdval;break;
	}
	return *this;
}

int main()
{
	std::cout << "---------1----------" << std::endl;
	Token s;
	std::cout << "---------2----------" << std::endl;
	Sales_data sales_data1("001-01", 1, 100);
	std::cout << "---------3----------" << std::endl;
	s = sales_data1;
	std::cout << "---------4----------" << std::endl;
	s = std::string("a");
	std::cout << "---------5----------" << std::endl;
	s = Token();
	std::cout << "---------6----------" << std::endl;
	Token s1(std::move(s));
	// Token s1(Token(s));
	std::cout << "---------7----------" << std::endl;

	return 0;
}