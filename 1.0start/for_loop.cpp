#include <iostream>

int main()
{
    int sum = 0;
    for(int i = -100;i <= 100; i++ )
    {
        sum += i;
        std::cout << i << std::endl;
    }
    std::cout << sum << std::endl;

    unsigned int u = 10, u2 = 42;
    std::cout << u-u2 << std::endl;
    std::cout << u2-u << std::endl;

    return 0;
}