## 9.1
（a）list，需要在中间插入数据，list最好；
（b）qedue，需要在头部和尾部插入或删除元素，选qedue；
（c）vector，没有特别的需求选vector。

## 9.2
```cpp
list<deque<int>> l;
```

## 9.3
两个迭代器begin和end满足如下条件：
它们指向同一个容器中的元素，或者是容器中的最后一个元素之后的位置，且我们可以通过反复递增begin来到达end。换句话说，end不在begin之前。

## 9.4
```cpp
#include <iostream>
#include <vector>

using namespace std;

bool find_int(vector<int>::const_iterator begin_, vector<int>::const_iterator end_, int n)
{
	// for(vector::const_iterator begin = begin_;begin != end_;++begin)
	while(begin_ != end_)
	{
		if( *begin_ == n) return true;
		++begin_;
	}

	return false;
}

int main()
{
	vector<int> vi{1,2,3,4,5,6};

	cout << boolalpha << find_int(vi.begin(), vi.end(), 0) << endl;

	return 0;
}
```

## 9.5
```cpp
#include <iostream>
#include <vector>

using namespace std;

vector<int>::const_iterator find_int(vector<int>::const_iterator begin_, vector<int>::const_iterator end_, int n)
{
	while(begin_ != end_)
	{
		if( *begin_ == n) return begin_;
		++begin_;
	}

	return begin_;
}

int main()
{
	vector<int> vi{1,2,3,4,5,6};

	find_int(vi.begin(), vi.end(), 0);

	return 0;
}
```

## 9.6
```cpp
while(iter1 != iter2)
```

## 9.7
```cpp
vector<int>::size_type
```

## 9.8
```cpp
list<string>::const_iterator		//read
list<string>::iterator				//write
```

## 9.9
begin返回容器的iterator类型，当我们需要写访问时使用；  
cbegin返回容器的const_iterator类型，当我们不需要写访问时使用。  

## 9.10
```cpp
it1：vector<int>::iterator，it2：vector<int>::const_iterator；
it3：vector<int>::const_iterator，it4：vector<int>::const_iterator。
```

## 9.11
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

## 9.12
两个容器的类型及其元素必须匹配；
传递迭代器参数来拷贝一个范围时，就不要求容器类型相同了，只要能将要拷贝的元素转换。

## 9.13
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <list>

using std::list; using std::vector; using std::cout; using std::endl;

int main()
{
    list<int> ilst(5, 4);
    vector<int> ivc(5, 5);

    // from list<int> to vector<double>
    vector<double> dvc(ilst.begin(), ilst.end());
    for (auto i : ilst) cout << i << " ";
    cout << endl;
    for (auto d : dvc) cout << d << " ";
    cout << endl;

    // from vector<int> to vector<double>
    vector<double> dvc2(ivc.begin(), ivc.end());
    for (auto i : ivc) cout << i << " ";
    cout << endl;
    for (auto d : dvc2) cout << d << " ";
    cout << endl;
    
    return 0;
}
```

## 9.14
