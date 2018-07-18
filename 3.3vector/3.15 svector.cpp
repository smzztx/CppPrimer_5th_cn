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
    vector<string> sv;
    string str;

    while(cin >> str)
    {
        sv.push_back(str);
        // cout << str << endl;
    }

    return 0;
}