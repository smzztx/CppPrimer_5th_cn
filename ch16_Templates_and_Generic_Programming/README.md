## 16.1
实例化：编译器处理过程，用实际的模板实参来生成模板的一个特殊实例，其中参数被替换为对应的实参。当函数模板被调用时，会自动根据传递给它的实参来实例化。而使用类模板时，则需要我们提供显式模板实参。  
  
## 16.2
```cpp
#include <iostream>

template<typename T>
int compare(const T &lhs, const T &rhs)
{
	if(lhs < rhs) return -1;
	if(rhs < lhs) return 1;
	return 0;
}

int main()
{
	std::cout << compare(1, 2) << std::endl;

	return 0;
}
```
  
## 16.3
```sh
error: no match for ‘operator<’ (operand types are ‘const Sales_data’ and ‘const Sales_data’)
```
  
## 16.4
```cpp
#include <iostream>
#include <vector>
#include <list>
#include <string>

class Sales_data{ };

template<typename InputIt, typename T>
InputIt find(const InputIt beg, const InputIt end, const T &value)
{
	for (InputIt iter = beg; iter != end; ++iter)
	{
		if (*iter == value)
		{
			return iter;
		}
	}
}

int main()
{
	std::vector<int> vi = {1, 2, 3};
	std::list<std::string> ls = {"aa", "bb", "cc"};

	std::cout << *(find(vi.begin(), vi.end(), 3)) << std::endl;
	std::cout << *(find(ls.begin(), ls.end(), "bb")) << std::endl;

	return 0;
}
```
  
## 16.5
```cpp
#include <iostream>
#include <string>

template<typename T>
void print(const T &arr)
{
	for(auto elem : arr)
		std::cout << elem << std::endl;
}

int main()
{
	char ac[] = "aabbccdd";
	int ai[] = {1, 2, 3, 4};

	print(ac);
	print(ai);

	return 0;
}
```
  
## 16.6
```cpp
#include <iostream>
#include <string>

template<typename T, unsigned N>
T* begin(T (&arr)[N])
{
	return arr;
}

template<typename T, unsigned N>
T* end(T (&arr)[N])
{
	return arr + N;
}

int main()
{
	char ac[] = "aabbccdd";

	std::cout << *(begin(ac)) << std::endl;
	std::cout << *(end(ac) - 1) << std::endl;

	return 0;
}
```
  
## 16.7
```cpp
#include <iostream>
#include <string>

template<typename T, unsigned size>
constexpr unsigned getSize(const T(&)[size])
{
    return size;
}

int main()
{
	char ac[] = "aabbccdd";

	std::cout << getSize(ac) << std::endl;

	return 0;
}
```
  
## 16.8
因为!=更符合“编写类型无关的代码”的原则。
  
## 16.9
