#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string str = "1122aabbcc 33";

    for(auto &c : str)
    {
        c = 'X';
    }
    cout<<str<<endl;

    return 0;
}