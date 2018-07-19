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

    int ia2[10];
    for(size_t i = 0;i<10;++i) ia2[i] = ia[i];

    for(auto i : ia) cout << i << " ";
    cout << endl;

    vector<int> iv1;
    for(decltype(iv1.size()) index = 0;index < 10;++index) iv1.push_back(index);

    vector<int> iv2(iv1);
    for(auto e : iv2) cout << e << " ";
    cout << endl;

    return 0;
}