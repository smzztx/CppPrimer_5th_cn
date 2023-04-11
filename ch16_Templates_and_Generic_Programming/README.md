## 练习16.1

> 给出实例化的定义。

实例化：编译器处理过程，用实际的模板实参来生成模板的一个特殊实例，其中参数被替换为对应的实参。当函数模板被调用时，会自动根据传递给它的实参来实例化。而使用类模板时，则需要我们提供显式模板实参。  
  
## [练习16.2](ex02.cpp)

> 编写并测试你自己版本的 compare 函数。


  
## [练习16.3](ex03.cpp)

> 对两个 Sales_data 对象调用你的 compare 函数，观察编译器在实例化过程中如何处理错误。

```sh
error: no match for ‘operator<’ (operand types are ‘const Sales_data’ and ‘const Sales_data’)
```
  
## [练习16.4](ex04.cpp)

> 编写行为类似标准库 find 算法的模版。函数需要两个模版类型参数，一个表示函数的迭代器参数，另一个表示值的类型。使用你的函数在一个 vector<int> 和一个list<string>中查找给定值。


  
## [练习16.5](ex05.cpp)

> 为6.2.4节中的print函数编写模版版本，它接受一个数组的引用，能处理任意大小、任意元素类型的数组。


  
## [练习16.6](ex06.cpp)

> 你认为接受一个数组实参的标准库函数 begin 和 end 是如何工作的？定义你自己版本的 begin 和 end。


  
## [练习16.7](ex07.cpp)

> 编写一个 constexpr 模版，返回给定数组的大小。


  
## 练习16.8

> 在第97页的“关键概念”中，我们注意到，C++程序员喜欢使用 != 而不喜欢 < 。解释这个习惯的原因。

因为!=更符合“编写类型无关的代码”的原则。
  
## 练习16.9

> 什么是函数模版，什么是类模版？

函数模板，模板定义，可从它实例化出特定函数。函数模板的定义以关键字template开始，后跟尖括号对<和>，其内为一个用逗号分隔的一个或多个模板参数列表，随后是函数的定义。  
类模板，模板定义，可从它实例化出特定的类。类模板的定义以template开始，后跟尖括号<和>，其内为一个用逗号分隔的一个或多个模板参数的列表，随后是类的定义。与函数模板不同之处是，编译器不能为类模板推断模板参数类型。  
  
## 练习16.10

> 当一个类模版被实例化时，会发生什么？

编译器使用显式模板参数列表来实例化特定的类。
  
## [练习16.11](ex11.cpp)

> 下面 List 的定义是错误的。应如何修改它？
```cpp
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
	List<elemType>();
	List<elemType>(const List<elemType> &);
	List<elemType>& operator=(const List<elemType> &);
	~List();
	void insert(ListItem *ptr, elemType value);
private:
	ListItem *front, *end;
};
```


  
## [练习16.12](ex12)

> 编写你自己版本的 Blob 和 BlobPtr 模版，包含书中未定义的多个const成员。


  
## 练习16.13

> 解释你为 BlobPtr 的相等和关系运算符选择哪种类型的友好关系？

一对一的友好关系，相同类型实例化的BlobPtr可以相互比较。
  
## [练习16.14](ex14)

> 编写 Screen 类模版，用非类型参数定义 Screen 的高和宽。


  
## [练习16.15](ex15)

> 为你的 Screen 模版实现输入和输出运算符。Screen 类需要哪些友元（如果需要的话）来令输入和输出运算符正确工作？解释每个友元声明（如果有的话）为什么是必要的。


  
## [练习16.16](ex16)

> 将 StrVec 类重写为模版，命名为 Vec。


  
## 练习16.17

> 声明为 typename 的类型参数和声明为 class 的类型参数有什么不同（如果有的话）？什么时候必须使用typename？

没有不同，在声明模板时可以typename和class可以互换。  
当我们希望通知编译器一个名字表示类型时，必须使用关键字typename，而不能使用class。  
  
## 练习16.18

> 解释下面每个函数模版声明并指出它们是否非法。更正你发现的每个错误。
```cpp
(a) template <typename T, U, typename V> void f1(T, U, V);
(b) template <typename T> T f2(int &T);
(c) inline template <typename T> T foo(T, unsigned int *);
(d) template <typename T> f4(T, T);
(e) typedef char Ctype;
	template <typename Ctype> Ctype f5(Ctype a);
```

