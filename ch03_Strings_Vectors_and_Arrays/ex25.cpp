#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<unsigned> score(11,0);
    unsigned int grade;
    auto it = score.begin();
    while(cin >> grade)
    {
        ++(*(it + grade/10));
        // cout << grade/10 << endl;
    }
    for(auto e : score)
    {
        cout << e <<" ";
    }
    cout << endl;
    return 0;
}
//input:
//42 65 95 100 39 67 95 76 88 76 83 92 76 93
//output:
// 0 0 0 1 1 0 2 3 2 4 1