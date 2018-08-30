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
```cpp
#include <iostream>
#include <list>
#include <vector>

using namespace std;

int main()
{
	list<char *> l1 = {"aaa","bbb","ccc"};
	vector<string> v1;

	v1.assign(l1.begin(),l1.end());

	for(auto s : v1)	cout << s << " ";
	cout << endl;

	return 0;
}
```

## 9.15
```cpp
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3};
	vector<int> v2 = {1,3};

	cout << boolalpha << (v1 == v2) << endl;

	return 0;
}
```

## 9.16
```cpp
#include <vector>
#include <iostream>
#include <list>

using namespace std;

int main()
{
	vector<int> v1 = {1,2,3};
	list<int> l1 = {1,2,3};

	cout << boolalpha << (vector<int>(l1.begin(),l1.end()) == v1) << endl;

	return 0;
}
```

## 9.17
c1和c2不能是无序容器，且容器类型要相同，最后，元素类型要支持运算符。

## 9.18
```cpp
#include <string>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
	string s;
	deque<string> deque1;

	while(cin >> s)
		deque1.push_back(s);

	for(auto iter = deque1.cbegin(); iter != deque1.cend(); ++iter)
		cout << *iter << " ";
	cout << endl;

	return 0;
}
```

## 9.19
只需讲deque替换为list。
```cpp
#include <string>
#include <list>
#include <iostream>

using namespace std;

int main()
{
	string s;
	list<string> list1;

	while(cin >> s)
		list1.push_back(s);

	for(auto iter = list1.cbegin(); iter != list1.cend(); ++iter)
		cout << *iter << " ";
	cout << endl;
	
	return 0;
}
```

## 9.20
```cpp
#include <string>
#include <list>
#include <deque>
#include <iostream>

using namespace std;

int main()
{
	list<int> list1 = {1,2,3,4,5,6};
	deque<int> deque_odd, deque_even;

	for(const auto i : list1)
		(i % 2) ? deque_odd.push_back(i) : deque_even.push_back(i);
		//(i & 0x1 ? deque_odd : deque_even).push_back(i);

	for(const auto i : deque_odd)
		cout << i << " ";
	cout << endl;

	for(const auto i : deque_even)
		cout << i << " ";
	cout << endl;
	
	return 0;
}
```

## 9.21
还是一样的操作，实现的是在vector的一个特定位置反复插入元素。具体请查看本节使用insert返回值的内容。

## 9.22
问题：
1.循环不会停止；
2.迭代器在插入操作后会变化。
```cpp
// cause the reallocation will lead the iterators and references
// after the insertion point to invalid. Thus, we need to call reserver at first.

#include <iostream>
#include <vector>

void double_and_insert(std::vector<int>& v, int some_val)
{
    auto mid = [&]{ return v.begin() + v.size() / 2; };
    for (auto curr = v.begin(); curr != mid(); ++curr)
        if (*curr == some_val)
            ++(curr = v.insert(curr, 2 * some_val));
}

int main()
{
    std::vector<int> v{ 1, 9, 1, 9, 9, 9, 1, 1 };
    double_and_insert(v, 1);

    for (auto i : v) 
        std::cout << i << std::endl;
}
```

## 9.23
同一个元素的拷贝。

## 9.24
```cpp
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// vector<int> v1 = {1};
	vector<int> v1;

	cout << v1.at(0) << endl;		//terminate called after throwing an instance of 'std::out_of_range'   what():  vector::_M_range_check
	cout << v1[0] << endl;			//Segmentation fault (core dumped)
	cout << v1.front() << endl;		//Segmentation fault (core dumped)
	cout << *v1.begin() << endl;	//Segmentation fault (core dumped)

	return 0;
}
```

## 9.25
如果elem1与elem2相等，则一个元素都不会删除；  
如果elem2是尾后迭代器，则会从elem1元素删除到最后一个元素；  
如果elem1与elem2都是尾后迭代器，则一个元素都不会删除。  

## 9.26
```cpp
#include <iostream>
#include <vector>
#include <list>

using namespace std;

int main()
{
	int ia[] = { 0, 1, 1, 2, 3, 5, 8, 13, 21, 55, 89 };

	vector<int> v1(ia, end(ia));
	list<int> l1(ia, end(ia));

	for(auto iter = l1.begin(); iter != l1.end(); )
	{		
		if(*iter % 2) iter = l1.erase(iter);
		else ++iter;
	}

	for(auto iter = v1.begin(); iter != v1.end(); )
	{	
			if(*iter % 2 == 0) iter = v1.erase(iter);
			else ++iter;
	}
	
	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	for(const auto i : v1)
		cout << i << " ";
	cout << endl;

	return 0;
}
```

