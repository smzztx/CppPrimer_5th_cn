#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> i_v,sum1_v,sum2_v;
    int i;
    while(cin >> i)
    {
        i_v.push_back(i);
    }
    
    for(decltype(i_v.size()) index = 0;index < i_v.size()-1;index++)
    {
        sum1_v.push_back(i_v[index] + i_v[index + 1]);
    }
    for(auto c : sum1_v)
    {
        cout << c <<" ";
    }
    cout << endl;

    for(decltype(i_v.size()) index = 0;index < i_v.size()/2 + 1;index++)
    {
        sum2_v.push_back(i_v[index] + i_v[i_v.size() - index - 1]);
    }
    for(auto c : sum2_v)
    {
        cout << c <<" ";
    }
    cout << endl;
    return 0;
}