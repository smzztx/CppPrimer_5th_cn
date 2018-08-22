#include <iostream>
#include <string>
#include <fstream>
#include "../ch07_Classes/Sales_data_ex26.h"

int main(int argc, char **argv)
{
    std::ifstream ifs(argv[1]);
    std::ofstream ofs(argv[2]);

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
                print(ofs, total);
                ofs << std::endl;
                total = trans;
            }
        }
        print(ofs, total);
        ofs << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}