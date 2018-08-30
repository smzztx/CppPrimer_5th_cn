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
