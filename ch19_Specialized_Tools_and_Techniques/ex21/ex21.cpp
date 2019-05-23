#include <string>
#include "Sales_data.h"

class Token
{
public:
	Token() : tok(INT), ival{0} { }
	Token(const Token &t) : tok(t.tok) { copyUnion(t); }
	Token &operator=(const Token&);
	Token(Token &&t) noexcept : tok(t.tok)
	{
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
	if(tok == STR) sval.std::string::~string();
	else if(tok == SD) sdval.Sales_data::~Sales_data();
	ival = i;
	tok = INT;
	return *this;
}

Token &Token::operator=(char c)
{
	if(tok == STR) sval.std::string::~string();
	else if(tok == SD) sdval.Sales_data::~Sales_data();
	cval = c;
	tok = CHAR;
	return *this;
}

Token &Token::operator=(double d)
{
	if(tok == STR) sval.std::string::~string();
	else if(tok == SD) sdval.Sales_data::~Sales_data();
	dval = d;
	tok = DBL;
	return *this;
}

Token &Token::operator=(const std::string &s)
{
	if(tok == SD) sdval.Sales_data::~Sales_data();
	if(tok == STR) sval = s;
	else new(&sval) std::string(s);
	tok = STR;
	return *this;
}

Token &Token::operator=(const Sales_data &sd)
{
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
	Token s;
	Sales_data sales_data1("001-01", 1, 100);
	s = sales_data1;
	s = std::string("a");

	return 0;
}