#include <iostream>
#include <string>
#include "Sales_data_ex13.h"

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2;
    Sales_data sales_data3("001-02");
    Sales_data sales_data4(std::cin);
    std::cout << sales_data4 << std::endl;

    return 0;
}