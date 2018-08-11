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
    
    for(auto it = i_v.begin();it+1 != i_v.end();++it)
    {
        sum1_v.push_back(*it + *(it+1));
    }
    for(auto c : sum1_v)
    {
        cout << c <<" ";
    }
    cout << endl;

    for(auto it_begin = i_v.begin(),it_end = i_v.end()-1;it_begin <= it_end;++it_begin,--it_end)
    {
        sum2_v.push_back(*it_begin + *it_end);
    }
    for(auto c : sum2_v)
    {
        cout << c <<" ";
    }
    cout << endl;
    return 0;
}