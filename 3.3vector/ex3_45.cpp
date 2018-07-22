#include <iostream>
#include <cstddef>
#include <iterator>

using std::cout;
using std::endl;
using std::begin;
using std::end;

int main()
{
    int ia[3][4] = {
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11}
    };

    for(const auto &i:ia)
        for(int j:i)
            cout << j << " ";
    cout << endl;

    for(size_t i = 0;i < 3;++i)
        for(size_t j = 0;j < 4;++j)
            cout << ia[i][j] << " ";
    cout << endl;

    for(auto *i = begin(ia);i != end(ia);i++)
        for(int *j = begin(*i);j != end(*i);j++)
            cout << *j << " ";
    cout << endl;

    return 0;
}