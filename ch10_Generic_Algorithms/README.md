## 练习10.1

> 头文件 algorithm 中定义了一个名为 count 的函数，它类似 find， 接受一对迭代器和一个值作为参数。 count 返回给定值在序列中出现的次数。编写程序，读取 int 序列存入vector中，打印有多少个元素的值等于给定值。

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,1,1};

	cout << count(v1.cbegin(), v1.cend(), 1) << endl;

	return 0;
}
```

## 练习10.2

> 重做上一题，但读取 string 序列存入 list 中。

```cpp
#include <list>
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	list<string> l1 = {"a", "b", "c", "a", "aa"};

	cout << count(l1.cbegin(), l1.cend(), "a") << endl;

	return 0;
}
```

## 练习10.3

> 用 accumulate求一个 vector<int> 中元素之和。

```cpp
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,1,1};

	cout << accumulate(v1.cbegin(), v1.cend(), 0) << endl;

	return 0;
}
```

## 练习10.4

> 假定 v 是一个vector<double>，那么调用 accumulate(v.cbegin(),v.cend(),0) 有何错误（如果存在的话）？

结果默认是int类型的，精度会降低。
```cpp
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	vector<double> v1 = {1,2,3.1,1,1};

	cout << accumulate(v1.cbegin(), v1.cend(), 0) << endl;

	return 0;
}
```

## 练习10.5

> 在本节对名册（roster）调用equal 的例子中，如果两个名册中保存的都是C风格字符串而不是string，会发生什么？

equal会比较指针地址，而不是字符串值，比较的结果与string类型的不一致。

## 练习10.6

> 编写程序，使用 fill_n 将一个序列中的 int 值都设置为 0。

```cpp
#include <iostream>
#include <vector>
#include <iterator>

using namespace std;

int main()
{
	vector<int> v1(10, 1);
	fill_n(v1.begin(), v1.size(), 0);
	for(const auto i : v1)
		cout << i << " ";
	cout << endl;

	vector<int> v2;
	fill_n(back_inserter(v2), 10, 0);
	for(const auto i : v2)
		cout << i << " ";
	cout << endl;

	return 0;
}
```
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

## 练习10.9

> 实现你自己的 elimDups。分别在读取输入后、调用 unique后以及调用erase后打印vector的内容。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e"};

	for(const auto s : elimDups(vs))
		cout << s << " ";
	cout << endl;

	return 0;
}
```

## 练习10.10

> 你认为算法不改变容器大小的原因是什么？

改变容器大小可能会导致迭代器失效，而且每种容器都有自己的特性，改变容器大小可能需要使用不同的方法，不改变容器大小使得算法更加通用。  

## 练习10.11

> 编写程序，使用 stable_sort 和 isShorter 将传递给你的 elimDups 版本的 vector 排序。打印 vector的内容，验证你的程序的正确性。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa"};

	for(const auto s : elimDups(vs))
		cout << s << " ";
	cout << endl;

	stable_sort(vs.begin(), vs.end(), isShorter);

	for(const auto s : vs)
		cout << s << " ";
	cout << endl;

	return 0;
}
```

## 练习10.12

> 编写名为 compareIsbn 的函数，比较两个 Sales_data 对象的isbn() 成员。使用这个函数排序一个保存 Sales_data 对象的 vector。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../ch07_Classes/Sales_data_ex26.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

bool compareIsbn(const Sales_data &sales_data1, const Sales_data &sales_data2)
{
	return sales_data1.isbn() < sales_data2.isbn();
}

int main()
{
	vector<string> v1;

	ifstream is("../ch08_The_IO_Library/book_sales");
	string buf;

	if(!is)
	{
		cerr << "open error" << endl;
		return -1;
	}

	while(getline(is, buf))
		v1.push_back(buf);

	vector<Sales_data> v2;
	for(const auto &s : v1)
	{
		// cout << s << endl;
		istringstream iss(s);
		v2.push_back(Sales_data(iss));
	}

	stable_sort(v2.begin(), v2.end(), compareIsbn);

	for(const auto s : v2)
		cout << s.isbn() << endl;

	return 0;
}
```

## 练习10.13

> 标准库定义了名为 partition 的算法，它接受一个谓词，对容器内容进行划分，使得谓词为true 的值会排在容器的前半部分，而使得谓词为 false 的值会排在后半部分。算法返回一个迭代器，指向最后一个使谓词为 true 的元素之后的位置。编写函数，接受一个 string，返回一个 bool 值，指出 string 是否有5个或更多字符。使用此函数划分 words。打印出长度大于等于5的元素。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