## 9.27
```cpp
#include <iostream>
#include <forward_list>

using namespace std;

int main()
{
	forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};
	auto prev = flst.before_begin();
	auto curr = flst.begin();

	while(curr != flst.end())
	{
		if(*curr % 2)
			curr = flst.erase_after(prev);
		else
		{
			prev = curr;
			++ curr;
		}
	}

	for(const auto i : flst)
		cout << i << " ";
	cout << endl;

	return 0;
}
```
## 9.28
```cpp
#include <iostream>
#include <forward_list>

using namespace std;

void insert_string(forward_list<string> &flst, const string &find_str, const string &insert_str)
{
	auto prev = flst.before_begin();
	auto curr = flst.begin();

	while(curr != flst.end())
	{
		if(*curr == find_str)
		{
			flst.insert_after(curr, insert_str);
			return;
		}
		else
		{
			prev = curr;
			++curr;
		}
	}
	flst.insert_after(prev, insert_str);
}

int main()
{
	forward_list<string> flst = {"aa", "bb", "cc", "dd"};

	insert_string(flst, "aaa", "bilibili");

	for(const auto s : flst)
		cout << s << " ";
	cout << endl;

	return 0;
}
```

## 9.29
会添加75个新元素，并对新元素进行初始化；  
后面90个元素会被丢弃。  

## 9.30
如果元素类型的类类型，则元素类型必须提供一个默认构造函数。

## 9.31
list:
```cpp
#include <list>
#include <iostream>

using namespace std;

int main()
{
	list<int> l1 = {0,1,2,3,4,5,6,7,8,9};
	auto iter = l1.begin();

	while(iter != l1.end())
	{
		if(*iter % 2)
		{
			iter = l1.insert(iter, *iter);
			++iter;
			++iter;
		}else
		{
			iter = l1.erase(iter);
		}
	}

	for(const auto i : l1)
		cout << i << " ";
	cout << endl;

	return 0;
}
```

forward_list:
```cpp
#include <forward_list>
#include <iostream>

using namespace std;

int main()
{
	forward_list<int> flst = {0,1,2,3,4,5,6,7,8,9};
	auto iter = flst.begin();
	auto prev = flst.before_begin();

	while(iter != flst.end())
	{
		if(*iter % 2)
		{
			iter = flst.insert_after(iter, *iter);
			prev = iter;
			++iter;
		}else
		{
			iter = flst.erase_after(prev);
		}
	}

	for(const auto i : flst)
		cout << i << " ";
	cout << endl;

	return 0;
}
```

## 9.32
不合法，insert中的参数运行顺序是未定义的，我们不知道iter运行的是iter+1的状态还是未+1的状态。

## 9.33
```cpp
#include <vector>
#include <iostream>

using namespace std;

int main()
{
	vector<int> v1 = {0,1,2,3,4,5,6,7,8,9};
	auto iter = v1.begin();

	while(iter != v1.end())
	{
		++iter;
		// iter = v1.insert(iter, 42);
		v1.insert(iter, 42);
		++iter;
	}

	for(const auto i : v1)
		cout << i << " ";
	cout << endl;

	return 0;
}
```
插入操作：如果存储空间被重新分配，则迭代器全部失效；如果没有重新分配，插入位置之后的迭代器全部失效。
运行结果为：
```sh
$ ./ex33 *** Error in `./ex33': munmap_chunk(): invalid pointer: 0x0000000002118040 ***
Aborted (core dumped)
```

## 9.34
会无限循环，当碰到第一个奇数时，iter从inert()中得到插入元素的迭代器，++iter后，迭代器指向的还是之前碰到的那个奇数，下次循环中还是检查这个奇数，程序陷入无限循环。  
在测试代码中，如果取消打印行的注释，会一直打印1。  

## 9.35
容器的size是指它已经保存的元素的数目；而capacity则是在不分配新的内存空间的前提下最多可以保存多少元素。  

## 9.36
不可能。

## 9.37
list所占的空间不是连续的；array是固定size的。

## 9.38
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<string> v;
	
	for (string buffer; cin >> buffer; v.push_back(buffer))
		cout << v.size() << " " << v.capacity() << endl;

	return 0;
}
```

## 9.39
为svec预留1024的空间，将输入添加到svec中，将svec的size增加当前size的一半。  

