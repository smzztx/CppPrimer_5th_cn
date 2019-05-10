#include <iostream>
#include <cmath>

int main()
{
	std::cout <<"default format: " << sqrt(2.0) << '\n'
		<< "scientific: " << std::scientific << sqrt(2.0) << '\n'
		<< "fixed decimal: " << std::fixed << sqrt(2.0) << '\n'
		<< "hexidecimal: " << std::uppercase << std::hexfloat << sqrt(2.0) << '\n'
		<< "use defaults: " << std::defaultfloat << sqrt(2.0)
		<< "\n\n";

	return 0;
}