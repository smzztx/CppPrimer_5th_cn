#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in,str;
    cin>>str_in;
    for(auto c : str_in)
        if(!ispunct(c))
            str = str + c;
    cout << str << endl;
    return 0;
}