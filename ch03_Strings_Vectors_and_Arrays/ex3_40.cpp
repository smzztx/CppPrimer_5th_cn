#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

int main()
{
    char ca1[] = "aaa";
    char ca2[] = "abc";
    char ca3[10];

    strcpy(ca3,ca1);
    strcat(ca3,ca2);

    cout << ca3 << endl;

    return 0;
}