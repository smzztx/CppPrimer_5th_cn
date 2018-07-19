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
    vector<string> text{"abcd,efg","","AAaa"};
    for(auto it = text.begin();it != text.end() && !it->empty();++it)
    {
        for(auto &c : *it)
            c = toupper(c);
    }
    
    for(auto it = text.begin();it != text.end();++it)
    {
        cout << *it << endl;
    }

    return 0;
}