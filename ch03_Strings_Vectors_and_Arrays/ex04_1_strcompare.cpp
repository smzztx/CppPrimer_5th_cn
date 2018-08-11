#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in1,str_in2;

    cin>>str_in1>>str_in2;
    if(str_in1 != str_in2)
    {
        if(str_in1>str_in2)
        {
            cout << str_in1 << endl;
        }else
        {
            cout << str_in2 << endl;
        }
    }

    return 0;
}