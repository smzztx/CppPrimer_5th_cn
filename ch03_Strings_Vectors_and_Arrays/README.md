## 3.1
### 3.1.1
```cpp
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	int i = 50 ,sum = 0;

	while(i <= 100)
	{
		sum += i;
		++i;
	}
	cout << sum << endl;

	return 0;
}
```

### 3.1.2
```cpp
#include <iostream>

using std::cout;
using std::endl;

int main()
{
	int i = 10 ,sum = 0;

	while(i >= 0)
	{
		sum += i;
		--i;
	}
	cout << sum << endl;

	return 0;
}
```

### 3.1.3
```cpp
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
    int small = 0, big = 0;
    cout << "please input two integers:";
    cin >> small >> big;

    if (small > big) {
        int tmp = small;
        small = big;
        big = tmp;
    }

    while (small <= big) {
        cout << small << " ";
        ++small;
    }
    cout << endl;

    return 0;
}
```

### 3.1.4
```cpp
#include <iostream>
#include <string>
#include "../ch02/ex2_42.h"

using std::cin;
using std::cout;
using std::endl;
using std::cerr;

int main()
{
    Sales_data data1, data2;

    // code to read into data1 and data2
    double price = 0;  // price per book, used to calculate total revenue

    // read the first transactions: ISBN, number of books sold, price per book 
    cin >> data1.bookNo >> data1.units_sold >> price;
    // calculate total revenue from price and units_sold
    data1.revenue = data1.units_sold * price;

    // read the second transaction
    cin >> data2.bookNo >> data2.units_sold >> price;
    data2.revenue = data2.units_sold * price;

    // code to check whether data1 and data2 have the same ISBN
    //        and if so print the sum of data1 and data2
    if (data1.bookNo == data2.bookNo)
    {
        unsigned totalCnt = data1.units_sold + data2.units_sold;
        double totalRevenue = data1.revenue + data2.revenue;

        // print: ISBN, total sold, total revenue, average price per book
        cout << data1.bookNo << " " << totalCnt
            << " " << totalRevenue << " ";
        if (totalCnt != 0)
            cout << totalRevenue / totalCnt << endl;
        else
            cout << "(no sales)" << endl;

        return 0;  // indicate success
    }
    else
    {  // transactions weren't for the same ISBN
        cerr << "Data must refer to the same ISBN" << endl;
        return -1; // indicate failure
    }
}
```

## 3.2
### 3.2.1
```cpp
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in;
    while(getline(cin,str_in))
    {
        cout << str_in << endl;
    }

    return 0;
}
```

### 3.2.2
```cpp
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in;

    while(cin>>str_in)
    {
        cout << str_in << endl;
    }
    return 0;
}
```

## 3.3
输入运算符碰到空格、回车和制表符，忽略前面空白；getline碰到回车，不忽略空白

## 3.4
### 3.4.1
```cpp
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in1,str_in2;

    cin>>str_in1>>str_in2;
    
    if(str_in1.size() != str_in2.size())
    {
        if(str_in1.size()>str_in2.size())
        {
            cout << str_in1 << endl;
        }else
        {
            cout << str_in2 << endl;
        }
    }

    return 0;
}
```

### 3.4.2
```cpp
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in1,str_in2;

    cin>>str_in1>>str_in2;
    
    if(str_in1.size() != str_in2.size())
    {
        if(str_in1.size()>str_in2.size())
        {
            cout << str_in1 << endl;
        }else
        {
            cout << str_in2 << endl;
        }
    }

    return 0;
}
```

## 3.5
### 3.5.1
```cpp
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in,str_sum;

    while(cin>>str_in)
    {
        str_sum = str_sum + str_in;
    }
    cout << str_sum << endl;
    return 0;
}
```

### 3.5.2
```cpp
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in,str_sum;

    while(cin>>str_in)
    {
        str_sum = str_sum + str_in + " ";
    }
    cout << str_sum << endl;
    return 0;
}
```

## 3.6
```cpp
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string str = "1122aabbcc 33";

    for(auto &c : str)
    {
        c = 'X';
    }
    cout<<str<<endl;

    return 0;
}
```

## 3.7
改为char后，在范围for循环中，改变的str中字符c的副本，因此，str并不会改变。
```cpp
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string str = "1122aabbcc 33";

    for(char c : str)
    {
        c = 'X';
    }
    cout<<str<<endl;

    return 0;
}
```

