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
Screen.h
```cpp
#ifndef SCREEN_EX23_H_
#define SCREEN_EX23_H_

#include <string>
#include <vector>

// template <unsigned W, unsigned H>
// class Screen;

// template <unsigned W, unsigned H>
// class Window_mgr
// {
// public:
//     using ScreenIndex = std::vector<Screen<W,H>>::size_type;
//     void clear(ScreenIndex<W,H>);
// private:
//     std::vector<Screen<W,H>> screens;
// };

template <unsigned W, unsigned H>
class Screen 
{
// friend void Window_mgr::clear(ScreenIndex);
public:
    using pos = std::string::size_type;

    Screen() = default;
    Screen(char c) : contents(H*W, c){ }

    char get() const { return contents[cursor]; }
    char get(pos r, pos c) const { return contents[r*width+c]; }
    Screen &move(pos r, pos c);
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream &os) {do_display(os); return *this;}
    const Screen &display(std::ostream &os) const {do_display(os); return *this;}
    // pos size() const;

private:
    pos cursor = 0;
    pos height = H, width = W;
    std::string contents;
    void do_display(std::ostream &os) const {os << contents;}
};


template <unsigned W, unsigned H>
inline Screen<W, H> &Screen<W, H>::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

template <unsigned W, unsigned H>
inline Screen<W, H> &Screen<W, H>::set(char c)
{
	contents[cursor] = c;
	return *this;
}

template <unsigned W, unsigned H>
inline Screen<W, H> &Screen<W, H>::set(pos r, pos col, char c)
{
	contents[r*width + col] = c;
	return *this;
}

// template <unsigned W, unsigned H>
// Screen<W, H>::pos Screen<W, H>::size() const
// {
//     return height * width;
// }

// void Window_mgr::clear(ScreenIndex i)
// {
//     Screen &s = screens[i];
//     s.contents = std::string(s.height * s.width, ' ');
// }

#endif
```
  
ex14.cpp
```cpp
#include <string>
#include <iostream>
#include "Screen.h"

int main()
{
	Screen<5, 5> myScreen('X');
	
	myScreen.move(4, 0).set('#').display(std::cout);
	std::cout << "\n";
	myScreen.display(std::cout);
	std::cout << "\n";
	// std::cout << myScreen.size() << std::endl;

	return 0;
}
```
  
## 16.15
Screen.h
```cpp
#ifndef SCREEN_EX23_H_
#define SCREEN_EX23_H_

#include <string>
#include <vector>

// template <unsigned W, unsigned H>
// class Screen;

// template <unsigned W, unsigned H>
// class Window_mgr
// {
// public:
//     using ScreenIndex = std::vector<Screen<W,H>>::size_type;
//     void clear(ScreenIndex<W,H>);
// private:
//     std::vector<Screen<W,H>> screens;
// };

template <unsigned W, unsigned H>
class Screen 
{
// friend void Window_mgr::clear(ScreenIndex);
public:
    using pos = std::string::size_type;

    friend std::ostream &operator<<(std::ostream &os, const Screen<H, W> &c)
    {
        unsigned int i, j;
        for(i = 0; i < c.height; ++i)
        {
            os << c.contents.substr(i * W, W) << std::endl;
        }
        return os;
    }

    friend std::istream &operator>>(std::istream &is, Screen &c)
    {
        char a;
        is >> a;
        std::string tmp(H * W, a);
        c.contents = tmp;
        return is;
    }

    Screen() = default;
    Screen(char c) : contents(H*W, c){ }

    char get() const { return contents[cursor]; }
    char get(pos r, pos c) const { return contents[r*width+c]; }
    Screen &move(pos r, pos c);
    Screen &set(char);
    Screen &set(pos, pos, char);
    Screen &display(std::ostream &os) {do_display(os); return *this;}
    const Screen &display(std::ostream &os) const {do_display(os); return *this;}
    // pos size() const;

private:
    pos cursor = 0;
    pos height = H, width = W;
    std::string contents;
    void do_display(std::ostream &os) const {os << contents;}
};


template <unsigned W, unsigned H>
inline Screen<W, H> &Screen<W, H>::move(pos r, pos c)
{
	pos row = r * width;
	cursor = row + c;
	return *this;
}

template <unsigned W, unsigned H>
inline Screen<W, H> &Screen<W, H>::set(char c)
{
	contents[cursor] = c;
	return *this;
}

template <unsigned W, unsigned H>
inline Screen<W, H> &Screen<W, H>::set(pos r, pos col, char c)
{
	contents[r*width + col] = c;
	return *this;
}

// template <unsigned W, unsigned H>
// Screen<W, H>::pos Screen<W, H>::size() const
// {
//     return height * width;
// }

// void Window_mgr::clear(ScreenIndex i)
// {
//     Screen &s = screens[i];
//     s.contents = std::string(s.height * s.width, ' ');
// }

#endif
```
  
