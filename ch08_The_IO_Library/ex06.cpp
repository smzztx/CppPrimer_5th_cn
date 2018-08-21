#include <iostream>
#include <string>
#include <fstream>
#include "Sales_data_ex06.h"

int main(int argc, char **argv)
{
    std::ifstream ifs(argv[1]);

    if(!ifs) return 1;

    Sales_data total(ifs);

    if (!total.isbn().empty())
    {
        Sales_data trans;

        while (read(ifs, trans))
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