（a）非法，U之前要加typename；  
（b）非法，模板内不能重用参数名T；  
（c）非法，inline在temple<>之后；  
（d）非法，必须声明返回类型；  
（e）合法，在模版参数Ctype的作用域之内会隐藏外层作用域声明的相同名字。  
  
## [练习16.19](ex19.cpp)

> 编写函数，接受一个容器的引用，打印容器中的元素。使用容器的 size_type 和 size成员来控制打印元素的循环。


  
## [练习16.20](ex20.cpp)

> 重写上一题的函数，使用begin 和 end 返回的迭代器来控制循环。


  
## [练习16.21](ex21)

> 编写你自己的 DebugDelete 版本。


  
## [练习16.22](ex22)

> 修改12.3节中你的 TextQuery 程序，令 shared_ptr 成员使用 DebugDelete 作为它们的删除器。


  
## 练习16.23

> 预测在你的查询主程序中何时会执行调用运算符。如果你的预测和实际不符，确认你理解了原因。

在销毁shared_ptr时，调用DebugDelete()。  
  
## [练习16.24](ex24)

> 为你的 Blob 模版添加一个构造函数，它接受两个迭代器。


  
## 练习16.25

> 解释下面这些声明的含义。
```cpp
extern template class vector<string>;
template class vector<Sales_data>;
```

实例化声明模板类vector<string>，不在本文件中实例化；  
实例化定义模板类vector<Sales_data>，在本文件中实例化。  
  
## 练习16.26

> 假设 NoDefault 是一个没有默认构造函数的类，我们可以显式实例化 vector<NoDefualt>吗？如果不可以，解释为什么。

不能，如果没有默认构造函数，我们又没有提供参数，该类无法初始化，vector无法实例化。  
  
## 练习16.27

> 对下面每条带标签的语句，解释发生了什么样的实例化（如果有的话）。如果一个模版被实例化，解释为什么;如果未实例化，解释为什么没有。
```cpp
template <typename T> class Stack {	};
void f1(Stack<char>); 		//(a)
class Exercise {
	Stack<double> &rds;		//(b)
	Stack<int> si;			//(c)
};
int main() {
	Stack<char> *sc;		//(d)
	f1(*sc);				//(e)
	int iObj = sizeof(Stack<string>);	//(f)
}
```
  
（a）没有实例化，因为只是声明；  
（b）没有实例化，引用和指针不需要实例化；  
（c）实例化，在类中定义；  
（d）没有实例化，引用和指针不需要实例化；  
（e）实例化，调用时需要实例化；  
（f）实例化，sizeof 需要知道 Stack<string> 的定义才能给出一个 Stack<string> 对象的大小，会实例化。  
  
## [练习16.28](ex28)
> 编写你自己版本的 shared_ptr 和 unique_ptr。


  
## [练习16.29](ex29)

> 修改你的 Blob 类，用你自己的 shared_ptr 代替标准库中的版本。


  
## [练习16.30](ex30)

> 重新运行你的一些程序，验证你的 shared_ptr 类和修改后的 Blob 类。（注意：实现 weak_ptr 类型超出了本书范围，因此你不能将BlobPtr类与你修改后的Blob一起使用。）

程序详见16.29，可以成功运行。  
  
## 练习16.31

> 如果我们将 DebugDelete 与 unique_ptr 一起使用，解释编译器将删除器处理为内联形式的可能方式。

unique_ptr将DebugDelete设置为默认删除器，编译时将执行DebugDelete。  
  
## 练习16.32

> 在模版实参推断过程中发生了什么？

在模板实参推断过程中，编译器使用函数调用中的实参类型来寻找模板实参，用这些模板实参生成的函数版本与给定的函数调用最为匹配。  
  
## 练习16.33

> 指出在模版实参推断过程中允许对函数实参进行的两种类型转换。

const转换：可以将一个非const对象的引用（或指针）传递给一个const的引用（或指针）形参。  
数组或函数指针转换：如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换。一个数组实参可以转换为一个指向其首元素的指针。类似的，一个函数实参可以转换为一个该函数类型的指针。  
  
## 练习16.34

> 对下面的代码解释每个调用是否合法。如果合法，T 的类型是什么？如果不合法，为什么？
```cpp
template <class T> int compare(const T&, const T&);
(a) compare("hi", "world");
(b) compare("bye", "dad");
```

（a）不合法，const char ()[3]和const char ()[6]；  
（b）合法，const char ()[4]和const char ()[4]。  
  
## 练习16.35