## 3.8
个人感觉范围for循环更好，更简洁，且声明的变量作用域在范围for循环内，不会对其他程序产生影响。
### 3.8.1
```cpp
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string str = "1122aabbcc 33";

    for(string::size_type index = 0;index < str.size();++index)
    {
        str[index] = 'X';
    }
    cout<<str<<endl;

    return 0;
}
```

### 3.8.2
```cpp
#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
    string str = "1122aabbcc 33";

    string::size_type index = 0;
    while(str[index]!='\0')
    {
        str[index] = 'X';
        index++;
    }
    cout<<str<<endl;

    return 0;
}
```

## 3.9
合法，定义后就占用一个字节，包含'\0'。

## 3.10
```cpp
#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
int main()
{
    std::string str_in,str;
    cin>>str_in;
    for(auto c : str_in)
        if(!ispunct(c))
            str = str + c;
    cout << str << endl;
    return 0;
}
```

## 3.11
合法，对const char的引用，但是不能改变c。

## 3.12
（a）正确，创建了元素为vector的vector对象；
（b）错误，vector元素类型不一致；
（c）正确，创建了一个包含10个元素为“null”的vector对象。

## 3.13
（a）包含0个元素；（b）包含10个元素，值都为0；
（c）包含10个元素，值都为42；（d）包含1个元素，值为10；
（e）包含2个元素，值为10，42；（f）包含10个元素，空字符串；（g）包含10个元素，值都为“hi”。

## 3.14
```cpp
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
```

## 3.15
```cpp
#include <string>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    vector<string> sv;
    string str;

    while(cin >> str)
    {
        sv.push_back(str);
        // cout << str << endl;
    }

    return 0;
}
```

## 3.16
```cpp
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
```

## 3.17
```cpp
#include <string>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    vector<string> str_v;
    string s;
    while(cin >> s)
    {
        str_v.push_back(s);
    }
    
    for(auto &c1 : str_v)
    {
        for(auto &c2 : c1)
        {
            c2 = toupper(c2);
        }
    }

    for(auto c : str_v)
    {
        cout << c <<endl;
    }

    return 0;
}
```

## 3.18
不合法，第2行改为：ivec.push_back(10)。

## 3.19
```cpp
vector<int> ivec1(10,42);	//最好，大量重复值，简洁
vector<int> ivec2{ 42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
vector<int> ivec3 = { 42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
vector<int> ivec4(ivec1);
vector<int> ivec4 = ivec1;
```

## 3.20
```cpp
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
```

## 3.21
```cpp
#include <string>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    vector<int> v1;
    cout << v1.size() << endl;
    for(auto it = v1.begin();it != v1.end();++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    vector<int> v2(10);
    cout << v2.size() << endl;
    for(auto it = v2.begin();it != v2.end();++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    vector<int> v3(10,42);
    cout << v3.size() << endl;
    for(auto it = v3.begin();it != v3.end();++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    vector<int> v4{10};
    cout << v4.size() << endl;
    for(auto it = v4.begin();it != v4.end();++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    vector<int> v5{10,42};
    cout << v5.size() << endl;
    for(auto it = v5.begin();it != v5.end();++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    vector<string> v6{10};
    cout << v6.size() << endl;
    for(auto it = v6.begin();it != v6.end();++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    vector<string> v7{10,"hi"};
    cout << v7.size() << endl;
    for(auto it = v7.begin();it != v7.end();++it)
    {
        cout << *it << ' ';
    }
    cout << endl;

    return 0;
}
```

## 3.22
```cpp
#include <string>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    vector<string> text{"abcd,efg","","AAaa"};
    for(auto it = text.begin();it != text.end() && !it->empty();++it)
    {
        for(auto &c : *it)
            c = toupper(c);
    }
    
    for(auto it = text.begin();it != text.end();++it)
    {
        cout << *it << endl;
    }

    return 0;
}
```

## 3.23
```cpp
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int main()
{
    vector<int> text{0,1,2,3,4,5,6,7,8,9};
    for(auto it = text.begin();it != text.end();++it)
    {
        *it = *it * 2;
    }
    
    for(auto it = text.begin();it != text.end();++it)
    {
        cout << *it << endl;
    }

    return 0;
}
```

## 3.24
```cpp
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
```

## 3.25
```cpp
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
```

## 3.26
迭代器相加不成立，指针加指针无意义。

