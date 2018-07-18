#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> iv;
    int i;

    while(cin >> i)
    {
        iv.push_back(i);
        // cout << i << endl;
    }

    return 0;
}