## 9.40
读入了256词、512词时，size增加到384、768，capacity不变；  
读入1000词或1048词后，size增加到1500、1572，capacity至少增大到可以容纳当前size。  

## 9.41
```cpp
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
	vector<char> vc = {'a','b','c'};
	string s(vc.begin(), vc.end());

	for(const auto c : vc)
		cout << c << " ";
	cout << endl;

	return 0;
}
```

## 9.42
```cpp
string s;
s.reserve(100);
```

## 9.43
在gcc上编译失败。
```cpp
//it can't compile it on gcc.
#include <string>
#include <iostream>

using namespace std;

void replace_with_str(string &s, const string &oldVal, const string &newVal)
{
	auto iter = s.begin();

	while(iter != s.end())
	{
		if(oldVal == string(iter, iter+oldVal.size()))
		{
			iter = s.erase(iter, iter+oldVal.size());
			iter = s.insert(iter, newVal.begin(), newVal.end());
			iter += newVal.size();
		}else
			++iter;
	}
}

int main()
{
	string s("tho thru");

	replace_with_str(s, "tho", "though");
	cout << s << endl;

	replace_with_str(s, "thru", "through");
	cout << s << endl;

	return 0;
}
```

## 9.44
```cpp
#include <string>
#include <iostream>

using namespace std;

void replace_with_str(string &s, const string &oldVal, const string &newVal)
{
	// auto iter = s.begin();
	string::size_type index = 0;

	while(index != s.size())
	{
		if(oldVal == string(s, index, oldVal.size()))
		{
			s.replace(index, oldVal.size(), newVal);
		}
		++index;
	}
}

int main()
{
	string s("tho thru tho");

	replace_with_str(s, "tho", "though");
	cout << s << endl;

	replace_with_str(s, "thru", "through");
	cout << s << endl;

	return 0;
}
```

## 9.45
```cpp
#include <string>
#include <iostream>

using namespace std;

string add_pre_post(const string &name, const string &pre, const string &post)
{
	string s = name;
	s.insert(s.begin(), pre.cbegin(), pre.cend());
	return s.append(post);
}

int main()
{
	string name("tx");

	cout << add_pre_post(name, "Mr.", "Jr.") << endl;

	cout << add_pre_post("TX", "Mr.", "Jr.") << endl;

	return 0;
}
````

## 9.46
```cpp
#include <string>
#include <iostream>

using namespace std;

string add_pre_post(const string &name, const string &pre, const string &post)
{
	string s = name;
	s.insert(0, pre);
	return s.insert(s.size(), post);
}

int main()
{
	string name("tx");

	cout << add_pre_post(name, "Mr.", "Jr.") << endl;

	cout << add_pre_post("TX", "Mr.", "Jr.") << endl;

	return 0;
}
```

## 9.47
```cpp
#include <string>
#include <iostream>

using namespace std;

int main()
{
	string numbers{"123456789"};
	string alphabet{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	string str{"ab2c3d7R4E6"};

	for(string::size_type pos = 0; (pos = str.find_first_of(numbers, pos)) != string::npos; ++pos)
	{
		cout << "found number at index: " << pos
		<< " element is " << str[pos] << endl;
	}
	for(string::size_type pos = 0; (pos = str.find_first_of(alphabet, pos)) != string::npos; ++pos)
	{
		cout << "found alphabet at index: " << pos
		<< " element is " << str[pos] << endl;
	}

	for(string::size_type pos = 0; (pos = str.find_first_not_of(alphabet, pos)) != string::npos; ++pos)
	{
		cout << "found number at index: " << pos
		<< " element is " << str[pos] << endl;
	}
	for(string::size_type pos = 0; (pos = str.find_first_not_of(numbers, pos)) != string::npos; ++pos)
	{
		cout << "found alphabet at index: " << pos
		<< " element is " << str[pos] << endl;
	}

	return 0;
}
```

## 9.48
string::npos

## 9.49
```cpp
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<string> v1(10, "5");
	int sum_int = 0;
	for(const auto s : v1)
		sum_int += stoi(s);
	cout << sum_int << endl;

	vector<string> v2(10, "3.14");
	double sum_double = 0;
	for(const auto s : v2)
		sum_double += stod(s);
	cout << sum_double << endl;

	return 0;
}
```

## 9.51
```cpp
#include <string>
#include <iostream>

using namespace std;

class my_date
{
public:
	my_date(const string&);
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;
};

