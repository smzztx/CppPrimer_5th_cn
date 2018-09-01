## 10.1
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

## 10.2
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

## 10.3
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

## 10.4
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

## 10.5
equal会比较指针地址，而不是字符串值，比较的结果与string类型的不一致。

## 10.6
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
## 10.7
（a）
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

## 10.8
back_inserter是<iterator>的一部分，而不是<algorithm>。  

## 10.9
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

## 10.10
改变容器大小可能会导致迭代器失效，而且每种容器都有自己的特性，改变容器大小可能需要使用不同的方法，不改变容器大小使得算法更加通用。  

## 10.11
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

## 10.12
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

## 10.13
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

## 10.14
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

## 10.15
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

## 10.16
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

## 10.17
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

## 10.18
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

## 10.19
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

## 10.20
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

## 10.21
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

## 10.22
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

## 10.23
假设要绑定的函数有n个参数，绑定取n + 1个参数。另外一个是函数本身的绑定。

## 10.24
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

## 10.25
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

## 10.26