ex15.cpp
```cpp
#include <string>
#include <iostream>
#include "Screen.h"

int main()
{
	Screen<5, 5> myScreen('X');
	
	myScreen.move(4, 0).set('#').display(std::cout);
	std::cout << "\n";
	myScreen.display(std::cout);
	std::cout << "\n";
	std::cout << myScreen << std::endl;
	// std::cout << myScreen.size() << std::endl;

	return 0;
}
```
  
##16.16
Vec.h
```cpp
#ifndef VEC_H_
#define VEC_H_

#include <string>
#include <utility>
#include <memory>
#include <algorithm>

template <typename T>
class Vec;

template <typename T>
bool operator==(Vec<T> &lhs, Vec<T> &rhs);

template <typename T>
bool operator!=(Vec<T> &lhs, Vec<T> &rhs);

template <typename T>
bool operator<(Vec<T> &lhs, Vec<T> &rhs);

template <typename T>
bool operator>(Vec<T> &lhs, Vec<T> &rhs);

template <typename T>
bool operator<=(Vec<T> &lhs, Vec<T> &rhs);

template <typename T>
bool operator>=(Vec<T> &lhs, Vec<T> &rhs);

template <typename T>
class Vec
{
friend bool operator== <T> (Vec &lhs, Vec &rhs);
friend bool operator!= <T> (Vec &lhs, Vec &rhs);
friend bool operator< <T> (Vec &lhs, Vec &rhs);
friend bool operator> <T> (Vec &lhs, Vec &rhs);
friend bool operator<= <T> (Vec &lhs, Vec &rhs);
friend bool operator>= <T> (Vec &lhs, Vec &rhs);

public:
	Vec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
	Vec(std::initializer_list<T>);
	Vec(const Vec&);
	Vec(Vec &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free)), cap(std::move(s.cap)) { s.elements = s.first_free = s.cap = nullptr; }
	Vec &operator=(const Vec&);
	Vec &operator=(Vec&&) noexcept;
	T& operator[](std::size_t n) { return elements[n]; }
	const T& operator[](std::size_t n) const { return elements[n]; }
	~Vec();
	void push_back(const T&);
	size_t size() const { return first_free - elements; }
	size_t capacity() const { return cap - elements; }
	T *begin() const { return elements; }
	T *end() const { return first_free; }
	void reserve(size_t n);
	void resize(size_t n);
	void resize(size_t n, const T &s);
private:
	std::allocator<T> alloc;
	void chk_n_alloc() { if(size() == capacity()) reallocate(); }
	std::pair<T*, T*> alloc_n_copy(const T*, const T*);
	void free();
	void reallocate();
	T *elements;
	T *first_free;
	T *cap;
};

template <typename T>
Vec<T>::Vec(std::initializer_list<T> il)
{
	auto newdata = alloc_n_copy(il.begin(), il.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template <typename T>
void Vec<T>::push_back(const T &s)
{
	chk_n_alloc();
	alloc.construct(first_free++, s);
}

template <typename T>
std::pair<T*,T*> Vec<T>::alloc_n_copy(const T *b, const T *e)
{
	auto data = alloc.allocate(e-b);
	return {data, uninitialized_copy(b, e, data)};
}

template <typename T>
void Vec<T>::free()
{
	if(elements)
	{
		std::for_each(elements, first_free, [this](T &p){ alloc.destroy(&p); });
		// for(auto p = first_free; p != elements; )
		// 	alloc.destroy(--p);
		alloc.deallocate(elements, cap-elements);
	}
}

template <typename T>
Vec<T>::Vec(const Vec<T> &s)
{
	auto newdata = alloc_n_copy(s.begin(), s.end());
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template <typename T>
Vec<T>::~Vec()
{
	free();
}

template <typename T>
void Vec<T>::reserve(size_t n)
{
	if(n > capacity()) return;
	auto newdata = alloc.allocate(n);
	auto dest = newdata;
	auto elem = elements;
	for(size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + n;
}

template <typename T>
void Vec<T>::resize(size_t n)
{
	resize(n,T());
}

template <typename T>
void Vec<T>::resize(size_t n, const T &s)
{
	if(n < size())
	{
		while(n < size())
			alloc.destroy(--first_free);
	}else if(n > size())
	{
		while(n > size())
			push_back(s);
			// alloc.construct(first_free, s);
	}
}

template <typename T>
Vec<T> &Vec<T>::operator=(const Vec<T> &rhs)
{
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

template <typename T>
Vec<T> &Vec<T>::operator=(Vec<T> &&rhs) noexcept
{
	if(this != &rhs)
	{
		free();
		alloc = std::move(rhs.alloc);
		elements = std::move(rhs.elements);
		first_free = std::move(rhs.first_free);
		cap = std::move(rhs.cap);
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

template <typename T>
void Vec<T>::reallocate()
{
	auto newcapacity = size() ? 2 * size() : 1;
	auto newdata = alloc.allocate(newcapacity);
	auto dest = newdata;
	auto elem = elements;
	for(size_t i = 0; i != size(); ++i)
		alloc.construct(dest++, std::move(*elem++));
	free();
	elements = newdata;
	first_free = dest;
	cap = elements + newcapacity;
}

template <typename T>
bool operator==(Vec<T> &lhs, Vec<T> &rhs)
{
	return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template <typename T>
bool operator!=(Vec<T> &lhs, Vec<T> &rhs)
{
	return !(lhs == rhs);
}

template <typename T>
bool operator<(Vec<T> &lhs, Vec<T> &rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <typename T>
bool operator>(Vec<T> &lhs, Vec<T> &rhs)
{
	return rhs < lhs;
}

template <typename T>
bool operator<=(Vec<T> &lhs, Vec<T> &rhs)
{
	return !(rhs < lhs);
}

template <typename T>
bool operator>=(Vec<T> &lhs, Vec<T> &rhs)
{
	return !(lhs < rhs);
}

#endif
```
  
