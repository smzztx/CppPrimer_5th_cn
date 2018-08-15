#include <iostream>
#include <string>
#include "Sales_data_ex26.h"

int main()
{
    Sales_data total(std::cin);

    if (!total.isbn().empty())
    {
        Sales_data trans;

        while (read(std::cin, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(std::cout, total);
                std::cout << std::endl;
                total = trans;
            }
        }
        print(std::cout, total);
        std::cout << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}