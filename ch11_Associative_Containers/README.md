## 练习11.1

> 描述map 和 vector 的不同。

map是关联容器，其元素是按关键字来保存和访问的；vector是顺序容器，其元素是按它们在容器中的位置来顺序保存和访问的。  

## 练习11.2

> 分别给出最适合使用 list、vector、deque、map以及set的例子。

list：适合插入较多的场景；  
vector：动态数组的场景；  
deque：需要头部和尾部增删的场景；  
map：字典的例子；  
set：添加忽略关键字的例子。  
这里实在是想不出好例子  

## 练习11.3

> 编写你自己的单词计数程序。

```cpp
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	map<string, size_t> word_count;
	string word;
	while(cin >> word)
		++word_count[word];

	for(const auto &w : word_count)
		cout << w.first << "," << w.second << endl;

	return 0;
}
```

## 练习11.4

> 扩展你的程序，忽略大小写和标点。例如，"example."、"example,"和"Example"应该递增相同的计数器。

经过研究发现，实际使用的是<ctype.h>中的ispunct，这个是全局变量。<cctype>是std::ispunct (<cctype>)和std::ispunct (<clocale>)，会有重载的问题。
```cpp
#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

int main()
{
	map<string, size_t> word_count;
	string word;

	while(cin >> word)
	{
		word.erase(find_if(word.begin(), word.end(), ::ispunct), word.end());
		for_each(word.begin(), word.end(), [](char &c){ c=tolower(c); });
		++word_count[word];
	}

	for(const auto &w : word_count)
		cout << w.first << "," << w.second << endl;

	return 0;
}
```

## 练习11.5

> 解释map和set的区别。你如何选择使用哪个？

