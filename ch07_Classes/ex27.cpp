#include <string>
#include <iostream>
#include "Screen_ex27.h"

int main()
{
	Screen myScreen(5, 5, 'X');
	
	myScreen.move(4, 0).set('#').display(std::cout);
	std::cout << "\n";
	myScreen.display(std::cout);
	std::cout << "\n";

	return 0;
}