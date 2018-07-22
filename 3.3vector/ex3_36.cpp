#include <iostream>
#include <vector>
#include <iterator>

using std::cout;
using std::endl;
using std::vector;
using std::end;
using std::begin;

//need int[] size
// bool compare_int(int const ia1[],int const ia2[])
// {
//     if(sizeof(ia1) == sizeof(ia2))
//     {
        
//         cout << sizeof(ia1) << sizeof(ia2) << endl;
//         for(int i = 0;i != sizeof(ia1)/sizeof(int);i++)
//         {
//             cout << ia1[i] << " " << ia2[i] << endl;
//             if(ia1[i] != ia2[i])
//             {
//                 return false;
//             }
//         }
//         return true;
//     }else
//     {
//         return false;
//     }
// }

bool compare_int(int *ia1_begin,int *ia1_end,int *ia2_begin,int *ia2_end)
{
    cout << ia1_end - ia1_begin << " " << ia2_end - ia2_begin <<endl;
    if((ia1_end - ia1_begin) == (ia2_end - ia2_begin))
    {
        for(int *i = ia1_begin,*j = ia2_begin;i != ia1_end,j != ia2_end;++i,++j)
        {
            if(*i != *j)
            {
                return false;
            }
        }
        return true;
    }else
    {
        return false;
    }
}

int main()
{

    int ia1[10] = {1,2,3};
    int ia2[9] = {1,2,3};

    if(compare_int(begin(ia1),end(ia1),begin(ia2),end(ia2)))
    {
        cout << "equal" << endl;
    }else
    {
        cout << "not equal" << endl;

    }

    vector<int> iv1{1,2,3,4};
    vector<int> iv2{1,2,3};
    if(iv1 == iv2)
    {
        cout << "equal" << endl;
    }else
    {
        cout << "not equal" << endl;
    }

    return 0;
}