ex16.cpp
```cpp
#include "Vec.h"
#include <string>

int main()
{
	Vec<std::string> s({"aaa", "bbb"});

	return 0;
}
```
  
## 16.17
没有不同，在声明模板时可以typename和class可以互换。  
当我们希望通知编译器一个名字表示类型时，必须使用关键字typename，而不能使用class。  
  
## 16.18
（a）非法，U之前要加typename；  
（b）非法，模板内不能重用参数名T；  
（c）非法，inline在temple<>之后；  
（d）非法，必须声明返回类型；  
（e）合法，在模版参数Ctype的作用域之内会隐藏外层作用域声明的相同名字。  
  
## 16.19
```cpp
#include <string>
#include <vector>
#include <iostream>

template <typename T>
void print_vector(T &v)
{
	for(typename T::size_type i = 0; i != v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

int main()
{
	std::vector<std::string> vs = {"a", "bb", "ccc"};
	print_vector(vs);

	std::vector<int> vi = {1, 2, 3};
	print_vector(vi);

	return 0;
}
```
  
## 16.20
```cpp
#include <string>
#include <vector>
#include <iostream>

template <typename T>
void print_vector(T &v)
{
	for(typename T::size_type i = 0; i != v.size(); ++i)
		std::cout << v[i] << " ";
	std::cout << std::endl;
}

template <typename T>
void print_vector2(T &v)
{
	for(typename T::iterator iter = v.begin(); iter != v.end(); ++iter)
		std::cout << *iter << " ";
	std::cout << std::endl;
}

int main()
{
	std::vector<std::string> vs = {"a", "bb", "ccc"};
	print_vector(vs);

	std::vector<int> vi = {1, 2, 3};
	print_vector(vi);

	print_vector2(vs);
	print_vector2(vi);

	return 0;
}
```
  