bool greater_than_5(const string &s)
{
	return s.size() >= 5;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	auto iter = partition(vs.begin(), vs.end(), greater_than_5);
	for(const auto s : vs)
		cout << s << " ";
	cout << endl;

	vs.erase(iter, vs.end());
	for(const auto s : vs)
		cout << s << " ";
	cout << endl;

	return 0;
}
```

## 练习10.14

> 编写一个 lambda ，接受两个int，返回它们的和。

```cpp
#include <iostream>

using namespace std;

int main()
{
	auto add_int = [](int x, int y){return x + y;};
	cout << add_int(1, 2) << endl;
	
	return 0;
}
```

## 练习10.15

> 编写一个 lambda ，捕获它所在函数的 int，并接受一个 int参数。lambda 应该返回捕获的 int 和 int 参数的和。

```cpp
#include <iostream>

using namespace std;

int main()
{
	int x = 1;
	auto add_int = [x](int y){return x + y;};

	cout << add_int(2) << endl;
	
	return 0;
}
```

## 练习10.16

> 使用 lambda 编写你自己版本的 biggies。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(),
		[](const string &a, const string &b)
			{ return a.size() < b.size(); });
	auto wc = find_if(words.begin(), words.end(),
		[sz](const string &a)
			{ return a.size() >= sz; });
	auto count = words.end() - wc;
	cout << count << endl;
	for(const auto s : words)
		cout << s << " ";
	cout << endl;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	biggies(vs, 5);

	return 0;
}
```

## 练习10.17

> 重写10.3.1节练习10.12的程序，在对sort的调用中使用 lambda 来代替函数 compareIsbn。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "../ch07_Classes/Sales_data_ex26.h"
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
	vector<string> v1;

	ifstream is("../ch08_The_IO_Library/book_sales");
	string buf;

	if(!is)
	{
		cerr << "open error" << endl;
		return -1;
	}

	while(getline(is, buf))
		v1.push_back(buf);

	vector<Sales_data> v2;
	for(const auto &s : v1)
	{
		// cout << s << endl;
		istringstream iss(s);
		v2.push_back(Sales_data(iss));
	}

	stable_sort(v2.begin(), v2.end(), []
		(const Sales_data &sales_data1, const Sales_data &sales_data2)
			{ return sales_data1.isbn() < sales_data2.isbn(); });

	for(const auto s : v2)
		cout << s.isbn() << endl;

	return 0;
}
```

## 练习10.18

> 重写 biggies，用 partition 代替 find_if。我们在10.3.1节练习10.13中介绍了 partition 算法。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(),
		[](const string &a, const string &b)
			{ return a.size() < b.size(); });
	auto wc = partition(words.begin(), words.end(),
		[sz](const string &a)
			{ return a.size() >= sz; });
	auto count = wc - words.begin();
	cout << count << endl;
	for(const auto s : words)
		cout << s << " ";
	cout << endl;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	biggies(vs, 5);

	return 0;
}
```

## 练习10.19

> 用 stable_partition 重写前一题的程序，与 stable_sort 类似，在划分后的序列中维持原有元素的顺序。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(),
		[](const string &a, const string &b)
			{ return a.size() < b.size(); });
	auto wc = partition(words.begin(), words.end(),
		[sz](const string &a)
			{ return a.size() >= sz; });
	auto count = wc - words.begin();
	cout << count << endl;
	for(const auto s : words)
		cout << s << " ";
	cout << endl;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	biggies(vs, 5);

	return 0;
}
```

## 练习10.20

> 标准库定义了一个名为 count_if 的算法。类似 find_if，此函数接受一对迭代器，表示一个输入范围，还接受一个谓词，会对输入范围中每个元素执行。count_if返回一个计数值，表示谓词有多少次为真。使用count_if重写我们程序中统计有多少单词长度超过6的部分。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};
	string::size_type sz = 6;

	cout << count_if(vs.begin(), vs.end(),
		[sz](const string &s)
			{ return s.size() >=sz; }) << endl;

	return 0;
}
```

## 练习10.21

> 编写一个 lambda，捕获一个局部 int 变量，并递减变量值，直至它变为0。一旦变量变为0，再调用lambda应该不再递减变量。lambda应该返回一个bool值，指出捕获的变量是否为0。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	int i = 6;

	auto reduce_i = [&i]() -> bool 
	{
		if(i <= 0)
			return false;
		else
		{
			--i;
			return true;
		}
	};

	while(reduce_i())
	{
		cout << i << endl;
	}

	return 0;
}
```

## 练习10.22

> 重写统计长度小于等于6的单词数量的程序，使用函数代替 lambda。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool judge_size(string &s, string::size_type sz)
{
	return s.size() >= sz;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	cout << count_if(vs.begin(), vs.end(), bind(judge_size, placeholders::_1, 6)) << endl;

	return 0;
}
```

