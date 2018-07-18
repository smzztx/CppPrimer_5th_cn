#include <string>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

// void print_vector(vector<int> v)
// {
//     cout << v.size() << endl;
//     for(auto c : v)
//     {
//         cout << c;
//     }
//     cout << endl;
// }

int main()
{
    vector<int> v1;
    // print_vector(v1);
    cout << v1.size() << endl;
    for(auto c : v1)
    {
        cout << c <<' ';
    }
    cout << endl;

    vector<int> v2(10);
    cout << v2.size() << endl;
    for(auto c : v2)
    {
        cout << c <<' ';
    }
    cout << endl;

    vector<int> v3(10,42);
    cout << v3.size() << endl;
    for(auto c : v3)
    {
        cout << c <<' ';
    }
    cout << endl;

    vector<int> v4{10};
    cout << v4.size() << endl;
    for(auto c : v4)
    {
        cout << c <<' ';
    }
    cout << endl;

    vector<int> v5{10,42};
    cout << v5.size() << endl;
    for(auto c : v5)
    {
        cout << c <<' ';
    }
    cout << endl;

    vector<string> v6{10};
    cout << v6.size() << endl;
    for(auto c : v6)
    {
        cout << c <<' ';
    }
    cout << endl;

    vector<string> v7{10,"hi"};
    cout << v7.size() << endl;
    for(auto c : v7)
    {
        cout << c <<' ';
    }
    cout << endl;

    return 0;
}