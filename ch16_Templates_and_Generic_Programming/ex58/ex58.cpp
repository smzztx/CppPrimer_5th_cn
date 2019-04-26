#include "StrVec.h"
#include "Vec.h"

int main()
{
	StrVec s;
	s.emplace_back("a");
	// s.emplace_back("bb", "ccc");	//error use of it, forward params to constructor

	Vec<std::string> Vs;
	Vs.emplace_back("a");

	return 0;
}