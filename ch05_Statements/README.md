# ch05 Statements
## 5.1
最简单的语句是空语句，空语句只有一个单独的分号：  
;//null statement  
如果在程序的某个地方，语法上需要一条语句但逻辑上不需要，此时应该使用空语句。  

## 5.2
复合语句是指用花括号括起来的语句和声明的序列，复合语句也被称作块。  
如果在程序的某个地方，语法上需要一条语句，但是逻辑上需要多条语句，则应使用复合语句。  

## 5.3
```cpp
#include <iostream>
int main()
{
    int sum = 0, val = 1;
    while (val <= 10)
        sum += val, ++val;
    std::cout << "Sum of 1 to 10 inclusive is " << sum << std::endl;
 
    return 0;
}
```
可读性降低了

## 5.4
（a）std::string::iterator iter = s.begin();  
    while (iter != s.end()) { /* . . . */ }  
（b）bool status;  
while ((status = find(word))) {/* ... */}  
if (!status) {/* ... */}  

## 5.5
```cpp
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;

int main()
{
    vector<string> scores = {"F", "D", "C", "B", "A", "A++"};

    int grade{0};
    while (cin >> grade) {
        string lettergrade;
        if (grade < 60)
            lettergrade = scores[0];
        else {
            lettergrade = scores[(grade - 50) / 10];
            if (grade != 100) {
                if (grade % 10 > 7)
                    lettergrade += "+";
                else if (grade % 10 < 3)
                    lettergrade += "-";
            }
        }

        cout << lettergrade << endl;
    }

    return 0;
}
```

## 5.6
```cpp
#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using std::cin;

int main()
{
    vector<string> scores = {"F", "D", "C", "B", "A", "A++"};

    int grade{0};
    while (cin >> grade) {
        string lettergrade = grade < 60 ? scores[0] : scores[(grade - 50) / 10];
        lettergrade +=
            (grade == 100 || grade < 60)
                ? ""
                : (grade % 10 > 7) ? "+" : (grade % 10 < 3) ? "-" : "";
        cout << lettergrade << endl;
    }

    return 0;
}
```

## 5.7
（a）if (ival1 != ival2) ival1 = ival2
    else ival1 = ival2 = 0;
（b）if (ival < minval)
    {
        minval = ival;
        occurs = 1;
    }
（c）int val;
    if (ival = get_value())
        cout << "ival = " << ival << endl;
    if (!ival)
        cout << "ival = 0\n";
（d）if (ival == 0)
       ival = get_value();
       
## 5.8
当一个if语句嵌套在另一个if语句内部时，很可能if分支会多于else分支。这时候我们怎么知道某个给定的else是和哪个if匹配呢。这个问题通常称作悬垂else。就C++而言，它规定else与离它最近的尚未匹配的if匹配的if匹配，从而消除了程序的二义性。

## 5.9
```cpp
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	char c;
	int aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;

	while(cin >> c)
	{
		if (c == 'a')
            ++aCnt;
        else if (c == 'e')
            ++eCnt;
        else if (c == 'i')
            ++iCnt;
        else if (c == 'o')
            ++oCnt;
        else if (c == 'u')
            ++uCnt;
	}
	cout << "Number of vowel a: \t" << aCnt << '\n' << "Number of vowel e: \t"
         << eCnt << '\n' << "Number of vowel i: \t" << iCnt << '\n'
         << "Number of vowel o: \t" << oCnt << '\n' << "Number of vowel u: \t"
         << uCnt << endl;
	return 0;
}
```

## 5.10
```cpp
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0;
    char ch;
    while (cin >> ch) 
        switch (ch) {
            case 'a':
            case 'A':
                ++aCnt;
                break;
            case 'e':
            case 'E':
                ++eCnt;
                break;
            case 'i':
            case 'I':
                ++iCnt;
                break;
            case 'o':
            case 'O':
                ++oCnt;
                break;
            case 'u':
            case 'U':
                ++uCnt;
                break;
        }

    cout << "Number of vowel a(A): \t" << aCnt << '\n'
         << "Number of vowel e(E): \t" << eCnt << '\n'
         << "Number of vowel i(I): \t" << iCnt << '\n'
         << "Number of vowel o(O): \t" << oCnt << '\n'
         << "Number of vowel u(U): \t" << uCnt << endl;

    return 0;
}
```

