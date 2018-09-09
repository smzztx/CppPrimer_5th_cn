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