map包括关键字-值对；set只有关键字。
[A nice answer on SO](http://stackoverflow.com/questions/16286714/advantages-of-stdset-vs-vectors-or-maps)

## 练习11.6

> 解释set和list 的区别。你如何选择使用哪个？

set：是关联容器，查找较快；list：是顺序容器，查找关键字是和容器的大小有关系。
[list vs set](http://stackoverflow.com/questions/2302681/c-stl-list-vs-set)

## 练习11.7

> 定义一个map，关键字是家庭的姓，值是一个vector，保存家中孩子（们）的名。编写代码，实现添加新的家庭以及向已有家庭中添加新的孩子。

```cpp
#include <map>
#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::map<std::string, std::vector<std::string>> familys;
	std::string last_name, first_name;

	std::cin >> last_name;
	while(std::cin >> first_name)
	{
		familys[last_name].push_back(first_name);
	}

	for(const auto f : familys)
	{
		std::cout << f.first << std::endl;
		for(const auto s : f.second)
			std::cout << s << " ";
		std::cout << std::endl;
	}

	return 0;
}
```

## 练习11.8

> 编写一个程序，在一个vector而不是一个set中保存不重复的单词。使用set的优点是什么？

```cpp
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::vector<std::string> vs;
	std::string s;
	std::cin >> s;
	vs.push_back(s);
	while(std::cin >> s)
	{
		if(std::find(vs.begin(), vs.end(), s) == vs.end())
			vs.push_back(s);
	}

	for(const auto &s : vs)
		std::cout << s << " ";
	std::cout << std::endl;

	return 0;
}
```

## 练习11.9

> 定义一个map，将单词与一个行号的list关联，list中保存的是单词所出现的行号。

```cpp
std::map<std::string, std::list<std::size_t>> word_and_line;
```

## 练习11.10

> 可以定义一个vector<int>::iterator 到 int 的map吗？list<int>::iterator 到 int 的map呢？对于两种情况，如果不能，解释为什么。

vector<int>::iterator可以，因为可以使用<；  
list<int>::iterator不能，未定义<。  

## 练习11.11

> 不使用decltype 重新定义 bookstore。

```cpp
#include <set>
#include <iostream>
#include <string>
#include "../ch07_Classes/Sales_data_ex26.h"

bool compareIsbn(const Sales_data &sales_data1, const Sales_data &sales_data2)
{
	return sales_data1.isbn() < sales_data2.isbn();
}

int main()
{
	using COMPAREISBN = bool (*)(const Sales_data &sales_data1, const Sales_data &sales_data2);
	// std::multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
	std::multiset<Sales_data, COMPAREISBN> bookstore(compareIsbn);

	return 0;
}
```

## 练习11.12

> 编写程序，读入string和int的序列，将每个string和int存入一个pair 中，pair保存在一个vector中。

```cpp
#include <utility>
#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::vector<std::pair<std::string, int>> vp;
	int i;
	std::string s;

	while(std::cin >> s >> i)
	{
		vp.push_back(std::pair<std::string, int>(s, i));
	}

	for(const auto &p : vp)
		std::cout << p.first << " " << p.second << std::endl;	

	return 0;
}
```

## 练习11.13

> 在上一题的程序中，至少有三种创建pair的方法。编写此程序的三个版本，分别采用不同的方法创建pair。解释你认为哪种形式最易于编写和理解，为什么？

```cpp
#include <utility>
#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::vector<std::pair<std::string, int>> vp;
	int i;
	std::string s;

	while(std::cin >> s >> i)
	{
		// vp.push_back(std::pair<std::string, int>(s, i));
		// std::pair<std::string, int> p(s, i); vp.push_back(p);
		// vp.push_back({s, i});
		// vp.push_back(make_pair(s, i));
		// std::pair<std::string, int> p = {s, i}; vp.push_back(p);
		vp.emplace_back(s, i);
	}

	for(const auto &p : vp)
		std::cout << p.first << " " << p.second << std::endl;	

	return 0;
}
```

## 练习11.14

> 扩展你在11.2.1节练习中编写的孩子姓达到名的map，添加一个pair的vector，保存孩子的名和生日。

```cpp
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <utility>

int main()
{
	std::map<std::string, std::vector<std::pair<std::string, std::string>>> familys;
	std::string last_name, first_name, birthday;

	std::cin >> last_name;
	while(std::cin >> first_name >> birthday)
	{
		familys[last_name].emplace_back(first_name, birthday);
	}

	for(const auto f : familys)
	{
		std::cout << f.first << std::endl;
		for(const auto p : f.second)
			std::cout << p.first << " " << p.second << std::endl;
		std::cout << std::endl;
	}

	return 0;
}
```

## 练习11.15

> 对一个int到vector<int>的map，其mapped_type、key_type和 value_type分别是什么？

mapped_type：vector<int>；  
key_type：int；  
value_type：pair<const int, vector<int>>。  

## 练习11.16

> 使用一个map迭代器编写一个表达式，将一个值赋予一个元素。

```cpp
#include <map>
#include <string>
#include <iostream>

int main()
{
	std::map<int, std::string> m = {{1,"aa"}};
	std::map<int, std::string>::iterator m_iter = m.begin();

	m_iter->second = "bb";
	std::cout << m_iter->second <<std::endl;

	return 0;
}
```

## 练习11.17

> 假定 c 是一个string的multiset，v 是一个string 的vector，解释下面的调用。指出每个调用是否合法：
```cpp
copy(v.begin(), v.end(), inserter(c, c.end()));
copy(v.begin(), v.end(), back_inserter(c));
copy(c.begin(), c.end(), inserter(v, v.end()));
copy(c.begin(), c.end(), back_inserter(v));
```

```cpp
copy(v.begin(), v.end(), inserter(c, c.end())); //合法
copy(v.begin(), v.end(), back_inserter(c)); //非法,set中没有push_back()
copy(c.begin(), c.end(), inserter(v, v.end())); //合法
copy(c.begin(), c.end(), back_inserter(v)); //合法
```

## 练习11.18

> 写出第382页循环中map_it 的类型，不要使用auto 或 decltype。

```cpp
map<string, size_t>::const_iterator map_it = word_count.cbegin();
```

## 练习11.19

> 定义一个变量，通过对11.2.2节中的名为 bookstore 的multiset 调用begin()来初始化这个变量。写出变量的类型，不要使用auto 或 decltype。

```cpp
using COMPAREISBN = bool (*)(const Sales_data &sales_data1, const Sales_data &sales_data2);
// std::multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
std::multiset<Sales_data, COMPAREISBN> bookstore(compareIsbn);
std::multiset<Sales_data, COMPAREISBN>::iterator bookstore_iter = bookstore.begin();
```

## 练习11.20

> 重写11.1节练习的单词计数程序，使用insert代替下标操作。你认为哪个程序更容易编写和阅读？解释原因。

之前的程序更容易理解，更加简洁。
```cpp
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	map<string, size_t> word_count;
	string word;
	while(cin >> word)
	{
		auto ret = word_count.insert({word, 1});
		if(!ret.second)
			++ret.first->second;
	}
		// ++word_count[word];

	for(const auto &w : word_count)
		cout << w.first << "," << w.second << endl;

	return 0;
}
```

## 练习11.21

> 假定word_count 是一个 string 到 size_t 的map，word 是一个string，解释下面循环的作用：
```cpp
while (cin >> word)
	++word_count.insert({word, 0}).first->second;
```

```cpp
word_count.insert({word, 0})//得到insert的返回值
word_count.insert({word, 0}).first//得到map的迭代器
word_count.insert({word, 0}).first->second//map中size_t的值
++word_count.insert({word, 0}).first->second//递增该值
```

## 练习11.22

> 给定一个map<string, vector<int>>，对此容器的插入一个元素的insert版本，写出其参数类型和返回类型。

```cpp
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <utility>

int main()
{
	std::map<std::string, std::vector<int>> m1;
	std::pair<std::string, std::vector<int>> p1({"aaa", {1,2,3,4}});
	std::pair<std::map<std::string, std::vector<int>>::iterator, bool> ret = m1.insert(p1);
	// std::pair<std::map<std::string, std::vector<int>>::iterator, bool> ret = m1.insert({"aaa", {1,2,3,4}});

	return 0;
}
```

## 练习11.23

> 11.2.1节练习中的map 以孩子的姓为关键字，保存他们的名的vector，用multimap 重写此map。

```cpp
#include <map>
#include <string>
#include <vector>
#include <iostream>

int main()
{
	std::multimap<std::string, std::vector<std::string>> familys;
	std::string last_name, first_name;
	std::vector<std::string> vs;

	std::cin >> last_name;
	while(std::cin >> first_name)
	{
		vs.push_back(first_name);
		// familys[last_name].push_back(first_name);
	}
	familys.insert({last_name, vs});

	for(const auto f : familys)
	{
		std::cout << f.first << std::endl;
		for(const auto s : f.second)
			std::cout << s << " ";
		std::cout << std::endl;
	}

	return 0;
}
```

## 练习11.24

> 下面的程序完成什么功能？
```cpp
map<int, int> m;
m[0] = 1;
```

在m中添加一个关键字为0的元素，并对其进行初始化。  

## 练习11.25

> 对比下面的程序与上一题程序
```cpp
vector<int> v;
v[0] = 1;
```

在访问v的第0个元素时超出范围。  

## 练习11.26

> 可以用什么类型来对一个map进行下标操作？下标运算符返回的类型是什么？请给出一个具体例子——即，定义一个map，然后写出一个可以用来对map进行下标操作的类型以及下标运算符将会返会的类型。

可以用key_type类型来对一个map进行下标操作；  
下标操作返回的类型是mapped_type。  
```cpp
#include <map>
#include <iostream>
#include <string>

int main()
{
	std::map<int, std::string> m1({{1, "aaa"}});
	std::map<int, std::string>::key_type i1 = 1;
	std::map<int, std::string>::mapped_type s1;

	s1 = m1[i1];
	std::cout << i1 << " " << s1 << std::endl;

	return 0;
}
```

## 练习11.27

> 对于什么问题你会使用count来解决？什么时候你又会选择find呢？

查看特定元素的关键字是否在容器中用find；  
要统计该元素的关键字有多少个用count。  

## 练习11.28

> 对一个string到int的vector的map，定义并初始化一个变量来保存在其上调用find所返回的结果。

```cpp
#include <map>
#include <vector>
#include <string>
#include <iostream>

int main()
{
	std::map<std::string, std::vector<int>> m1 = {{"aa", {1,2,3,4,5}}};
	std::map<std::string, std::vector<int>>::iterator m_iter = m1.find("aa");

	return 0;
}
```

## 练习11.29

> 如果给定的关键字不在容器中，upper_bound、lower_bound 和 equal_range 分别会返回什么？

如果没有元素与给定关键字匹配，则lower_bound和upper_bound会返回相等的迭代器——都指向给定关键字的插入点，能保持容器中元素顺序的插入位置。  
如果equal_range未匹配到元素，则两个迭代器都指向关键字可以插入的位置。  

## 练习11.30

> 对于本节最后一个程序中的输出表达式，解释运算对象pos.first->second的含义。

第一个迭代器解引用后得到书名。  

## 练习11.31

> 编写程序，定义一个作者及其作品的multimap。使用find在multimap中查找一个元素并用erase删除它。确保你的程序在元素不在map 中时也能正常运行。

```cpp
#include <map>
#include <string>
#include <iostream>

int main()
{
	std::multimap<std::string, std::string> m1 = {{"aa", "abc"}, {"aa", "bcd"}, {"aa", "cde"}};

	m1.erase(m1.find("aa"));

	for (const auto &p : m1)
		std::cout << p.first << " " << p.second << std::endl;

	return 0;
}
```

## 练习11.32

> 使用上一题定义的multimap 编写一个程序，按字典序打印作者列表和他们的作品。

```cpp
#include <map>
#include <string>
#include <iostream>
#include <set>

int main()
{
	std::multimap<std::string, std::string> m1 = {{"bb", "lalala"}, {"aa", "bcd"}, {"aa", "abc"}, {"aa", "cde"}};

	std::map<std::string, std::multiset<std::string>> order_m1;
	for(const auto p : m1)
		order_m1[p.first].insert(p.second);

	for (const auto &p : order_m1)
	{
		std::cout << p.first << std::endl;
		for(const auto s : p.second)
			std::cout << s << " ";
		std::cout << std::endl;
	}

	return 0;
}
```

## 练习11.33

> 实现你自己版本的单词转换程序。

```cpp
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

map<string, string> buildMap(ifstream &map_file)
{
	map<string, string> trans_map;
	string key;
	string value;
	while(map_file >> key && getline(map_file, value))
		if(value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for " + key);
	return trans_map;
}

const string &transform(const string &s, const map<string, string> &m)
{
	auto map_it = m.find(s);
	if(map_it != m.cend())
		return map_it->second;
	else
		return s;
}

void word_tranform(ifstream &map_file, ifstream &input)
{
	auto trans_map = buildMap(map_file);
	// for(const auto p : trans_map)
	// 	cout << p.first << "->" << p.second << endl;
	string text;
	while(getline(input, text))
	{
		istringstream stream(text);
		string word;
		bool firstword = true;
		while(stream >> word)
		{
			if(firstword)
				firstword = false;
			else
				cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}

int main()
{
	ifstream map_file("word_transformation.txt"), input("word_transformation_bad.txt");
	word_tranform(map_file, input);

	return 0;
}
```

## 练习11.34

> 如果你将transform 函数中的find替换为下标运算符，会发生什么情况？

当map中没有那个元素时会插入该元素，与预期不符。  

## 练习11.35

> 在buildMap中，如果进行如下改写，会有什么效果？
```cpp
trans_map[key] = value.substr(1);
//改为
trans_map.insert({key, value.substr(1)});
```

在这里没有影响，如果关键字出现多次，使用下标会重复赋值，最后保存的是最后一个值，使用insert只插入第一个。

## 练习11.36

> 我们的程序并没检查输入文件的合法性。特别是，它假定转换规则文件中的规则都是有意义的。如果文件中的某一行包含一个关键字、一个空格，然后就结束了，会发生什么？预测程序的行为并进行验证，再与你的程序进行比较。

```cpp
if(value.size() > 1)
	trans_map[key] = value.substr(1);
else
	throw runtime_error("no rule for " + key);
```
value.size() > 1 为false，将会抛出异常“no rule for” + key。

## 练习11.37

> 一个无序容器与其有序版本相比有何优势？有序版本有何优势？

无序容器可以获得更好的平均性能；  
有序容器可以自定义排序。  

## 练习11.38

> 用 unordered_map 重写单词计数程序和单词转换程序。

单词计数程序：
```cpp
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	unordered_map<string, size_t> word_count;
	string word;
	while(cin >> word)
		++word_count[word];

	for(const auto &w : word_count)
		cout << w.first << "," << w.second << endl;

	return 0;
}
```

单词转换程序：
```cpp
#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

unordered_map<string, string> buildMap(ifstream &map_file)
{
	unordered_map<string, string> trans_map;
	string key;
	string value;
	while(map_file >> key && getline(map_file, value))
		if(value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for " + key);
	return trans_map;
}

const string &transform(const string &s, const unordered_map<string, string> &m)
{
	auto map_it = m.find(s);
	if(map_it != m.cend())
		return map_it->second;
	else
		return s;
}

void word_tranform(ifstream &map_file, ifstream &input)
{
	auto trans_map = buildMap(map_file);
	// for(const auto p : trans_map)
	// 	cout << p.first << "->" << p.second << endl;
	string text;
	while(getline(input, text))
	{
		istringstream stream(text);
		string word;
		bool firstword = true;
		while(stream >> word)
		{
			if(firstword)
				firstword = false;
			else
				cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}

int main()
{
	ifstream map_file("word_transformation.txt"), input("word_transformation_bad.txt");
	word_tranform(map_file, input);

	return 0;
}
```