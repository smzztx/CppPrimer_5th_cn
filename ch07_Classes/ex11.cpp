#include <string>
#include <iostream>
#include "Sales_data_ex11.h"

int main()
{
	Sales_data sales_data1;
	print(std::cout, sales_data1) << std::endl;

	Sales_data sales_data2("1-01");
	print(std::cout, sales_data2) << std::endl;

	Sales_data sales_data3("1-01", 1, 100);
	print(std::cout, sales_data3) << std::endl;

	Sales_data sales_data4(std::cin);
	print(std::cout, sales_data4) << std::endl;

	// Sales_data sales_data5();
	// print(std::cout, sales_data5) << std::endl;

	return 0;
}