## 3.27
（a）非法；（b）合法；
（c）非法；（d）非法。

## 3.28
sa：空字符串；
ia：0；
sa2：空字符串；
ia2：不确定值。

## 3.29
数组的缺点：数组的大小是确定不变的，不能随意向数组中增加元素，丧失了vectoer的灵活性，没有API，风险更大。

## 3.30
数组越界ix < array_size。

## 3.31
```cpp
#include <cstddef>
#include <iostream>

using std::cout;
using std::endl;

int main()
{
    int ia[10];
    for(size_t i = 0;i<10;i++) ia[i] = i;

    for(auto i : ia) cout << i << " ";
    cout << endl;

    return 0;
}
```

## 3.32
```cpp
#include <cstddef>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    int ia[10];
    for(size_t i = 0;i<10;++i) ia[i] = i;

    int ia2[10];
    for(size_t i = 0;i<10;++i) ia2[i] = ia[i];

    for(auto i : ia) cout << i << " ";
    cout << endl;

    vector<int> iv1;
    for(decltype(iv1.size()) index = 0;index < 10;++index) iv1.push_back(index);

    vector<int> iv2(iv1);
    for(auto e : iv2) cout << e << " ";
    cout << endl;

    return 0;
}
```

## 3.33
数组的值为不确定的。

## 3.34
将p1移动（p2-p1）个位置；p1或p2是非法的，该程序就是非法的。

## 3.35
```cpp
#include <cstddef>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

int main()
{
    int ia[10];
    for(size_t i = 0;i<10;++i) ia[i] = i;
    for(auto i : ia) cout << i << " ";
    cout << endl;

    for(int i = 0,*pa = ia;i<10;++i)
    {
        *pa = 0;
        ++pa;
    }

    for(auto i : ia) cout << i << " ";
    cout << endl;

    return 0;
}
```

## 3.36
```cpp
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
```

## 3.37
没有'\0'，循环可能不会停止，将会打印出垃圾信息（存在风险）。

## 3.38
指针相加实际为地址相加，没有什么意义。

## 3.39
```cpp
#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::string;


int main()
{
    string s1 = "aabb";
    string s2 = "aabb";

    if(s1 == s2)
    {
        cout << "equal" << endl;
    }else
    {
        cout << "not equal" << endl;
    }

    const char ca1[] = {'a','b','c'};
    const char ca2[] = "abc";

    if(strcmp(ca1,ca2) == 0)
    {
        cout << "equal" <<endl;
    }else
    {
        cout << "not equal" <<endl;
    }

    return 0;
}
```

## 3.40
```cpp
#include <iostream>
#include <string>
#include <cstring>

using std::cout;
using std::endl;
using std::string;

int main()
{
    char ca1[] = "aaa";
    char ca2[] = "abc";
    char ca3[10];

    strcpy(ca3,ca1);
    strcat(ca3,ca2);

    cout << ca3 << endl;

    return 0;
}
```

## 3.41
```cpp
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
```

## 3.42
```cpp
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
```

## 3.43
```cpp
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

    for(const int (&i)[4]:ia)
        for(int j:i)
            cout << j << " ";
    cout << endl;

    for(size_t i = 0;i < 3;++i)
        for(size_t j = 0;j < 4;++j)
            cout << ia[i][j] << " ";
    cout << endl;

    for(int (*i)[4] = begin(ia);i != end(ia);i++)
        for(int *j = begin(*i);j != end(*i);j++)
            cout << *j << " ";
    cout << endl;

    return 0;
}
```

## 3.44
```cpp
#include <iostream>
#include <cstddef>
#include <iterator>

using std::cout;
using std::endl;
using std::begin;
using std::end;

int main()
{
    typedef int int_array[4];
    // using int_array = int[4];
    int ia[3][4] = {
        {0,1,2,3},
        {4,5,6,7},
        {8,9,10,11}
    };

    for(const int_array &i:ia)
        for(int j:i)
            cout << j << " ";
    cout << endl;

    for(size_t i = 0;i < 3;++i)
        for(size_t j = 0;j < 4;++j)
            cout << ia[i][j] << " ";
    cout << endl;

    for(int_array *i = begin(ia);i != end(ia);i++)
        for(int *j = begin(*i);j != end(*i);j++)
            cout << *j << " ";
    cout << endl;

    return 0;
}
```

## 3.45
```cpp
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
```