## [练习10.1](ex01.cpp)

> 头文件 algorithm 中定义了一个名为 count 的函数，它类似 find， 接受一对迭代器和一个值作为参数。 count 返回给定值在序列中出现的次数。编写程序，读取 int 序列存入vector中，打印有多少个元素的值等于给定值。



## [练习10.2](ex02.cpp)

> 重做上一题，但读取 string 序列存入 list 中。



## [练习10.3](ex03.cpp)

> 用 accumulate求一个 vector<int> 中元素之和。



## [练习10.4](ex04.cpp)

> 假定 v 是一个vector<double>，那么调用 accumulate(v.cbegin(),v.cend(),0) 有何错误（如果存在的话）？

结果默认是int类型的，精度会降低。


## 练习10.5

> 在本节对名册（roster）调用equal 的例子中，如果两个名册中保存的都是C风格字符串而不是string，会发生什么？

equal会比较指针地址，而不是字符串值，比较的结果与string类型的不一致。

## [练习10.6](ex06.cpp)

> 编写程序，使用 fill_n 将一个序列中的 int 值都设置为 0。


## 练习10.7

> 下面程序是否有错误？如果有，请改正：
```cpp
(a) vector<int> vec; list<int> lst; int i;
	while (cin >> i)
		lst.push_back(i);
	copy(lst.cbegin(), lst.cend(), vec.begin());
(b) vector<int> vec;
	vec.reserve(10);
	fill_n(vec.begin(), 10, 0);
```

（a）10.4.1中说明back_inserter(vec)
```cpp
copy(lst.cbegin(), lst.cend(), back_inserter(vec));
```
（b）没有报错，但是与预期不符，vec并没有10个元素，且每个元素都为0。可以加上
```cpp
vec.resize(10);
```
或改为：
```cpp
fill_n(back_inserter(v), 10, 0);
```

## 练习10.8

> 本节提到过，标准库算法不会改变它们所操作的容器的大小。为什么使用 back_inserter 不会使这一断言失效？

back_inserter是<iterator>的一部分，而不是<algorithm>。  

## [练习10.9](ex09.cpp)

> 实现你自己的 elimDups。分别在读取输入后、调用 unique后以及调用erase后打印vector的内容。



## 练习10.10

> 你认为算法不改变容器大小的原因是什么？

改变容器大小可能会导致迭代器失效，而且每种容器都有自己的特性，改变容器大小可能需要使用不同的方法，不改变容器大小使得算法更加通用。  

## [练习10.11](ex11.cpp)

> 编写程序，使用 stable_sort 和 isShorter 将传递给你的 elimDups 版本的 vector 排序。打印 vector的内容，验证你的程序的正确性。



## [练习10.12](ex12.cpp)

> 编写名为 compareIsbn 的函数，比较两个 Sales_data 对象的isbn() 成员。使用这个函数排序一个保存 Sales_data 对象的 vector。



## [练习10.13](ex13.cpp)

> 标准库定义了名为 partition 的算法，它接受一个谓词，对容器内容进行划分，使得谓词为true 的值会排在容器的前半部分，而使得谓词为 false 的值会排在后半部分。算法返回一个迭代器，指向最后一个使谓词为 true 的元素之后的位置。编写函数，接受一个 string，返回一个 bool 值，指出 string 是否有5个或更多字符。使用此函数划分 words。打印出长度大于等于5的元素。



## [练习10.14](ex14.cpp)

> 编写一个 lambda ，接受两个int，返回它们的和。



## [练习10.15](ex15.cpp)

> 编写一个 lambda ，捕获它所在函数的 int，并接受一个 int参数。lambda 应该返回捕获的 int 和 int 参数的和。



## [练习10.16](ex16.cpp)

> 使用 lambda 编写你自己版本的 biggies。



## [练习10.17](ex17.cpp)

> 重写10.3.1节练习10.12的程序，在对sort的调用中使用 lambda 来代替函数 compareIsbn。



## [练习10.18](ex18.cpp)

> 重写 biggies，用 partition 代替 find_if。我们在10.3.1节练习10.13中介绍了 partition 算法。



## [练习10.19](ex19.cpp)

> 用 stable_partition 重写前一题的程序，与 stable_sort 类似，在划分后的序列中维持原有元素的顺序。



## [练习10.20](ex20.cpp)

> 标准库定义了一个名为 count_if 的算法。类似 find_if，此函数接受一对迭代器，表示一个输入范围，还接受一个谓词，会对输入范围中每个元素执行。count_if返回一个计数值，表示谓词有多少次为真。使用count_if重写我们程序中统计有多少单词长度超过6的部分。



## [练习10.21](ex21.cpp)

> 编写一个 lambda，捕获一个局部 int 变量，并递减变量值，直至它变为0。一旦变量变为0，再调用lambda应该不再递减变量。lambda应该返回一个bool值，指出捕获的变量是否为0。



## [练习10.22](ex22.cpp)

