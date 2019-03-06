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
函数模板，模板定义，可从它实例化出特定函数。函数模板的定义以关键字template开始，后跟尖括号对<和>，其内为一个用逗号分隔的一个或多个模板参数列表，随后是函数的定义。  
类模板，模板定义，可从它实例化出特定的类。类模板的定义以template开始，后跟尖括号<和>，其内为一个用逗号分隔的一个或多个模板参数的列表，随后是类的定义。与函数模板不同之处是，编译器不能为类模板推断模板参数类型。  
  
## 16.10
编译器使用显式模板参数列表来实例化特定的类。
  
## 16.11
```cpp
template <typename elemType> class ListItem;
template <typename elemType> class List
{
public:
    List<elemType>();
    List<elemType>(const List<elemType> &);
    List<elemType>& operator=(const List<elemType> &);
    ~List();
    void insert(ListItem<elemType> *ptr, elemType value);
private:
    ListItem<elemType> *front, *end;
};

int main()
{
    return 0;
}
```
  
## 16.12
```cpp
#ifndef STRBLOB_H_
#define STRBLOB_H_

#include <string>
#include <initializer_list>
#include <memory>
#include <vector>
#include <stdexcept>

template <typename T>
class ConstStrBlobPtr;

template <typename T>
class StrBlob
{
public:
	friend class ConstStrBlobPtr<T>;

	typedef typename std::vector<T>::size_type size_type;

	StrBlob();
	StrBlob(std::initializer_list<T> il);
	size_type size() const { return data->size(); }
	bool empty() const { return data->empty(); }
	void push_back(const T &t) { data->push_back(t); }
	void pop_back();
	T& front();
	T& back();
	const T& front() const;
	const T& back() const;
	ConstStrBlobPtr<T> begin();
	ConstStrBlobPtr<T> end();
private:
	std::shared_ptr<std::vector<T>> data;
	void check(size_type i, const T &msg) const;
};

template <typename T>
class ConstStrBlobPtr
{
public:
	ConstStrBlobPtr<T>() : curr(0){};
	ConstStrBlobPtr<T>(const StrBlob<T> &a, size_t sz = 0) : wptr(a.data), curr(sz) {}
	T& deref() const;
	ConstStrBlobPtr<T>& incr();
private:
	std::shared_ptr<std::vector<T>> check(std::size_t, const T&) const;
	std::weak_ptr<std::vector<T>> wptr;
	std::size_t curr;
};

template <typename T>
std::shared_ptr<std::vector<T>> ConstStrBlobPtr<T>::check(std::size_t i, const T &msg) const
{
	auto ret = wptr.lock();
	if(!ret)
		throw std::runtime_error("unbound ConstStrBlobPtr<T>");
	if(i >= ret->size())
		throw std::out_of_range(msg);
	return ret;
}

template <typename T>
T& ConstStrBlobPtr<T>::deref() const
{
	auto p = check(curr, "dereference past end");
	return (*p)[curr];
}

template <typename T>
ConstStrBlobPtr<T>& ConstStrBlobPtr<T>::incr()
{
	check(curr, "increment past end of ConstStrBlobPtr<T>");
	++curr;
	return *this;
}

template <typename T>
StrBlob<T>::StrBlob() : data(std::make_shared<std::vector<T>>()){}

template <typename T>
StrBlob<T>::StrBlob(std::initializer_list<T> il) : data(std::make_shared<std::vector<T>>(il)){}

template <typename T>
void StrBlob<T>::check(size_type i, const T &msg) const
{
	if(i >= data->size())
		throw std::out_of_range(msg);
}

template <typename T>
T & StrBlob<T>::front()
{
	check(0, "front on empty StrBlob");
	return data->front();
}

template <typename T>
T & StrBlob<T>::back()
{
	check(0, "back on empty StrBlob");
	return data->back();
}

template <typename T>
const T& StrBlob<T>::front() const
{
	check(0, "front on empty StrBlob");
	return data->front();
}

template <typename T>
const T& StrBlob<T>::back() const
{
	check(0, "back on empty StrBlob");
	return data->back();
}

template <typename T>
void StrBlob<T>::pop_back()
{
	check(0, "pop_back on empty StrBlob");
	data->pop_back();
}

template <typename T>
ConstStrBlobPtr<T> StrBlob<T>::begin() { return ConstStrBlobPtr<T>(*this); }

template <typename T>
ConstStrBlobPtr<T> StrBlob<T>::end()
{
	auto ret = ConstStrBlobPtr<T>(*this, data->size());
	return ret;
}

#endif
```
  
## 16.13
一对一的友好关系，相同类型实例化的BlobPtr可以相互比较。
  
## 16.14