my_date::my_date(const string &s)
{
	string date_str = s;
	string::size_type index1 = 0;
	string::size_type index2 = 0;

	if(s.find(',') != string::npos)//January 1, 1900
	{
		index1 = s.find(' ');
		index2 = s.find(',', index1+1);
		cout << "year: " << s.substr(index2+1, s.size()) << "; month: " << s.substr(0, index1) << "; day: " << s.substr(index1+1, index2-index1-1) << endl;
		// month = stoi(s.substr(0, index1));
		if( s.find("Jan") < s.size() )  month = 1;
		if( s.find("Feb") < s.size() )  month = 2;
		if( s.find("Mar") < s.size() )  month = 3;
		if( s.find("Apr") < s.size() )  month = 4;
		if( s.find("May") < s.size() )  month = 5;
		if( s.find("Jun") < s.size() )  month = 6;
		if( s.find("Jul") < s.size() )  month = 7;
		if( s.find("Aug") < s.size() )  month = 8;
		if( s.find("Sep") < s.size() )  month = 9;
		if( s.find("Oct") < s.size() )  month =10;
		if( s.find("Nov") < s.size() )  month =11;
		if( s.find("Dec") < s.size() )  month =12;
		day = stoi(s.substr(index1+1, index2-index1-1));
		year = stoi(s.substr(index2+1, s.size()));
	}else if(s.find('/') != string::npos)//1/1/1900
	{
		index1 = s.find('/');
		index2 = s.find('/', index1+1);
		cout << "year: " << s.substr(index2+1, s.size()) << "; month: " << s.substr(0, index1) << "; day: " << s.substr(index1+1, index2-index1-1) << endl;
		month = stoi(s.substr(0, index1));
		day = stoi(s.substr(index1+1, index2-index1-1));
		year = stoi(s.substr(index2+1, s.size()));
	}else//Jan 1 1900
	{
		index1 = s.find(' ');
		index2 = s.find(' ', index1+1);
		cout << "year: " << s.substr(index2+1, s.size()) << "; month: " << s.substr(0, index1) << "; day: " << s.substr(index1+1, index2-index1-1) << endl;
		// month = stoi(s.substr(0, index1));
		if( s.find("Jan") < s.size() )  month = 1;
		if( s.find("Feb") < s.size() )  month = 2;
		if( s.find("Mar") < s.size() )  month = 3;
		if( s.find("Apr") < s.size() )  month = 4;
		if( s.find("May") < s.size() )  month = 5;
		if( s.find("Jun") < s.size() )  month = 6;
		if( s.find("Jul") < s.size() )  month = 7;
		if( s.find("Aug") < s.size() )  month = 8;
		if( s.find("Sep") < s.size() )  month = 9;
		if( s.find("Oct") < s.size() )  month =10;
		if( s.find("Nov") < s.size() )  month =11;
		if( s.find("Dec") < s.size() )  month =12;
		day = stoi(s.substr(index1+1, index2-index1-1));
		year = stoi(s.substr(index2+1, s.size()));
	}
	cout << "year: " << year << "; month: " << month << "; day: " << day << endl;
}

int main()
{
	my_date my_date1("January 1, 1900");
	my_date my_date2("1/1/1900");
	my_date my_date3("Jan 1 1900");

	return 0;
}
```

## 9.52
看了半天没看懂，还以为要写个计算器，贴上大神代码：  
```cpp
//
//  ex9_52.cpp
//  Exercise 9.52 
//
//  Created by pezy on 12/5/14.
//
//  @Brief  Use a stack to process parenthesized expressions. 
//          When you see an open parenthesis, note that it was seen. 
//          When you see a close parenthesis after an open parenthesis, 
//          pop elements down to and including the open parenthesis off the stack. 
//          push a value onto the stack to indicate that a parenthesized expression was replaced. 

#include <stack>
#include <string>
#include <iostream>

using std::string; using std::cout; using std::endl; using std::stack;

int main()
{
    string expression{ "This is (pezy)." };
    bool bSeen = false;
    stack<char> stk;
    for (const auto &s : expression)
    {
        if (s == '(') { bSeen = true; continue; }
        else if (s == ')') bSeen = false;
        
        if (bSeen) stk.push(s);
    }
    
    string repstr;
    while (!stk.empty())
    {
        repstr += stk.top();
        stk.pop();
    }
    
    expression.replace(expression.find("(")+1, repstr.size(), repstr);
    
    cout << expression << endl;
    
    return 0;
}
```