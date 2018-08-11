#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in;
    while(getline(cin,str_in))
    {
        cout << str_in << endl;
    }

    return 0;
}