> 下面调用中哪些是错误的（如果有的话）？如果调用合法，T 的类型是什么？如果调用不合法，问题何在？
```cpp
template <typename T> T calc(T, int);
tempalte <typename T> T fcn(T, T);
double d; float f; char c;
(a) calc(c, 'c'); 
(b) calc(d, f);
(c) fcn(c, 'c');
(d) fcn(d, f);
```

注意此处为单引号：  
（a）合法，T为char；  
（b）合法，T为double；  
（c）合法，T为char；  
（d）不合法，无法确定T的类型为double还是float。  
  
## 练习16.36

> 进行下面的调用会发生什么：
```cpp
template <typename T> f1(T, T);
template <typename T1, typename T2) f2(T1, T2);
int i = 0, j = 42, *p1 = &i, *p2 = &j;
const int *cp1 = &i, *cp2 = &j;
(a) f1(p1, p2);
(b) f2(p1, p2);
(c) f1(cp1, cp2);
(d) f2(cp1, cp2);
(e) f1(p1, cp1);
(f) f2(p1, cp1);
```

题目中没有函数没有返回类型，我们认为是void，typename T2后")"替换为">"：  
（a）f1(int*, int*)；  
（b）f2(int*, int*)；  
（c）f1(const int*, const int*)；  
（d）f2(const int*, const int*)；  
（e）出错；  
（f）f2(int*, const int*)。  
  
## 练习16.37

> 标准库 max 函数有两个参数，它返回实参中的较大者。此函数有一个模版类型参数。你能在调用 max 时传递给它一个 int 和一个 double 吗？如果可以，如何做？如果不可以，为什么？

可以，使用指定模板实参。  
```cpp
int a = 1;
double b = 2.0;
max<double>(a, b);
```
  
## 练习16.38

> 当我们调用 make_shared 时，必须提供一个显示模版实参。解释为什么需要显式模版实参以及它是如果使用的。

规定返回类型，推断需要分配多大空间。  
  
## 练习16.39

> 对16.1.1节 中的原始版本的 compare 函数，使用一个显式模版实参，使得可以向函数传递两个字符串字面量。

```cpp
compare<std::string>("a", "bb");
```
  
## 练习16.40

> 下面的函数是否合法？如果不合法，为什么？如果合法，对可以传递的实参类型有什么限制（如果有的话）？返回类型是什么？
```cpp
template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0)
{
	//处理序列
	return *beg;
}
```

合法，传递的实参必须支持+0操作，返回类型由+操作的返回类型决定。  
  
## [练习16.41](ex41.cpp)

> 编写一个新的 sum 版本，它返回类型保证足够大，足以容纳加法结果。

下述代码应该有问题。

  
## 练习16.42

> 对下面每个调用，确定 T 和 val 的类型：
```cpp
template <typename T> void g(T&& val);
int i = 0; const int ci = i;
(a) g(i);
(b) g(ci);
(c) g(i * ci);
```

（a）T为int&，val为int& && -> int&；  
（b）T为const int&，val为const int& && -> const int&；  
（c）T为int，val为int&&。  
  
## 练习16.43

> 使用上一题定义的函数，如果我们调用g(i = ci),g 的模版参数将是什么？

int&  
  
## 练习16.44

> 使用与第一题中相同的三个调用，如果 g 的函数参数声明为 T（而不是T&&），确定T的类型。如果g的函数参数是 const T&呢？

T：  
（a）int；  
（b）int；  
（c）int。  
  
const T&：  
（a）int；  
（b）int；  
（c）int。  
  
## 练习16.45

> 如果下面的模版，如果我们对一个像42这样的字面常量调用g，解释会发生什么？如果我们对一个int 类型的变量调用g 呢？
```cpp
template <typename T> void g(T&& val) { vector<T> v; }
```

42，T为int，val为int&&，vector<int> v；  
int，T为int&，val为int& && -> int&，vector<int&> v，无法对int&进行内存分配，会报错。  
  
## 练习16.46

> 解释下面的循环，它来自13.5节中的 StrVec::reallocate:
```cpp
for (size_t i = 0; i != size(); ++i)
	alloc.construct(dest++, std::move(*elem++));
```

从C++11开始，std::allocator::construct的第二个参数为 Args&&... args，*elem++会返回一个左值，需要我们自行转换为右值。  
  
## [练习16.47](ex47.cpp)

> 编写你自己版本的翻转函数，通过调用接受左值和右值引用参数的函数来测试它。


  
## [练习16.48](ex48.cpp)

