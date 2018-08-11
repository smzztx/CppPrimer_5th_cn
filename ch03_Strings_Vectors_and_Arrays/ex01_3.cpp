#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    int small = 0, big = 0;
    cout << "please input two integers:";
    cin >> small >> big;

    if (small > big) {
        int tmp = small;
        small = big;
        big = tmp;
    }

    while (small <= big) {
        cout << small << " ";
        ++small;
    }
    cout << endl;

    return 0;
}