## 练习10.23

> bind 接受几个参数？

假设要绑定的函数有n个参数，绑定取n + 1个参数。另外一个是函数本身的绑定。

## 练习10.24

> 给定一个string，使用 bind 和 check_size 在一个 int 的vector 中查找第一个大于string长度的值。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
bool check_size(string &s, int sz)
{
	return s.size() < sz;
}

int main()
{
	vector<int> vi = {1,2,3,4,5,6};
	string s("aaaa");

	auto iter = find_if(vi.begin(), vi.end(), bind(check_size, s, placeholders::_1));

	cout << *iter << endl;

	return 0;
}
```

## 练习10.25

> 在10.3.2节的练习中，编写了一个使用partition 的biggies版本。使用 check_size 和 bind 重写此函数。

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

bool check_size(const string &s, string::size_type sz)
{
	return s.size() >= sz;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	auto iter = partition(vs.begin(), vs.end(), bind(check_size, placeholders::_1, 5));
	for(const auto s : vs)
		cout << s << " ";
	cout << endl;

	vs.erase(iter, vs.end());
	for(const auto s : vs)
		cout << s << " ";
	cout << endl;

	return 0;
}
```

## 练习10.26

> 解释三种迭代器的不同之处。

back_inserter创建一个使用push_back的迭代器；  
front_inserter创建一个使用push_front的迭代器；  
inserter创建一个使用insert的迭代器。此函数接受第二个参数，这个参数必须是一个指向给定容器的迭代器。元素将被插入到给定迭代器所表示的元素之前。  

## 练习10.27

> 除了 unique 之外，标准库还定义了名为 unique_copy 的函数，它接受第三个迭代器，表示拷贝不重复元素的目的位置。编写一个程序，使用 unique_copy将一个vector中不重复的元素拷贝到一个初始化为空的list中。

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,1,1,2,3,4,5};
	list<int> l1;

	unique_copy(v1.begin(),v1.end(),back_inserter(l1));

	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	return 0;
}
```

## 练习10.28

> 一个vector 中保存 1 到 9，将其拷贝到三个其他容器中。分别使用inserter、back_inserter 和 front_inserter 将元素添加到三个容器中。对每种 inserter，估计输出序列是怎样的，运行程序验证你的估计是否正确。

```cpp
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,4,5,6,7,8,9};
	list<int> l1,l2,l3;

	copy(v1.begin(),v1.end(),back_inserter(l1));
	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	copy(v1.begin(),v1.end(),front_inserter(l2));
	for(const auto i : l2)
		cout << i << " ";
	cout << endl;

	copy(v1.begin(),v1.end(),inserter(l3,l3.begin()));
	for(const auto i : l3)
		cout << i << " ";
	cout << endl;

	return 0;
}
```

## 练习10.29

> 编写程序，使用流迭代器读取一个文本文件，存入一个vector中的string里。

```cpp
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	ifstream ifs("../ch08_The_IO_Library/data");
	istream_iterator<string> str_istream_iter(ifs), eof;
	vector<string> v1(str_istream_iter, eof);
	ostream_iterator<string> cout_iter(cout, " ");
	copy(v1.begin(), v1.end(), cout_iter);
	cout << endl;

	return 0;
}
```

## 练习10.30

> 使用流迭代器、sort 和 copy 从标准输入读取一个整数序列，将其排序，并将结果写到标准输出。

```cpp
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	istream_iterator<int> int_cin(cin), eof;
	vector<int> v1(int_cin, eof);
	sort(v1.begin(), v1.end());
	ostream_iterator<int> cout_iter(cout, " ");
	copy(v1.begin(), v1.end(), cout_iter);
	cout << endl;

	return 0;
}
```

## 练习10.31

> 修改前一题的程序，使其只打印不重复的元素。你的程序应该使用 unique_copy。

```cpp
#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include "../ch01_Getting_Started/Sales_item.h"

using namespace std;

