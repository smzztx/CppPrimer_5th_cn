#include <string>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    vector<string> str_v;
    string s;
    while(cin >> s)
    {
        str_v.push_back(s);
    }
    
    for(auto &c1 : str_v)
    {
        for(auto &c2 : c1)
        {
            c2 = toupper(c2);
        }
    }

    for(auto c : str_v)
    {
        cout << c <<endl;
    }

    return 0;
}