> 重写统计长度小于等于6的单词数量的程序，使用函数代替 lambda。


## 练习10.23

> bind 接受几个参数？

假设要绑定的函数有n个参数，绑定取n + 1个参数。另外一个是函数本身的绑定。

## [练习10.24](ex24.cpp)

> 给定一个string，使用 bind 和 check_size 在一个 int 的vector 中查找第一个大于string长度的值。



## [练习10.25](ex25.cpp)

> 在10.3.2节的练习中，编写了一个使用partition 的biggies版本。使用 check_size 和 bind 重写此函数。



## 练习10.26

> 解释三种迭代器的不同之处。

back_inserter创建一个使用push_back的迭代器；  
front_inserter创建一个使用push_front的迭代器；  
inserter创建一个使用insert的迭代器。此函数接受第二个参数，这个参数必须是一个指向给定容器的迭代器。元素将被插入到给定迭代器所表示的元素之前。  

## [练习10.27](ex27.cpp)

> 除了 unique 之外，标准库还定义了名为 unique_copy 的函数，它接受第三个迭代器，表示拷贝不重复元素的目的位置。编写一个程序，使用 unique_copy将一个vector中不重复的元素拷贝到一个初始化为空的list中。



## [练习10.28](ex28.cpp)

> 一个vector 中保存 1 到 9，将其拷贝到三个其他容器中。分别使用inserter、back_inserter 和 front_inserter 将元素添加到三个容器中。对每种 inserter，估计输出序列是怎样的，运行程序验证你的估计是否正确。



## [练习10.29](ex29.cpp)

> 编写程序，使用流迭代器读取一个文本文件，存入一个vector中的string里。



## [练习10.30](ex30.cpp)

> 使用流迭代器、sort 和 copy 从标准输入读取一个整数序列，将其排序，并将结果写到标准输出。


## [练习10.31](ex31.cpp)

> 修改前一题的程序，使其只打印不重复的元素。你的程序应该使用 unique_copy。



## [练习10.32](ex32.cpp)

> 重写1.6节中的书店程序，使用一个vector保存交易记录，使用不同算法完成处理。使用 sort 和10.3.1节中的 compareIsbn 函数来排序交易记录，然后使用 find 和 accumulate 求和。

之前谓词处写了sale_item != *beg，找了半天才发现这是检查3个成员变量的。


## [练习10.33](ex33.cpp)

> 编写程序，接受三个参数：一个输入文件和两个输出文件的文件名。输入文件保存的应该是整数。使用 istream_iterator 读取输入文件。使用 ostream_iterator 将奇数写入第一个输入文件，每个值后面都跟一个空格。将偶数写入第二个输出文件，每个值都独占一行。



## [练习10.34](ex34.cpp)

> 使用 reverse_iterator 逆序打印一个vector。



## [练习10.35](ex35.cpp)

> 使用普通迭代器逆序打印一个vector。



## [练习10.36](ex36.cpp)

> 使用 find 在一个 int 的list 中查找最后一个值为0的元素。



## [练习10.37](ex37.cpp)

> 给定一个包含10 个元素的vector，将位置3到7之间的元素按逆序拷贝到一个list中。



## 练习10.38

> 列出5个迭代器类别，以及每类迭代器所支持的操作。

输入迭代器：==、!=、++、*、->；  
输出迭代器：++、*；  
前项迭代器：==、!=、++、*、->；  
双向迭代器：==、!=、++、--、*、->；  
随机访问迭代器：==、!=、++、--、*、->、<、<=、>、>=、+、+=、-、-=、-、iter[n]、*(iter[n])。  

## 练习10.39

> list 上的迭代器属于哪类？vector呢？

list术语双向迭代器；vector属于随机访问迭代器。  

## 练习10.40

> 你认为 copy 要求哪类迭代器？reverse 和 unique 呢？

copy：前两个参数为输入迭代器，第三个参数为输出迭代器；  
reverse：双向迭代器；  
unique：前向迭代器。  

## 练习10.41

> 仅根据算法和参数的名字，描述下面每个标准库算法执行什么操作：
```cpp
replace(beg, end, old_val, new_val);
replace_if(beg, end, pred, new_val);
replace_copy(beg, end, dest, old_val, new_val);
replace_copy_if(beg, end, dest, pred, new_val);
```

```cpp
replace(beg, end, old_val, new_val); // 在beg与end之间，如果是old_val则替换为new_val
replace_if(beg, end, pred, new_val); // 在beg与end之间，如果满足谓词条件则替换为new_val
replace_copy(beg, end, dest, old_val, new_val); // 在beg与end之间，如果是old_val则替换为new_val，不改变原始值，将结果复制到dest
replace_copy_if(beg, end, dest, pred, new_val); // 在beg与end之间，如果满足谓词条件则替换为new_val，不改变原始值，将结果复制到dest
```

## [练习10.42](ex42.cpp)
> 使用 list 代替 vector 重新实现10.2.3节中的去除重复单词的程序。

