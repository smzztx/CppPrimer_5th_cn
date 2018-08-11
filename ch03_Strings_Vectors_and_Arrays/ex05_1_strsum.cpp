#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in,str_sum;

    while(cin>>str_in)
    {
        str_sum = str_sum + str_in;
    }
    cout << str_sum << endl;
    return 0;
}