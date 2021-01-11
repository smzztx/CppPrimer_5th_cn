// example.C
#include "ex58.h"
#include <vector>
//you should  initialize a static atributte of a class in main, instead of the .cpp of the class, or just after the class definition in theglobal scope of the .h
double Example::rate = 6.5;
std::vector<double> Example::vec(vecSize);
// std::vector<double> Example::vec(Example::vecSize);

int main()
{
	return 0;
}
