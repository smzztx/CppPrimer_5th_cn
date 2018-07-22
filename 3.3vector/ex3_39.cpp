#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::string;


int main()
{
    string s1 = "aabb";
    string s2 = "aabb";

    if(s1 == s2)
    {
        cout << "equal" << endl;
    }else
    {
        cout << "not equal" << endl;
    }

    const char ca1[] = {'a','b','c'};
    const char ca2[] = "abc";

    if(strcmp(ca1,ca2) == 0)
    {
        cout << "equal" <<endl;
    }else
    {
        cout << "not equal" <<endl;
    }

    return 0;
}