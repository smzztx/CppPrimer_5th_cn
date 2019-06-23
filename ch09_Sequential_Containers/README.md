## 练习9.1

> 对于下面的程序任务，vector、deque和list哪种容器最为适合？解释你的选择的理由。如果没有哪一种容器优于其他容器，也请解释理由。
* (a) 读取固定数量的单词，将它们按字典序插入到容器中。我们将在下一章中看到，关联容器更适合这个问题。
* (b) 读取未知数量的单词，总是将单词插入到末尾。删除操作在头部进行。
* (c) 从一个文件读取未知数量的整数。将这些数排序，然后将它们打印到标准输出。

（a）list，需要在中间插入数据，list最好；
（b）qedue，需要在头部和尾部插入或删除元素，选qedue；
（c）vector，没有特别的需求选vector。
  
## 练习9.2

> 定义一个list对象，其元素类型是int的deque。

```cpp
list<deque<int>> l;
```
  
## 练习9.3

> 构成迭代器范围的迭代器有何限制？

两个迭代器begin和end满足如下条件：
它们指向同一个容器中的元素，或者是容器中的最后一个元素之后的位置，且我们可以通过反复递增begin来到达end。换句话说，end不在begin之前。
  
## [练习9.4](ex04.cpp)

> 编写函数，接受一对指向vector<int>的迭代器和一个int值。在两个迭代器指定的范围中查找给定的值，返回一个布尔值来指出是否找到。


  
## [练习9.5](ex05.cpp)

> 重写上一题的函数，返回一个迭代器指向找到的元素。注意，程序必须处理未找到给定值的情况。


  
## 练习9.6

> 下面的程序有何错误？你应该如何修改它？
```cpp
list<int> lst1;
list<int>::iterator iter1 = lst1.begin(),
					iter2 = lst1.end();
while (iter1 < iter2) /* ... */
```

```cpp
while(iter1 != iter2)
```
  
## 练习9.7

> 为了索引int 的 vector中的元素，应该使用什么类型？

```cpp
vector<int>::size_type
```
  
## 练习9.8

> 为了读取string 的list 中的元素，应该使用什么类型？如果写入list，又应该使用什么类型？

```cpp
list<string>::const_iterator		//read
list<string>::iterator				//write
```
  
## 练习9.9

> begin 和 cbegin 两个函数有什么不同？

begin返回容器的iterator类型，当我们需要写访问时使用；  
cbegin返回容器的const_iterator类型，当我们不需要写访问时使用。  
  
## 练习9.10

> 下面4个对象分别是什么类型？
```cpp
vector<int> v1;
const vector<int> v2;
auto it1 = v1.begin(), it2 = v2.begin();
auto it3 = v1.cbegin(), it4 = v2.cbegin();
```

```cpp
it1：vector<int>::iterator，it2：vector<int>::const_iterator；
it3：vector<int>::const_iterator，it4：vector<int>::const_iterator。
```
  
## 练习9.11

> 对6种创建和初始化 vector 对象的方法，每一种都给出一个实例。解释每个vector包含什么值。

```cpp
vector<int> v1;  //v1为空
vector<int> v2 = v1;  //v2为空
vector<int> v3(v2);  //v3为空
vector<int> v4(10);  //10个0
vector<int> v5(10,1);  //10个1
vector<int> v6{1,2,3};  //1 2 3
vector<int> v7 = {1,2,3};  //1 2 3
vector<int> v8(v7.begin(),v7.end());  //1 2 3
```
  
## 练习9.12

> 对于接受一个容器创建其拷贝的构造函数，和接受两个迭代器创建拷贝的构造函数，解释它们的不同。

两个容器的类型及其元素必须匹配；
传递迭代器参数来拷贝一个范围时，就不要求容器类型相同了，只要能将要拷贝的元素转换。
  
## [练习9.13](ex13.cpp)

> 如何从一个list<int>初始化一个vector<double>？从一个vector<int>又该如何创建？编写代码验证你的答案。


  
## [练习9.14](ex14.cpp)

> 编写程序，将一个list中的char * 指针元素赋值给一个vector中的string。


  
## [练习9.15](ex15.cpp)

> 编写程序，判定两个vector<int>是否相等。


  
## [练习9.16](ex16.cpp)

> 重写上一题的程序，比较一个list<int>中的元素和一个vector<int>中的元素。


  
## 练习9.17

> 假定c1 和 c2 是两个容器，下面的比较操作有何限制？
```cpp
	if (c1 < c2)
```

c1和c2不能是无序容器，且容器类型要相同，最后，元素类型要支持运算符。
  
## [练习9.18](ex18.cpp)

> 编写程序，从标准输入读取string序列，存入一个deque中。编写一个循环，用迭代器打印deque中的元素。


  
## [练习9.19](ex19.cpp)

> 重写上一题的程序，用list替代deque。列出程序要做出哪些改变。

