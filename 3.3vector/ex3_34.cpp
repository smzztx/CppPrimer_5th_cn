#include <cstddef>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    int ia[10];
    for(size_t i = 0;i<10;++i) ia[i] = i;
    for(auto i : ia) cout << i << " ";
    cout << endl;

    for(int i = 0,*pa = ia;i<10;++i)
    {
        *pa = 0;
        ++pa;
    }

    for(auto i : ia) cout << i << " ";
    cout << endl;

    return 0;
}