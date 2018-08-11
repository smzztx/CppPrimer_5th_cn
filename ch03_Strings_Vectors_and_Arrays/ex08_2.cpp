#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string str = "1122aabbcc 33";

    string::size_type index = 0;
    while(str[index]!='\0')
    {
        str[index] = 'X';
        index++;
    }
    cout<<str<<endl;

    return 0;
}