## 16.21
DebugDelete.h
```cpp
#ifndef DEBUGDELETE_H_
#define DEBUGDELETE_H_

#include <iostream>

class DebugDelete
{
public:
	DebugDelete(std::ostream &s = std::cerr) : os(s) { }
	template <typename T> void operator() (T *p) const
	{
		os << "deleting unique_ptr" << std::endl;
		delete p;
	}
private:
	std::ostream &os;
};

#endif
```
  
ex21.cpp
```cpp
#include "DebugDelete.h"

int main()
{
	DebugDelete d;
	int *p = new int;
	d(p);

	return 0;
}
```
  
## 16.22
```cpp
#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "StrBlob.h"
#include "DebugDelete.h"

class QueryResult;

class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	StrBlob file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> word_map;
};

class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, StrBlob f) : sought(s), lines(p), file(f) { }
	std::set<StrBlob::size_type>::iterator begin() const { return lines->begin(); }
	std::set<StrBlob::size_type>::iterator end() const { return lines->end(); }
	// std::shared_ptr<StrBlob> get_file() const { return std::make_shared<StrBlob>(file); }
	const StrBlob& get_file() const { return file; }
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	StrBlob file;
};

TextQuery::TextQuery(std::ifstream &ifs)
{
	std::string text_line;

	while(std::getline(ifs, text_line))
	{
		file.push_back(text_line);
		int line_number = file.size() - 1;
		std::istringstream line(text_line);
		std::string text_word;
		while(line >> text_word)
		{
			std::string word;
			std::copy_if(text_word.begin(), text_word.end(), std::back_inserter(word), isalpha);
			// std::cout << word << std::endl;
			auto &wm_lines = word_map[word];
			if(!wm_lines)
				wm_lines.reset(new std::set<line_no>, DebugDelete());
			wm_lines->insert(line_number);
		}
	}
}

QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<TextQuery::line_no>> nodata(new std::set<TextQuery::line_no>);
	auto loc = word_map.find(sought);
	if(loc == word_map.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " /*<< make_plural(qr.lines->size(), "time", "s")*/ << std::endl;
	for(auto num : *qr.lines)
	{
		ConstStrBlobPtr p(qr.file, num);
		os << "\t(line " << num + 1 << ") " << p.deref() << std::endl;
	}
		
	return os;
}

#endif
```
  
## 16.23
在销毁shared_ptr时，调用DebugDelete()。  

## 16.24
```cpp
#ifndef BLOB_H_
#define BLOB_H_

#include <vector>
#include <memory>

template <typename T>
class Blob
{
public:
	// template <typename It>
	// Blob(It begin, It end) : data(std::make_shared<std::vector<T>>(begin, end)) { }
	template <typename It>
	Blob(It begin, It end);
private:
	std::shared_ptr<std::vector<T>> data;
};

template <typename T>
template <typename It>
Blob<T>::Blob(It begin, It end) : data(std::make_shared<std::vector<T>>(begin, end)) { }

#endif
```
  
## 16.25
