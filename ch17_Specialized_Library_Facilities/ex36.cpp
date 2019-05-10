#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
	std::cout << std::left << std::setw(16) <<"default format: " << std::right << std::setw(25) << sqrt(2.0) << '\n'
		<< std::left << std::setw(16) << "scientific: " << std::scientific << std::right << std::setw(25) << sqrt(2.0) << '\n'
		<< std::left << std::setw(16) << "fixed decimal: " << std::fixed << std::right << std::setw(25) << sqrt(2.0) << '\n'
		<< std::left << std::setw(16) << "hexidecimal: " << std::uppercase << std::hexfloat << std::right << std::setw(25) << sqrt(2.0) << '\n'
		<< std::left << std::setw(16) << "use defaults: " << std::defaultfloat << std::right << std::setw(25) << sqrt(2.0)
		<< "\n\n";

	return 0;
}