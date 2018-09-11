## 11.1
map是关联容器，其元素是按关键字来保存和访问的；vector是顺序容器，其元素是按它们在容器中的位置来顺序保存和访问的。  

## 11.2
list：适合插入较多的场景；  
vector：动态数组的场景；  
deque：需要头部和尾部增删的场景；  
map：字典的例子；  
set：添加忽略关键字的例子。  
这里实在是想不出好例子  

## 11.3
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

## 11.4
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

## 11.5
map包括关键字-值对；set只有关键字。
[A nice answer on SO](http://stackoverflow.com/questions/16286714/advantages-of-stdset-vs-vectors-or-maps)

## 11.6
set：是关联容器，查找较快；list：是顺序容器，查找关键字是和容器的大小有关系。
[list vs set](http://stackoverflow.com/questions/2302681/c-stl-list-vs-set)

## 11.7
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

## 11.8
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

## 11.9
```cpp
std::map<std::string, std::list<std::size_t>> word_and_line;
```

## 11.10
vector<int>::iterator可以，因为可以使用<；  
list<int>::iterator不能，未定义<。  

## 11.11
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

## 11.12
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

## 11.13
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

## 11.14
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

## 11.15
mapped_type：vector<int>；  
key_type：int；  
value_type：pair<const int, vector<int>>。  

## 11.16
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

## 11.17
```cpp
copy(v.begin(), v.end(), inserter(c, c.end())); //合法
copy(v.begin(), v.end(), back_inserter(c)); //非法,set中没有push_back()
copy(c.begin(), c.end(), inserter(v, v.end())); //合法
copy(c.begin(), c.end(), back_inserter(v)); //合法
```

## 11.18
```cpp
map<string, size_t>::const_iterator map_it = word_count.cbegin();
```

## 11.19
```cpp
using COMPAREISBN = bool (*)(const Sales_data &sales_data1, const Sales_data &sales_data2);
// std::multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
std::multiset<Sales_data, COMPAREISBN> bookstore(compareIsbn);
std::multiset<Sales_data, COMPAREISBN>::iterator bookstore_iter = bookstore.begin();
```

## 11.20
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

## 11.21
```cpp
word_count.insert({word, 0})//得到insert的返回值
word_count.insert({word, 0}).first//得到map的迭代器
word_count.insert({word, 0}).first->second//map中size_t的值
++word_count.insert({word, 0}).first->second//递增该值
```

## 11.22
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

## 11.23
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

## 11.24
在m中添加一个关键字为0的元素，并对其进行初始化。  

##  11.25
在访问v的第0个元素时超出范围。  

## 11.26
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

## 11.27
查看特定元素的关键字是否在容器中用find；  
要统计该元素的关键字有多少个用count。  

## 11.28
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

## 11.29
如果没有元素与给定关键字匹配，则lower_bound和upper_bound会返回相等的迭代器——都指向给定关键字的插入点，能保持容器中元素顺序的插入位置。  
如果equal_range未匹配到元素，则两个迭代器都指向关键字可以插入的位置。  

## 11.30
第一个迭代器解引用后得到书名。  

## 11.31
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

## 11.32
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

## 11.33
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

## 11.34
当map中没有那个元素时会插入该元素，与预期不符。  

## 11.35
在这里没有影响，如果关键字出现多次，使用下标会重复赋值，最后保存的是最后一个值，使用insert只插入第一个。

## 11.36
```cpp
if(value.size() > 1)
	trans_map[key] = value.substr(1);
else
	throw runtime_error("no rule for " + key);
```
value.size() > 1 为false，将会抛出异常“no rule for” + key。

## 11.37
