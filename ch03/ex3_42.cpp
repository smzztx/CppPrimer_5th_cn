#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> iv(3,2);
    int ia[3];

    for(int i = 0;i < 3;++i) ia[i] = iv[i];

    for(auto i : ia)
        cout << i << " ";
    cout << endl;

    return 0;
}