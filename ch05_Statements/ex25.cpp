#include <iostream>
#include <stdexcept>

int main()
{
	int i1,i2;
	while(std::cin >> i1 >> i2)
	{
		try
		{
			if(i2 == 0)
			{
				throw std::runtime_error("divisor can't be 0");
			}
			std::cout << i1/i2 << std::endl;
		}catch(std::runtime_error err)
		{
			std::cout << err.what()
					  << "\ntry again? enter y or n" << std::endl;
			char c;
			std::cin >> c;
			if(!std::cin || c == 'n') break;
		}
	}
	

	return 0; 
}