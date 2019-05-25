## 练习3.1

> 使用恰当的using 声明重做 1.4.1节和2.6.2节的练习。

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
  
## 练习3.2

> 编写一段程序从标准输入中一次读入一行，然后修改该程序使其一次读入一个词。

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
  
## 练习3.3 

> 请说明string类的输入运算符和getline函数分别是如何处理空白字符的。

输入运算符碰到空格、回车和制表符，忽略前面空白；getline碰到回车，不忽略空白。  
  
## 练习3.4

> 编写一段程序读取两个字符串，比较其是否相等并输出结果。如果不相等，输出比较大的那个字符串。改写上述程序，比较输入的两个字符串是否等长，如果不等长，输出长度较大的那个字符串。

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
  
## 练习3.5

> 编写一段程序从标准输入中读入多个字符串并将他们连接起来，输出连接成的大字符串。然后修改上述程序，用空格把输入的多个字符串分割开来。

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
  
## 练习3.6

> 编写一段程序，使用范围for语句将字符串内所有字符用X代替。

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
  
## 练习3.7

> 就上一题完成的程序而言，如果将循环控制的变量设置为char将发生什么？先估计一下结果，然后实际编程进行验证。

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
  
## 练习3.8

> 分别用while循环和传统for循环重写第一题的程序，你觉得哪种形式更好呢？为什么？

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
  
## 练习3.9

> 下面的程序有何作用？它合法吗？如果不合法？为什么？
```cpp
string s;
cout << s[0] << endl;
```

合法，定义后就占用一个字节，包含'\0'。  
  
## 练习3.10

> 编写一段程序，读入一个包含标点符号的字符串，将标点符号去除后输出字符串剩余的部分。

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
  
## 练习3.11

> 下面的范围for语句合法吗？如果合法，c的类型是什么？
```cpp
const string s = "Keep out!";
for(auto &c : s){ /* ... */ }
```

合法，对const char的引用，但是不能改变c。  
  
## 3.12
## 练习3.12

> 下列vector对象的定义有不正确的吗？如果有，请指出来。对于正确的，描述其执行结果；对于不正确的，说明其错误的原因。
```cpp
vector<vector<int>> ivec;
vector<string> svec = ivec;
vector<string> svec(10, "null");
```

（a）正确，创建了元素为vector的vector对象；  
（b）错误，vector元素类型不一致；  
（c）正确，创建了一个包含10个元素为“null”的vector对象。  
  
## 练习3.13

> 下列的vector对象各包含多少个元素？这些元素的值分别是多少？
```cpp
vector<int> v1;
vector<int> v2(10);
vector<int> v3(10, 42);
vector<int> v4{ 10 };
vector<int> v5{ 10, 42 };
vector<string> v6{ 10 };
vector<string> v7{ 10, "hi" };
```

（a）包含0个元素；（b）包含10个元素，值都为0；  
（c）包含10个元素，值都为42；（d）包含1个元素，值为10；  
（e）包含2个元素，值为10，42；（f）包含10个元素，空字符串；（g）包含10个元素，值都为“hi”。  
  
## 练习3.14

> 编写一段程序，用cin读入一组整数并把它们存入一个vector对象。

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
  
## 练习3.15

> 改写上题程序，不过这次读入的是字符串。

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
  
## 练习3.16

> 编写一段程序，把练习3.13中vector对象的容量和具体内容输出出来

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
  
## 练习3.17

> 从cin读入一组词并把它们存入一个vector对象，然后设法把所有词都改为大写形式。输出改变后的结果，每个词占一行。

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
  
## 练习3.18

> 下面的程序合法吗？如果不合法，你准备如何修改？
```cpp
vector<int> ivec;
ivec[0] = 42;
```

不合法，第2行改为：ivec.push_back(10)。  
  
## 练习3.19

> 如果想定义一个含有10个元素的vector对象，所有元素的值都是42，请例举三种不同的实现方法，哪种方式更好呢？

```cpp
vector<int> ivec1(10,42);	//最好，大量重复值，简洁
vector<int> ivec2{ 42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
vector<int> ivec3 = { 42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
vector<int> ivec4(ivec1);
vector<int> ivec4 = ivec1;
```
  
## 练习3.20

> 读入一组整数并把他们存入一个vector对象，将每对相邻整数的和输出出来。改写你的程序，这次要求先输出第一个和最后一个元素的和，接着输入第二个和倒数第二个元素的和，以此类推。

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
  
## 练习3.21

> 请使用迭代器重做3.3.3节的第一个练习。

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
  
## 练习3.22

> 修改之前那个输出text第一段的程序，首先把text的第一段全部改成大写形式，然后输出它。

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
  
