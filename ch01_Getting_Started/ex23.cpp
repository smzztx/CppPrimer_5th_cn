#include <iostream>
#include "Sales_item.h"

int main()
{
    Sales_item currItem, valItem;
    if (std::cin >> currItem) {
        while (std::cin >> valItem) {
            if (valItem.isbn() == currItem.isbn())
                currItem += valItem;
            else {
                std::cout << currItem << std::endl;
                currItem = valItem;
            }
        }

        std::cout << currItem << std::endl;
    }
    return 0;
}