只需讲deque替换为list。

  
## [练习9.20](ex20.cpp)

> 编写程序，从一个list<int>拷贝元素到两个deque中。值为偶数的所有元素都拷贝到一个deque中，而奇数值元素都拷贝到另一个deque中。


  
## 练习9.21

> 如果我们将第308页中使用 insert 返回值将元素添加到list中的循环程序改写为将元素插入到vector中，分析循环将如何工作。

还是一样的操作，实现的是在vector的一个特定位置反复插入元素。具体请查看本节使用insert返回值的内容。
  
## 练习9.22

> 假定iv是一个int的vector，下面的程序存在什么错误？你将如何修改？
```cpp
vector<int>::iterator iter = iv.begin(),
					  mid = iv.begin() + iv.size() / 2;
while (iter != mid)
	if (*iter == some_val)
		iv.insert(iter, 2 * some_val);
```

问题：
1.循环不会停止；
2.迭代器在插入操作后会变化。
```cpp
// cause the reallocation will lead the iterators and references
// after the insertion point to invalid. Thus, we need to call reserver at first.

#include <iostream>
#include <vector>

void double_and_insert(std::vector<int>& v, int some_val)
{
    auto mid = [&]{ return v.begin() + v.size() / 2; };
    for (auto curr = v.begin(); curr != mid(); ++curr)
        if (*curr == some_val)
            ++(curr = v.insert(curr, 2 * some_val));
}

int main()
{
    std::vector<int> v{ 1, 9, 1, 9, 9, 9, 1, 1 };
    double_and_insert(v, 1);

    for (auto i : v) 
        std::cout << i << std::endl;
}
```
  
## 练习9.23

> 在本节第一个程序中，若 c.size() 为1，则val、val2、val3和val4的值会是什么？

同一个元素的拷贝。
  
## [练习9.24](ex24.cpp)

> 编写程序，分别使用 at、下标运算符、front 和 begin 提取一个vector中的第一个元素。在一个空vector上测试你的程序。

```cpp
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// vector<int> v1 = {1};
	vector<int> v1;

	cout << v1.at(0) << endl;		//terminate called after throwing an instance of 'std::out_of_range'   what():  vector::_M_range_check
	cout << v1[0] << endl;			//Segmentation fault (core dumped)
	cout << v1.front() << endl;		//Segmentation fault (core dumped)
	cout << *v1.begin() << endl;	//Segmentation fault (core dumped)

	return 0;
}
```
  
## 练习9.25

> 对于第312页中删除一个范围内的元素的程序，如果 elem1 与 elem2 相等会发生什么？如果 elem2 是尾后迭代器，或者 elem1 和 elem2 皆为尾后迭代器，又会发生什么？

如果elem1与elem2相等，则一个元素都不会删除；  
如果elem2是尾后迭代器，则会从elem1元素删除到最后一个元素；  
如果elem1与elem2都是尾后迭代器，则一个元素都不会删除。  
  
## [练习9.26](ex26.cpp)

> 使用下面代码定义的ia，将ia 拷贝到一个vector和一个list中。是用单迭代器版本的erase从list中删除奇数元素，从vector中删除偶数元素。
```cpp
int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };
```


  
## [练习9.27](ex27.cpp)

> 编写程序，查找并删除forward_list<int>中的奇数元素。

  
## [练习9.28](ex28.cpp)

> 编写函数，接受一个forward_list<string>和两个string共三个参数。函数应在链表中查找第一个string，并将第二个string插入到紧接着第一个string之后的位置。若第一个string未在链表中，则将第二个string插入到链表末尾。


  
## 练习9.29

> 假定vec包含25个元素，那么vec.resize(100)会做什么？如果接下来调用vec.resize(10)会做什么？

会添加75个新元素，并对新元素进行初始化；  
后面90个元素会被丢弃。  
  
## 练习9.30

> 接受单个参数的resize版本对元素类型有什么限制（如果有的话）？

如果元素类型的类类型，则元素类型必须提供一个默认构造函数。
  
## 练习9.31

> 第316页中删除偶数值元素并复制奇数值元素的程序不能用于list或forward_list。为什么？修改程序，使之也能用于这些类型。

[list](ex31_list.cpp)

  
[forward_list](ex31_forward_list.cpp)

  
## 练习9.32

> 在第316页的程序中，向下面语句这样调用insert是否合法？如果不合法，为什么？
```cpp
iter = vi.insert(iter, *iter++);
```

不合法，insert中的参数运行顺序是未定义的，我们不知道iter运行的是iter+1的状态还是未+1的状态。
  
## [练习9.33](ex33.cpp)

> 在本节最后一个例子中，如果不将insert的结果赋予begin，将会发生什么？编写程序，去掉此赋值语句，验证你的答案。


