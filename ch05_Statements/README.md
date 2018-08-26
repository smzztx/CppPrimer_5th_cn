# ch05 Statements
## 5.1
最简单的语句是空语句，空语句只有一个单独的分号：  
;//null statement  
如果在程序的某个地方，语法上需要一条语句但逻辑上不需要，此时应该使用空语句。  

## 5.2
复合语句是指用花括号括起来的语句和声明的序列，复合语句也被称作块。  
如果在程序的某个地方，语法上需要一条语句，但是逻辑上需要多条语句，则应使用复合语句。  

## [5.3](ex03.cpp)
可读性降低了

## 5.4
（a）
```cpp
std::string::iterator iter = s.begin();
while (iter != s.end()) { /* . . . */ }
```
（b）
```cpp
bool status;
while ((status = find(word))) {/* ... */}
if (!status) {/* ... */}
```

## [5.5](ex05.cpp)

## [5.6](ex06.cpp)

## 5.7
（a）
```cpp
if (ival1 != ival2) ival1 = ival2
else ival1 = ival2 = 0;
```
（b）
```cpp
if (ival < minval)
{
    minval = ival;
    occurs = 1;
}
```
（c）
```cpp
int val;
if (ival = get_value())
    cout << "ival = " << ival << endl;
if (!ival)
    cout << "ival = 0\n";
```
（d）
```cpp
if (ival == 0)
   ival = get_value();
```

## 5.8
当一个if语句嵌套在另一个if语句内部时，很可能if分支会多于else分支。这时候我们怎么知道某个给定的else是和哪个if匹配呢。这个问题通常称作悬垂else。就C++而言，它规定else与离它最近的尚未匹配的if匹配的if匹配，从而消除了程序的二义性。

## [5.9](ex09.cpp)

## [5.10](ex10.cpp)

## [5.11](ex11.cpp)
改为：
```cpp
while (cin >> std::noskipws >> ch) 
```

## [5.12](ex12.cpp)

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
[部分测试代码](ex13.cpp)

## [5.14](ex14.cpp)

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

## [5.17](ex17.cpp)

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

## [5.19](ex19.cpp)

## [5.20](ex20.cpp)

## [5.21](ex21.cpp)

## 5.22
```cpp
do
｛
 int sz = get_size();
｝while(sz <= 0);
```

## [5.23](ex23.cpp)
运行结果：

```sh
$ ./ex23 
1 0
Floating point exception (core dumped)
```

## [5.24](ex24.cpp)
运行结果：

```sh
$ ./ex24 
1 0
terminate called after throwing an instance of 'std::runtime_error'
  what():  divisor can't be 0
Aborted (core dumped)
```

## [5.25](ex25.cpp)
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