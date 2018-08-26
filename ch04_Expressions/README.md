#ch04 Expressions
## 4.1
105

## 4.2
（a）*(vec.begin())；  
（b）(*(vec.begin())) + 1。  

## 4.3
可以接受，效率是C++最大的优势。我们要做的是避免类似代码的产生。

## 4.4
(((12/3)*4)+(5*15))+((24%4)/2)  
91  

## 4.5
（a）-86 （b）-18  
（c）0   （d）-2  

## 4.6
i % 2 == 0 ? "even" : "odd"  

## 4.7
short svalue = 32767; ++svalue; // -32768  
unsigned uivalue = 0; --uivalue;  // 4294967295  
unsigned short usvalue = 65535; ++usvalue;  // 0  

## 4.8
逻辑与、逻辑或运算符都是先求左侧运算对象的值再求右侧运算对象的值，当且仅当左侧运算对象无法确定表达式的结果时才会计算右侧运算对象的值。  
逻辑与：当且仅当左侧运算对象为真时才对右侧运算对象求值。  
逻辑或：当且仅当左侧运算对象为假时才对右侧运算对象求值。  
相等性运算符：求值顺序不明确。  

## 4.9
当指针cp不为空时，才判断解引用cp的值。  
我们知道，cp不为空，&&左侧为true；*cp为'H'，右侧也为真，所以if语句为真。  

## 4.10
while(cin >> i && i != 42)

## 4.11
a >=b && b > c && c>d

## 4.12
根据4.12运算符优先级表我们得到<的优先级大于!=，所以j < k得到bool值，bool值再与i比较是否不等。等价于：i != (j < k)

## 4.13
（a）i=3,d=3 （b）i=3,d=3.5  

## 4.14
非法操作；  
if判断为真。  

## 4.15
pi改为*p  

## 4.16
（a）if((p = getPtr() != 0)；（b）if(i == 1024)。  

## 4.17
前置递增运算符：将运算对象加1，然后将改变后的对象作为求值结果；  
后置递增运算符：将运算对象加1，但是求值结果是运算对象改变之前那个值的副本。  

## 4.18
循环第一次解引用第二个地址；循环到最后一次时，将会解引用vector最后一个地址的后一个位置（等同于v.end()）

## 4.19
（a）指针ptr不为空时，判断指针所指的值是不是不为0；  
（b）判断ival和ival+1是不是不为0；  
（c）vec[ival] <= vec[ival+1]。  

## 4.20
（a）合法，求iter的解引用，并把iter指向下一个位置；  
（b）不合法，*iter为字符串，不能++；  
（c）不合法，iter没有empty()成员；  
（d）合法，iter所指向的值是否为空；  
（e）不合法，字符串不能++；  
（f）合法，先判断是否为空，再iter++。  

## 4.21
[ex21.cpp](ex21.cpp)

## 4.22
一个if语句更容易理解，逻辑更清晰。  
[ex22.cpp](ex22.cpp)

## 4.23
+的优先级大于 == 和 ?: 所以会先执行s + (s[s.size() - 1],与程序本意不符，且字符串与字符无法比较。  
改为：string pl = s + (s[s.size() - 1] == 's' ? "" : "s") ;  

## 4.24
finalgrade = (grade > 90) ? "high pass" : (grade < 60) ? "fail" : "pass";  
 if grade > 90,finalgrade = "high pass" ? "fail" : "pass";  
 finalgrade = "fail";  
grade <= 90时，结果符合预期。  

## 4.25
0100 0000 '@'  

## 4.26
int最小为16位，可能会出现位数不够的情况。

## 4.27
011  
111  
（a）011，3  
（b）111，7  
（c）true  
（d）true  

## 4.28
[ex28.cpp](ex28.cpp)

## 4.29
40/4=10，数组所占的字节数/数组类型int所占的字节数，就是数组的个数；  
4/4=1，指针所占的字节数/int所占的字节数。  

## 4.30
（a）(sizeof x) + y；  
（b）sizeof(p->mem[i])；  
（c）(sizeof a) < b；  
（d）sizeof(f())。  

## 4.31
后置版本需要将未修改的值保存下来，以便返回，如果不需要未修改的值就使用前置版本。使用后置版本无需改动。

## 4.32
ptr和ix的功能都是为了遍历数组，功能一样，实现的过程不一样，ptr是指针方式实现，ix是索引方式实现。

## 4.33
(someValue ? ++x, ++y : --x), --y

## 4.34
（a）float变换为bool；  
（b）ival变换为float，结果变换为double；  
（c）cval变换为int，结果变换为double。  

## 4.35
（a）'a'->int，int->char；  
（b）ival->double,ui->double,double->float；  
（c）ui->float，float->double；  
（d）ival->float,float->double,double->char。  

## 4.36
i *= static_cast<int>(d)

## 4.37
（a）pv = static_cast<void*>(const_cast<string*>(ps));  
（b）i = static_cast<int>(*pc);  
（c）pv = static_cast<void*>(&d);  
（d）pc = reinterpret_cast<void*>(pv);  

## 4.38
将(j/i)转换为double，并赋值给slope。