插入操作：如果存储空间被重新分配，则迭代器全部失效；如果没有重新分配，插入位置之后的迭代器全部失效。
运行结果为：
```sh
$ ./ex33 *** Error in `./ex33': munmap_chunk(): invalid pointer: 0x0000000002118040 ***
Aborted (core dumped)
```
  
## [练习9.34](ex34.cpp)

> 假定vi是一个保存int的容器，其中有偶数值也有奇数值，分析下面循环的行为，然后编写程序验证你的分析是否正确。
```cpp
iter = vi.begin();
while (iter != vi.end())
	if (*iter % 2)
		iter = vi.insert(iter, *iter);
	++iter;
```

会无限循环，当碰到第一个奇数时，iter从inert()中得到插入元素的迭代器，++iter后，迭代器指向的还是之前碰到的那个奇数，下次循环中还是检查这个奇数，程序陷入无限循环。  
在测试代码中，如果取消打印行的注释，会一直打印1。  
  
## 练习9.35

> 解释一个vector的capacity和size有何区别。

容器的size是指它已经保存的元素的数目；而capacity则是在不分配新的内存空间的前提下最多可以保存多少元素。  
  
## 练习9.36

> 一个容器的capacity可能小于它的size吗？

不可能。
  
## 练习9.37

> 为什么list或array没有capacity成员函数？

list所占的空间不是连续的；array是固定size的。
  
## [练习9.38](ex38.cpp)

> 编写程序，探究在你的标准实现中，vector是如何增长的。


  
## 练习9.39

> 解释下面程序片段做了什么：
```cpp
vector<string> svec;
svec.reserve(1024);
string word;
while (cin >> word)
	svec.push_back(word);
svec.resize(svec.size() + svec.size() / 2);
```

为svec预留1024的空间，将输入添加到svec中，将svec的size增加当前size的一半。  
  
## 练习9.40

> 如果上一题的程序读入了256个词，在resize之后容器的capacity可能是多少？如果读入了512个、1000个、或1048个呢？

读入了256词、512词时，size增加到384、768，capacity不变；  
读入1000词或1048词后，size增加到1500、1572，capacity至少增大到可以容纳当前size。  
  
## [练习9.41](ex41.cpp)

> 编写程序，从一个vector<char>初始化一个string。


  
## 练习9.42

> 假定你希望每次读取一个字符存入一个string中，而且知道最少需要读取100个字符，应该如何提高程序的性能？

```cpp
string s;
s.reserve(100);
```
  
## [练习9.43](ex43.cpp)

> 编写一个函数，接受三个string参数是s、oldVal 和newVal。使用迭代器及insert和erase函数将s中所有oldVal替换为newVal。测试你的程序，用它替换通用的简写形式，如，将"tho"替换为"though",将"thru"替换为"through"。

在gcc上编译失败。

  
## [练习9.44](ex44.cpp)

> 重写上一题的函数，这次使用一个下标和replace。


  
## [练习9.45](ex45.cpp)

> 编写一个函数，接受一个表示名字的string参数和两个分别表示前缀（如"Mr."或"Mrs."）和后缀（如"Jr."或"III"）的字符串。使用迭代器及insert和append函数将前缀和后缀添加到给定的名字中，将生成的新string返回。


  
## [练习9.46](ex46.cpp)

> 重写上一题的函数，这次使用位置和长度来管理string，并只使用insert。


  
## [练习9.47](ex47.cpp)

> 编写程序，首先查找string"ab2c3d7R4E6"中每个数字字符，然后查找其中每个字母字符。编写两个版本的程序，第一个要使用find_first_of，第二个要使用find_first_not_of。


  
## 练习9.48

> 假定name和numbers的定义如325页所示，numbers.find(name)返回什么？

string::npos
  
## [练习9.49](ex49.cpp)
> 如果一个字母延伸到中线之上，如d 或 f，则称其有上出头部分（ascender）。如果一个字母延伸到中线之下，如p或g，则称其有下出头部分（descender）。编写程序，读入一个单词文件，输出最长的既不包含上出头部分，也不包含下出头部分的单词。


  
## [练习9.50](ex50.cpp)

> 编写程序处理一个vector<string>，其元素都表示整型值。计算vector中所有元素之和。修改程序，使之计算表示浮点值的string之和。


  
## [练习9.51](ex51.cpp)

> 设计一个类，它有三个unsigned成员，分别表示年、月和日。为其编写构造函数，接受一个表示日期的string参数。你的构造函数应该能处理不同的数据格式，如January 1,1900、1/1/1990、Jan 1 1900 等。


  
## [练习9.52](ex52.cpp)

> 使用stack处理括号化的表达式。当你看到一个左括号，将其记录下来。当你在一个左括号之后看到一个右括号，从stack中pop对象，直至遇到左括号，将左括号也一起弹出栈。然后将一个值（括号内的运算结果）push到栈中，表示一个括号化的（子）表达式已经处理完毕，被其运算结果所替代。

看了半天没看懂，还以为要写个计算器，贴上大神代码：  
