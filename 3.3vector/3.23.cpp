#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> text{0,1,2,3,4,5,6,7,8,9};
    for(auto it = text.begin();it != text.end();++it)
    {
        *it = *it * 2;
    }
    
    for(auto it = text.begin();it != text.end();++it)
    {
        cout << *it << endl;
    }

    return 0;
}