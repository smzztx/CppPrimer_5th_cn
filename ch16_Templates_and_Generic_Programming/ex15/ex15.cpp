#include <string>
#include <iostream>
#include "Screen.h"

int main()
{
	Screen<5, 5> myScreen('X');
	
	myScreen.move(4, 0).set('#').display(std::cout);
	std::cout << "\n";
	myScreen.display(std::cout);
	std::cout << "\n";
	std::cout << myScreen << std::endl;
	// std::cout << myScreen.size() << std::endl;

	return 0;
}