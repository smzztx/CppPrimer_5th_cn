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
由于C++在标准库STL中也定义了ispunct函数，定义于std命名空间，且是一个模板函数。由于程序直接通过using namespace std导入了std命名空间，程序默认使用STL库中的ispunct，导致编译器直接使用了未特化的模板函数，并未使用cctype库中的此函数，因此编译无法通过。正如SO上所说的，为了避免此类问题出现，我们应该尽量避免直接使用using namespace std;，由于std命名空间定义了很多标识符，直接导入全部的std命名空间会产生意想不到的冲突。
[摘自](https://www.jianshu.com/p/3f5f8432ec2a)
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