## 5.11
改为：
```cpp
while (cin >> std::noskipws >> ch) 
```
代码如下：
```cpp
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, tabCnt = 0, newlineCnt = 0;
    char ch;
    while (cin >> std::noskipws >> ch)
        switch (ch) {
            case 'a':
            case 'A':
                ++aCnt;
                break;
            case 'e':
            case 'E':
                ++eCnt;
                break;
            case 'i':
            case 'I':
                ++iCnt;
                break;
            case 'o':
            case 'O':
                ++oCnt;
                break;
            case 'u':
            case 'U':
                ++uCnt;
                break;
            case '\n':
                ++newlineCnt;
                break;
            case '\t':
            case '\v':
                ++tabCnt;
                break;
        }

    cout << "Number of vowel a(A): \t" << aCnt << '\n'
         << "Number of vowel e(E): \t" << eCnt << '\n'
         << "Number of vowel i(I): \t" << iCnt << '\n'
         << "Number of vowel o(O): \t" << oCnt << '\n'
         << "Number of vowel u(U): \t" << uCnt << '\n'
         << "Number of newline: \t" << newlineCnt << '\n'
         << "Number of tab: \t" << tabCnt << endl;

    return 0;
}
```

## 5.12
```cpp
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

int main()
{
    unsigned aCnt = 0, eCnt = 0, iCnt = 0, oCnt = 0, uCnt = 0, tabCnt = 0, newlineCnt = 0, ffCnt = 0, flCnt = 0, fiCnt = 0;
    char ch, prech;
    while (cin >> std::noskipws >> ch)
    {
        switch (ch) {
            case 'a':
            case 'A':
                ++aCnt;
                break;
            case 'e':
            case 'E':
                ++eCnt;
                break;
            case 'i':
                if(prech == 'f') ++fiCnt;
            case 'I':
                ++iCnt;
                break;
            case 'o':
            case 'O':
                ++oCnt;
                break;
            case 'u':
            case 'U':
                ++uCnt;
                break;
            case '\n':
                ++newlineCnt;
                break;
            case '\t':
            case '\v':
                ++tabCnt;
                break;
            case 'f':
                if(prech == 'f') ++ffCnt;
                break;
            case 'l':
                if(prech == 'f') ++flCnt;
                break;
        }
        prech = ch;
    }
    cout << "Number of vowel a(A): \t" << aCnt << '\n'
         << "Number of vowel e(E): \t" << eCnt << '\n'
         << "Number of vowel i(I): \t" << iCnt << '\n'
         << "Number of vowel o(O): \t" << oCnt << '\n'
         << "Number of vowel u(U): \t" << uCnt << '\n'
         << "Number of newline: \t" << newlineCnt << '\n'
         << "Number of tab: \t" << tabCnt << '\n'
         << "Number of fi: \t" << fiCnt << '\n'
         << "Number of ff: \t" << ffCnt << '\n'
         << "Number of fl: \t" << flCnt << endl;

    return 0;
}
```

## 5.13
（a）加上break：  
```cpp
    unsigned aCnt = 0, eCnt = 0, iouCnt = 0;
    char ch = next_text();
    switch (ch) {
        case 'a': aCnt++; break;
        case 'e': eCnt++; break;
        default : iouCnt++; break;
    }
```

（b）case 1处可能被略过，default处又使用到变量ix，所以需要将ix定义到switch case之外：  
```cpp
    unsigned index = some_value();
    int ix;
    switch (index) {
        case 1:
            ix = get_value();
            ivec[ ix ] = index;
            break;
        default:
            ix = static_cast<int>(ivec.size())-1;
            ivec[ ix ] = index;
    }
```

（c）switch case语法不对：  
```cpp
    unsigned evenCnt = 0, oddCnt = 0;
    int digit = get_num() % 10;
    switch (digit) {
        case 1: case 3: case 5: case 7: case 9:
            oddcnt++;
            break;
        case 2: case 4: case 6: case 8: case 0:
            evencnt++;
            break;
    }
```
（d）case标签必须是整形常量表达式：
```cpp
    const unsigned ival=512, jval=1024, kval=4096;
    unsigned bufsize;
    unsigned swt = get_bufCnt();
    switch(swt) {
        case ival:
            bufsize = ival * sizeof(int);
            break;
        case jval:
            bufsize = jval * sizeof(int);
            break;
        case kval:
            bufsize = kval * sizeof(int);
            break;
    }
```

## 5.14
```cpp
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::cin;
using std::endl;

int main()
{
	string s,pres,max_string;
	unsigned int cnt = 1,max_cnt = 1;

	while(cin >> s)
	{
		if(s == pres)
		{
			++cnt;
		}else
		{
			if(cnt > max_cnt)
			{
				max_cnt = cnt;
				max_string = pres;
			}
			cnt = 1;
		}
		pres = s;
	}

	(max_cnt > 1) ? (cout << max_string << ":" << max_cnt << endl) : (cout << "no repeat" << endl);
	return 0;
}
```

