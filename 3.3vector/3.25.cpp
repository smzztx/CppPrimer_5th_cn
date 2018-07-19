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
        (*(it + grade/10))++;
        cout << grade/10 << endl;
    }
    for(auto e : score)
    {
        cout << e <<" ";
    }
    cout << endl;
    return 0;
}