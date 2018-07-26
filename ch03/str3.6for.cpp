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

    for(string::size_type index = 0;index < str.size();++index)
    {
        str[index] = 'X';
    }
    cout<<str<<endl;

    string::size_type index = 0;
    while(str[index]!='\0')
    {
        str[index] = 'X';
        index++;
    }
    cout<<str<<endl;
    
    string s;
    cout << s[0] << endl;

    return 0;
}