> 编写你自己版本的 debug_rep 函数。


  
## 练习16.49

> 解释下面每个调用会发生什么：
```cpp
template <typename T> void f(T);
tempalte <typename T> void f(const T*);
tempalte <typename T> void g(T);
tempalte <typename T> void g(T*);
int i = 42, *p = &i;
const int ci = 0, *p2 = &ci;
g(42); g(p); g(ci); g(p2);
f(42); f(p); f(ci); f(p2);
```

g(42) g(T)；g(p) g(T*)；g(ci) g(int) g(T)；g(p2)->g(const int*) g(T*)；  
f(42) f(T)；f(p) f(T)；f(ci) f(T)；f(p2) f(const T*)。  
  
## [练习16.50](ex50.cpp)

> 定义上一个练习中的函数，令它们打印一条身份信息。运行该练习中的代码。如果函数调用的行为与你预期不符，确定你理解了原因。


```sh
$ ./ex50 
template <typename T> void g(T t)
template <typename T> void g(T *t)
template <typename T> void g(T t)
template <typename T> void g(T *t)
template <typename T> void f(T t)
template <typename T> void f(T t)
template <typename T> void f(T t)
template <typename T> void f(const T *t)
```
  
## 练习16.51

> 调用本节中的每个 foo，确定 sizeof...(Args) 和 sizeof...(rest)分别返回什么。

foo(i, s, 42, d);
3 3
  
foo(s, 42, "hi");
2 2
  
foo(d, s);
1 1
  
foo("hi");
0 0
  
## [练习16.52](ex52.cpp)

> 编写一个程序验证上一题的答案。


  
## [练习16.53](ex53.cpp)

> 编写你自己版本的 print 函数，并打印一个、两个及五个实参来测试它，要打印的每个实参都应有不同的类型。 


  
## 练习16.54

> 如果我们对一个没 << 运算符的类型调用 print，会发生什么？

会编译报错。
  
## 练习16.55

> 如果我们的可变参数版本 print 的定义之后声明非可变参数版本，解释可变参数的版本会如何执行。

编译报错：error: no matching function for call to ‘print(std::ostream&)’。  
  
## [练习16.56](ex56.cpp)

> 编写并测试可变参数版本的 errorMsg。


  
## 练习16.57

> 比较你的可变参数版本的 errorMsg 和6.2.6节中的 error_msg函数。两种方法的优点和缺点各是什么？

error_msg函数中使用initializer_list，initializer_list只能接受相同类型（或它们的类型可以转换为同一个公共类型）的可变数目实参的函数；而errorMsg函数可以接受不同类型的可变数目实参，更加灵活。  
  
## [练习16.58](ex58)

> 为你的 StrVec 类及你为16.1.2节练习中编写的 Vec 类添加 emplace_back 函数。


  
## 练习16.59

> 假定 s 是一个 string，解释调用 svec.emplace_back(s)会发生什么。

会在 construst 函数中转发扩展包。  
  
## 练习16.60

> 解释 make_shared 是如何工作的。

make_shared 是一个可变模版函数，它将参数包转发然后构造一个对象，再然后一个指向该对象的智能指针。  
  
## [练习16.61](ex61.cpp)

> 定义你自己版本的 make_shared。


  
## [练习16.62](ex62)

> 定义你自己版本的 hash<Sales_data>, 并定义一个 Sales_data 对象的 unorder_multise。将多条交易记录保存到容器中，并打印其内容。


  
## [练习16.63](ex63_ex64.cpp)

> 定义一个函数模版，统计一个给定值在一个vecor中出现的次数。测试你的函数，分别传递给它一个double的vector，一个int的vector以及一个string的vector。


  
## [练习16.64](ex63_ex64.cpp)

> 为上一题的模版编写特例化版本来处理vector<const char*>。编写程序使用这个特例化版本。

详见16.63。
  
## [练习16.65](ex65.cpp)

> 在16.3节中我们定义了两个重载的 debug_rep 版本，一个接受 const char* 参数，另一个接受 char * 参数。将这两个函数重写为特例化版本。


  
## 练习16.66

> 重载debug_rep 函数与特例化它相比，有何优点和缺点？

会改变函数匹配顺序，几个函数都提供同样好的匹配的情况下，编译器会选择非模板版本。  
  
## 练习16.67

> 定义特例化版本会影响 debug_rep 的函数匹配吗？如果不影响，为什么？

不会改变，特例化模板函数不会重载函数，不会影响函数匹配顺序。  