## 5.15
（a）ix只能在for循环内部使用，如果要在外部使用，需要定义在for循环外：  
```cpp
int ix;
    for (ix = 0; ix != sz; ++ix)  { /* ... */ }
    if (ix != sz)
    // . . .
```

（b）没有初始化语句：  
```cpp
int ix;
    for (; ix != sz; ++ix) { /* ... */ }
```

（c）如果sz的初始值为0，则不进入循环；如果sz的初始值不为0，则需要循环体内需要有语句退出循环，否则会无休止地执行下去。  

## 5.16
```cpp
// while idiomatic
int i;
while ( cin >> i )
    // ...
 
// same as for
for (int i = 0; cin >> i;)
    // ...
 
// for idiomatic
for (int i = 0; i != size; ++i)
    // ...
 
// same as while
int i = 0;
while (i != size)
{
    // ...
    ++i;
}
```
我更趋向于while，因为只需要判断条件，更加简洁。

## 5.17
```cpp
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

bool function(vector<int> v1,vector<int> v2)
{
	for(decltype(v1.size()) i = 0,sz1 = v1.size(),sz2 = v2.size();i != sz1 && i != sz2;++i)
	{
		if(v1[i] != v2[i])
		{
			cout << "false" << endl;
			return false;
		}
	}
	cout << "true" << endl;
	return true;
}

int main()
{
	vector<int> v1{0,1,2,3,4,5,6,7,8,9};
	vector<int> v2{0,1,2,3};

	function(v1,v2);

	return 0;
}

```

## 5.18
（a）加上花括号：
```cpp
do { // added bracket.
        int v1, v2;
        cout << "Please enter two numbers to sum:" ;
        if (cin >> v1 >> v2)
            cout << "Sum is: " << v1 + v2 << endl;
    }while (cin);
```

（b）condition使用的变量必须定义在循环体外：
```cpp
int ival;
    do {
        // . . .
    } while (ival = get_response());
```

（c）condition使用的变量必须定义在循环体外：
```cpp
int ival;
    do {
        ival = get_response();
    } while (ival);
```

## 5.19
```cpp
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	do
	{
		string s1,s2;
		cin >> s1 >> s2;
		(s1.size() < s2.size()) ? (cout << s1 << endl) : (cout << s2 << endl);
	}while(cin);

	return 0;
}
```

## 5.20
```cpp
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	string repeat_s,pre_s,s;
	while(cin >> s)
	{
		if(s == pre_s)
		{
			repeat_s = s;
			cout << repeat_s << endl;
			break;
		}
		pre_s = s;
	}
	if(repeat_s.empty())
	{
		cout << "no repeat" << endl;
	}

	return 0;
}
```

## 5.21
```cpp
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
	string repeat_s,pre_s,s;
	while(cin >> s)
	{
		if(!isupper(s[0])) continue;
		if(s == pre_s)
		{
			repeat_s = s;
			cout << repeat_s << endl;
			break;
		}
		pre_s = s;
	}
	if(repeat_s.empty())
	{
		cout << "no repeat" << endl;
	}

	return 0;
}
```

## 5.22
```cpp
do
｛
 int sz = get_size();
｝while(sz <= 0);
```

## 5.23
```cpp
#include <iostream>

int main()
{
	int i1,i2;
	std::cin >> i1 >> i2;
	std::cout << i1/i2 << std::endl;

	return 0; 
}
```
运行结果：

```sh
$ ./ex23 
1 0
Floating point exception (core dumped)
```

## 5.24
```cpp
#include <iostream>
#include <stdexcept>

int main()
{
	int i1,i2;
	std::cin >> i1 >> i2;
	if(i2 == 0)
	{
		throw std::runtime_error("divisor can't be 0");
	}
	std::cout << i1/i2 << std::endl;

	return 0; 
}
```
运行结果：

```sh
$ ./ex24 
1 0
terminate called after throwing an instance of 'std::runtime_error'
  what():  divisor can't be 0
Aborted (core dumped)
```

## 5.25
```cpp
#include <iostream>
#include <stdexcept>

int main()
{
	int i1,i2;
	while(std::cin >> i1 >> i2)
	{
		try
		{
			if(i2 == 0)
			{
				throw std::runtime_error("divisor can't be 0");
			}
			std::cout << i1/i2 << std::endl;
		}catch(std::runtime_error err)
		{
			std::cout << err.what()
					  << "\ntry again? enter y or n" << std::endl;
			char c;
			std::cin >> c;
			if(!std::cin || c == 'n') break;
		}
	}
	

	return 0; 
}
```
运行结果：
```sh
$ ./ex25 
1 0
divisor can't be 0
try again? enter y or n
y
1 0
divisor can't be 0
try again? enter y or n
n
```