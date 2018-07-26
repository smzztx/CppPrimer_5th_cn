#include <iostream>
#include <vector>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::begin;
using std::end;

int main()
{
    int ia[] = {1,2,3};
    vector<int> iv(begin(ia),end(ia));

    for(auto e : iv)
        cout << e << " ";
    cout << endl;

    return 0;
}