int main()
{
	istream_iterator<Sales_item> int_cin(cin), eof;
	vector<Sales_item> v1(int_cin, eof);
	sort(v1.begin(), v1.end(), compareIsbn);
	// for(const auto s : v1)
	// 	cout << s.isbn() << endl;
	cout << endl;
	for(auto beg = v1.cbegin(), end = beg; beg != v1.cend(); beg = end)
	{
		end = find_if(beg, v1.cend(), [beg](const Sales_item &sale_item){ return sale_item.isbn() != beg->isbn(); });
		cout << accumulate(beg, end, Sales_item(beg->isbn())) << endl;
	}

	return 0;
}
```

## 练习10.32

> 重写1.6节中的书店程序，使用一个vector保存交易记录，使用不同算法完成处理。使用 sort 和10.3.1节中的 compareIsbn 函数来排序交易记录，然后使用 find 和 accumulate 求和。

之前谓词处写了sale_item != *beg，找了半天才发现这是检查3个成员变量的。
```cpp
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>
#include "../ch01_Getting_Started/Sales_item.h"

using namespace std;

int main()
{
	istream_iterator<Sales_item> int_cin(cin), eof;
	vector<Sales_item> v1(int_cin, eof);
	sort(v1.begin(), v1.end(), compareIsbn);
	// for(const auto s : v1)
	// 	cout << s.isbn() << endl;
	cout << endl;
	for(auto beg = v1.cbegin(), end = beg; beg != v1.cend(); beg = end)
	{
		end = find_if(beg, v1.cend(), [beg](const Sales_item &sale_item){ return sale_item.isbn() != beg->isbn(); });
		cout << accumulate(beg, end, Sales_item(beg->isbn())) << endl;
	}

	return 0;
}
```

## 练习10.33

> 编写程序，接受三个参数：一个输入文件和两个输出文件的文件名。输入文件保存的应该是整数。使用 istream_iterator 读取输入文件。使用 ostream_iterator 将奇数写入第一个输入文件，每个值后面都跟一个空格。将偶数写入第二个输出文件，每个值都独占一行。

```cpp
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{
	if(argc != 4) return -1;

	ifstream ifs(argv[1]);
	istream_iterator<int> int_istream_iter(ifs), eof;
	vector<int> v1(int_istream_iter, eof);
	
	ofstream ofs_odd("argv[2]");
	ostream_iterator<int> odd_iter(ofs_odd, "\n");
	copy_if(v1.begin(), v1.end(), odd_iter, [](int i){return i % 2; });
	ofs_odd.close();

	ofstream ofs_even("argv[3]");
	ostream_iterator<int> even_iter(ofs_even, "\n");
	copy_if(v1.begin(), v1.end(), even_iter, [](int i){return !(i % 2); });
	ofs_even.close();

	return 0;
}
```

## 练习10.34

> 使用 reverse_iterator 逆序打印一个vector。

```cpp
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,4,5,6,7,8};

	for(auto r_iter = v1.crbegin(); r_iter != v1.crend(); ++r_iter)
		cout << *r_iter << " ";
	cout << endl;

	return 0;
}
```

## 练习10.35

> 使用普通迭代器逆序打印一个vector。

```cpp
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,4,5,6,7,8};

	for(auto iter = v1.end()-1; iter != v1.begin()-1; --iter)
		cout << *iter << " ";
	cout << endl;

	return 0;
}
```

## 练习10.36

> 使用 find 在一个 int 的list 中查找最后一个值为0的元素。

```cpp
#include <iostream>
#include <iterator>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	list<int> l1 = {1,2,3,4,5,6,7,8,0};

	// for(auto r_iter = l1.crbegin(); r_iter != l1.crend(); ++r_iter)
	// 	cout << *r_iter << " ";
	// cout << endl;

	auto r_iter = find(l1.crbegin(), l1.crend(), 0);
	// r_iter.base();
	cout << distance(r_iter, l1.crend()) << endl;
	// cout << l1.end() - l1.begin() << endl;

	return 0;
}
```

## 练习10.37

> 给定一个包含10 个元素的vector，将位置3到7之间的元素按逆序拷贝到一个list中。

```cpp
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <algorithm>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3,4,5,6,7,8,9,0};
	list<int> l1(v1.crbegin()+2,v1.crbegin()+7);

	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	return 0;
}
```

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

## 练习10.42
> 使用 list 代替 vector 重新实现10.2.3节中的去除重复单词的程序。

```cpp
#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

list<string> &elimDups(list<string> &words)
{
	// sort(words.begin(), words.end());
	words.sort();
	words.unique();
	// auto end_unique = unique(words.begin(), words.end());
	// words.erase(end_unique, words.end());
	return words;
}

int main()
{
	list<string> vs = {"d","c","b","a","a","c","e"};

	for(const auto s : elimDups(vs))
		cout << s << " ";
	cout << endl;

	return 0;
}
```