## 练习3.23

> 编写一段程序，创建一个含有10个整数的vector对象，然后使用迭代器将所有元素的值都变成原来的两倍。输出vector对象的内容，检验程序是否正确。

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
  
## 练习3.24

> 请使用迭代器重做3.3.3节的最后一个练习。

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
  
## 练习3.25

> 3.3.3节划分分数段的程序是使用下标运算符实现的，请利用迭代器改写该程序实现完全相同的功能。

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
        //cout << e <<" ";
    }
    cout << endl;
    return 0;
}
```
  
## 练习3.26

> 在100页的二分搜索程序中，为什么用的是 mid = beg + (end - beg) / 2, 而非 mid = (beg + end) / 2 ; ?

迭代器相加不成立，指针加指针无意义。

## 练习3.27

> 假设txt_size 是一个无参函数，它的返回值是int。请回答下列哪个定义是非法的，为什么？
```cpp
unsigned buf_size = 1024;
(a) int ia[buf_size];
(b) int ia[4 * 7 - 14];
(c) int ia[txt_size()];
(d) char st[11] = "fundamental";
```

（a）非法；（b）合法；  
（c）非法；（d）非法。  
  
## 练习3.28

> 下列数组中元素的值是什么？
```cpp
string sa[10];
int ia[10];
int main() {
    string sa2[10];
    int ia2[10];
}
```

sa：空字符串；  
ia：0；  
sa2：空字符串；  
ia2：不确定值。  
  
## 练习3.29

> 相比于vector 来说，数组有哪些缺点，请例举一些。

数组的缺点：数组的大小是确定不变的，不能随意向数组中增加元素，丧失了vectoer的灵活性，没有API，风险更大。  
  
## 练习3.30

> 指出下面代码中的索引错误。
```cpp
constexpr size_t array_size = 10;
int ia[array_size];
for (size_t ix = 1; ix <= array_size; ++ix)
    ia[ix] = ix;
```

数组越界ix < array_size。  
  
## 练习3.31

> 编写一段程序，定义一个含有10个int的数组，令每个元素的值就是其下标值。

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
  
## 练习3.32

> 将上一题刚刚创建的数组拷贝给另一数组。利用vector重写程序，实现类似的功能。

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
  
## 练习3.33

> 对于104页的程序来说，如果不初始化scores将会发生什么？

数组的值为不确定的。  
  
## 练习3.34

> 假定p1 和 p2 都指向同一个数组中的元素，则下面程序的功能是什么？什么情况下该程序是非法的？
```cpp
p1 += p2 - p1;
```

将p1移动（p2-p1）个位置；p1或p2是非法的，该程序就是非法的。  
  
## 练习3.35

> 编写一段程序，利用指针将数组中的元素置为0。

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
  
## 练习3.36

> 编写一段程序，比较两个数组是否相等。再写一段程序，比较两个vector对象是否相等。

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
  
## 练习3.37

> 下面的程序是何含义，程序的输出结果是什么？
```cpp
const char ca[] = { 'h', 'e', 'l', 'l', 'o' };
const char *cp = ca;
while (*cp) {
    cout << *cp << endl;
    ++cp;
}
```

没有'\0'，循环可能不会停止，将会打印出垃圾信息（存在风险）。  
  
## 练习3.38

> 在本节中我们提到，将两个指针相加不但是非法的，而且也没有什么意义。请问为什么两个指针相加没有意义？

指针相加实际为地址相加，没有什么意义。  
  
## 练习3.39

> 编写一段程序，比较两个string对象。再编写一段程序，比较两个C风格字符串的内容。

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
  
## 练习3.40

> 编写一段程序，定义两个字符数组并用字符串字面值初始化它们；接着再定义一个字符数组存放前面两个数组连接后的结果。使用strcpy和strcat把前两个数组的内容拷贝到第三个数组当中。

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
  
## 练习3.41

> 编写一段程序，用整型数组初始化一个vector对象。

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
  
## 练习3.42

> 编写一段程序，将含有整数元素的vector对象拷贝给一个整型数组。

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
  
## 练习3.43

> 编写3个不同版本的程序，令其均能输出ia的元素。版本1使用范围for语句管理迭代过程；版本2和版本3都使用普通for语句，其中版本2要求使用下标运算符，版本3要求使用指针。此外，在所有3个版本的程序中都要直接写出数据类型，而不能使用类型别名、auto关键字和decltype关键字。

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
  
## 练习3.44

> 改写上一个练习中的程序，使用类型别名来代替循环控制变量的类型。

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
  
## 练习3.45

> 再一次改写程序，这次使用auto关键字。

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