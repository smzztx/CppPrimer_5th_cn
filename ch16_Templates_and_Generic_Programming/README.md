## 练习16.1

> 给出实例化的定义。

实例化：编译器处理过程，用实际的模板实参来生成模板的一个特殊实例，其中参数被替换为对应的实参。当函数模板被调用时，会自动根据传递给它的实参来实例化。而使用类模板时，则需要我们提供显式模板实参。  
  
## 练习16.2

> 编写并测试你自己版本的 compare 函数。

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
  
## 练习16.3

> 对两个 Sales_data 对象调用你的 compare 函数，观察编译器在实例化过程中如何处理错误。

```sh
error: no match for ‘operator<’ (operand types are ‘const Sales_data’ and ‘const Sales_data’)
```
  
## 练习16.4

> 编写行为类似标准库 find 算法的模版。函数需要两个模版类型参数，一个表示函数的迭代器参数，另一个表示值的类型。使用你的函数在一个 vector<int> 和一个list<string>中查找给定值。

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
  
## 练习16.5

> 为6.2.4节中的print函数编写模版版本，它接受一个数组的引用，能处理任意大小、任意元素类型的数组。

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
  
## 练习16.6

> 你认为接受一个数组实参的标准库函数 begin 和 end 是如何工作的？定义你自己版本的 begin 和 end。

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
  
## 练习16.7

> 编写一个 constexpr 模版，返回给定数组的大小。

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
  
## 练习16.8

> 在第97页的“关键概念”中，我们注意到，C++程序员喜欢使用 != 而不喜欢 < 。解释这个习惯的原因。

因为!=更符合“编写类型无关的代码”的原则。
  
## 练习16.9

> 什么是函数模版，什么是类模版？

函数模板，模板定义，可从它实例化出特定函数。函数模板的定义以关键字template开始，后跟尖括号对<和>，其内为一个用逗号分隔的一个或多个模板参数列表，随后是函数的定义。  
类模板，模板定义，可从它实例化出特定的类。类模板的定义以template开始，后跟尖括号<和>，其内为一个用逗号分隔的一个或多个模板参数的列表，随后是类的定义。与函数模板不同之处是，编译器不能为类模板推断模板参数类型。  
  
## 练习16.10

> 当一个类模版被实例化时，会发生什么？

编译器使用显式模板参数列表来实例化特定的类。
  
## 练习16.11

> 下面 List 的定义是错误的。应如何修改它？
```cpp
template <typename elemType> class ListItem;
template <typename elemType> class List {
public:
	List<elemType>();
	List<elemType>(const List<elemType> &);
	List<elemType>& operator=(const List<elemType> &);
	~List();
	void insert(ListItem *ptr, elemType value);
private:
	ListItem *front, *end;
};
```

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
  
## 练习16.12

> 编写你自己版本的 Blob 和 BlobPtr 模版，包含书中未定义的多个const成员。

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
  
## 练习16.13

> 解释你为 BlobPtr 的相等和关系运算符选择哪种类型的友好关系？

一对一的友好关系，相同类型实例化的BlobPtr可以相互比较。
  
## 练习16.14

> 编写 Screen 类模版，用非类型参数定义 Screen 的高和宽。

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
  
## 练习16.15

> 为你的 Screen 模版实现输入和输出运算符。Screen 类需要哪些友元（如果需要的话）来令输入和输出运算符正确工作？解释每个友元声明（如果有的话）为什么是必要的。

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
  
## 练习16.16

> 将 StrVec 类重写为模版，命名为 Vec。

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
        //  alloc.destroy(--p);
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
  
## 练习16.17

> 声明为 typename 的类型参数和声明为 class 的类型参数有什么不同（如果有的话）？什么时候必须使用typename？

没有不同，在声明模板时可以typename和class可以互换。  
当我们希望通知编译器一个名字表示类型时，必须使用关键字typename，而不能使用class。  
  
## 练习16.18

> 解释下面每个函数模版声明并指出它们是否非法。更正你发现的每个错误。
```cpp
(a) template <typename T, U, typename V> void f1(T, U, V);
(b) template <typename T> T f2(int &T);
(c) inline template <typename T> T foo(T, unsigned int *);
(d) template <typename T> f4(T, T);
(e) typedef char Ctype;
	template <typename Ctype> Ctype f5(Ctype a);
```

（a）非法，U之前要加typename；  
（b）非法，模板内不能重用参数名T；  
（c）非法，inline在temple<>之后；  
（d）非法，必须声明返回类型；  
（e）合法，在模版参数Ctype的作用域之内会隐藏外层作用域声明的相同名字。  
  
## 练习16.19

> 编写函数，接受一个容器的引用，打印容器中的元素。使用容器的 size_type 和 size成员来控制打印元素的循环。

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
  
## 练习16.20

> 重写上一题的函数，使用begin 和 end 返回的迭代器来控制循环。

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
  
## 练习16.21

> 编写你自己的 DebugDelete 版本。

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
  
## 练习16.22

> 修改12.3节中你的 TextQuery 程序，令 shared_ptr 成员使用 DebugDelete 作为它们的删除器。

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
  
## 练习16.23

> 预测在你的查询主程序中何时会执行调用运算符。如果你的预测和实际不符，确认你理解了原因。

在销毁shared_ptr时，调用DebugDelete()。  
  
## 练习16.24

> 为你的 Blob 模版添加一个构造函数，它接受两个迭代器。

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
  
## 练习16.25

> 解释下面这些声明的含义。
```cpp
extern template class vector<string>;
template class vector<Sales_data>;
```

实例化声明模板类vector<string>，不在本文件中实例化；  
实例化定义模板类vector<Sales_data>，在本文件中实例化。  
  
## 练习16.26

> 假设 NoDefault 是一个没有默认构造函数的类，我们可以显式实例化 vector<NoDefualt>吗？如果不可以，解释为什么。

不能，如果没有默认构造函数，我们又没有提供参数，该类无法初始化，vector无法实例化。  
  
## 练习16.27

> 对下面每条带标签的语句，解释发生了什么样的实例化（如果有的话）。如果一个模版被实例化，解释为什么;如果未实例化，解释为什么没有。
```cpp
template <typename T> class Stack {	};
void f1(Stack<char>); 		//(a)
class Exercise {
	Stack<double> &rds;		//(b)
	Stack<int> si;			//(c)
};
int main() {
	Stack<char> *sc;		//(d)
	f1(*sc);				//(e)
	int iObj = sizeof(Stack<string>);	//(f)
}
```

注意区分模板实例化与对象实例化。  
需要（隐式）实例化的理由一般是需要获得模板函数/类的定义。  
（a）实例化，在函数中定义；  
（b）实例化，在类中定义；  
（c）实例化，在类中定义；  
（d）未实例化，使用时实例化；  
（e）未实例化，在（a）处实例化模板；  
（f）实例化，sizeof 需要知道 Stack<string> 的定义才能给出一个 Stack<string> 对象的大小，会实例化。  
  
## 练习16.28

> 编写你自己版本的 shared_ptr 和 unique_ptr。

shared_pointer.h
```cpp
#pragma once
#include <functional>
#include "delete.h"

namespace cp5
{
    template <typename T>
    class SharedPointer;

    template <typename T>
    void swap(SharedPointer<T> &lhs, SharedPointer<T> &rhs)
    {
        using std::swap;
        swap(lhs.ptr, rhs.ptr);
        swap(lhs.ref_count, rhs.ref_count);
        swap(lhs.deleter, rhs.deleter);
    }

    template <typename T>
    class SharedPointer
    {
    public:
        SharedPointer() : ptr(nullptr), ref_count{ new std::size_t(1)}, deleter{ cp5::Delete{} } { };
        explicit SharedPointer(T *raw_ptr) : ptr{ raw_ptr }, ref_count{ new std::size_t(1) }, deleter{ cp5::Delete{} } { };
        SharedPointer(SharedPointer const &other) : ptr{ other.ptr }, ref_count{ other.ref_count }, deleter{ other.deleter }
        {
            ++*ref_count;
        }

        SharedPointer(SharedPointer &&other) noexcept : ptr{ other.ptr }, ref_count{ other.ref_count }, deleter{ std::move(other.deleter) }
        {
            other.ptr = nullptr;
            other.ref_count = nullptr;
        }

        SharedPointer &operator=(SharedPointer const& rhs)
        {
            //increment first to ensure safty for self-assignment
            ++*rhs.ref_count;
            decrement_and_destroy();
            ptr = rhs.ptr, ref_count = rhs.ref_count, deleter = rhs.deleter;
            return *this;
        }

        SharedPointer& operator=(SharedPointer && rhs) noexcept
        {
            cp5::swap(*this, rhs);
            rhs.decrement_and_destroy();
            return *this;
        }

        operator bool() const
        {
            return ptr ? true : false;
        }

        T& operator* () const
        {
            return *ptr;
        }

        T* operator->() const
        {
            return &*ptr;
        }

        std::size_t use_count() const
        {
            return *ref_count;
        }

        T *get() const
        {
            return ptr;
        }

        bool unique() const
        {
            return 1 == *ref_count;
        }

        void swap(SharedPointer& rhs)
        {
            cp5::swap(*this, rhs);
        }

        void reset()
        {
            decrement_and_destroy();
        }

        void reset(T* pointer)
        {
            if (ptr != pointer)
            {
                decrement_and_destroy();
                ptr = pointer;
                ref_count = new std::size_t(1);
            }
        }

        void reset(T *pointer, const std::function<void(T*)>& d)
        {
            reset(pointer);
            deleter = d;
        }

        ~SharedPointer()
        {
            decrement_and_destroy();
        }

    private:
        T *ptr;
        std::size_t *ref_count;
        std::function<void(T*)> deleter;
        void decrement_and_destroy()
        {
            if(ptr && 0 == --*ref_count)
                delete ref_count,deleter(ptr);
            else if(!ptr)
                delete ref_count;
            ref_count = nullptr;
            ptr = nullptr;
        }
    };
}
```
  
unique_pointer.h
```cpp
#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

#include "../ex22/DebugDelete.h"

template <typename, typename> class unique_pointer;
template <typename T, typename D> void
swap(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs);

template <typename T, typename D = DebugDelete>
class unique_pointer
{
    friend void swap<T, D>(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs);

public:
    unique_pointer(const unique_pointer&) = delete;
    unique_pointer &operator=(const unique_pointer&) = delete;

    unique_pointer() = default;
    explicit unique_pointer(T *up) : ptr(up) { }

    unique_pointer(unique_pointer &&up) noexcept : ptr(up.ptr) { up.ptr = nullptr; }
    unique_pointer &operator=(unique_pointer &&up) noexcept;

    unique_pointer &operator=(std::nullptr_t n) noexcept;

    T &operator*() const { return *ptr; }
    T *operator->() const { return &this->operator*(); }
    operator bool() const { return ptr ? true : false; }

    T *get() const noexcept { return ptr; }

    void swap(unique_pointer<T, D> &rhs) { ::swap(*this, rhs); }

    void reset() noexcept { deleter(ptr); ptr = nullptr; }
    void reset(T *p) noexcept { deleter(ptr); ptr = p; }

    T *release();

    ~unique_pointer()
    {
        deleter(ptr);
    }
private:
    T *ptr = nullptr;
    D deleter = D();
};

template<typename T, typename D>
inline void swap(unique_pointer<T, D> &lhs, unique_pointer<T, D> &rhs)
{
    using std::swap;
    swap(lhs.ptr, rhs.ptr);
    swap(lhs.deleter, rhs.deleter);
}

template <typename T, typename D>
inline unique_pointer<T, D> &unique_pointer<T, D>::operator=(unique_pointer &&rhs) noexcept
{
    if(this->ptr != rhs.ptr)
    {
        deleter(ptr);
        ptr = nullptr;
        ::swap(*this, rhs);
    }
    return *this;
}

template <typename T, typename D>
inline unique_pointer<T, D> &unique_pointer<T, D>::operator=(std::nullptr_t n) noexcept
{
    if(n == nullptr)
    {
        deleter(ptr);
        ptr = nullptr;
    }
    return *this;
}

template <typename T, typename D>
inline T *unique_pointer<T, D>::release()
{
    T *ret = ptr;
    ptr = nullptr;
    return ret;
}

#endif
```
  
## 练习16.29

> 修改你的 Blob 类，用你自己的 shared_ptr 代替标准库中的版本。

```cpp
#ifndef BLOB_H_
#define BLOB_H_

#include <vector>
#include <memory>
#include "shared_pointer.h"

template <typename T>
class Blob
{
public:
    // template <typename It>
    // Blob(It begin, It end) : data(std::make_shared<std::vector<T>>(begin, end)) { }
    template <typename It>
    Blob(It begin, It end);
private:
    cp5::shared_pointer<std::vector<T>> data;
};

template <typename T>
template <typename It>
Blob<T>::Blob(It begin, It end) : data(std::make_shared<std::vector<T>>(begin, end)) { }

#endif
```
  
## 练习16.30

> 重新运行你的一些程序，验证你的 shared_ptr 类和修改后的 Blob 类。（注意：实现 weak_ptr 类型超出了本书范围，因此你不能将BlobPtr类与你修改后的Blob一起使用。）

程序详见16.29，可以成功运行。  
  
## 练习16.31

> 如果我们将 DebugDelete 与 unique_ptr 一起使用，解释编译器将删除器处理为内联形式的可能方式。

unique_ptr将DebugDelete设置为默认删除器，编译时将执行DebugDelete。  
  
## 练习16.32

> 在模版实参推断过程中发生了什么？

在模板实参推断过程中，编译器使用函数调用中的实参类型来寻找模板实参，用这些模板实参生成的函数版本与给定的函数调用最为匹配。  
  
## 练习16.33

> 指出在模版实参推断过程中允许对函数实参进行的两种类型转换。

const转换：可以将一个非const对象的引用（或指针）传递给一个const的引用（或指针）形参。  
数组或函数指针转换：如果函数形参不是引用类型，则可以对数组或函数类型的实参应用正常的指针转换。一个数组实参可以转换为一个指向其首元素的指针。类似的，一个函数实参可以转换为一个该函数类型的指针。  
  
## 练习16.34

> 对下面的代码解释每个调用是否合法。如果合法，T 的类型是什么？如果不合法，为什么？
```cpp
template <class T> int compare(const T&, const T&);
(a) compare("hi", "world");
(b) compare("bye", "dad");
```

（a）不合法，const char ()[3]和const char ()[6]；  
（b）合法，const char ()[4]和const char ()[4]。  
  
## 练习16.35

> 下面调用中哪些是错误的（如果有的话）？如果调用合法，T 的类型是什么？如果调用不合法，问题何在？
```cpp
template <typename T> T calc(T, int);
tempalte <typename T> T fcn(T, T);
double d; float f; char c;
(a) calc(c, 'c'); 
(b) calc(d, f);
(c) fcn(c, 'c');
(d) fcn(d, f);
```

注意此处为单引号：  
（a）合法，T为char；  
（b）合法，T为double；  
（c）合法，T为char；  
（d）不合法，无法确定T的类型为double还是float。  
  
## 练习16.36

> 进行下面的调用会发生什么：
```cpp
template <typename T> f1(T, T);
template <typename T1, typename T2) f2(T1, T2);
int i = 0, j = 42, *p1 = &i, *p2 = &j;
const int *cp1 = &i, *cp2 = &j;
(a) f1(p1, p2);
(b) f2(p1, p2);
(c) f1(cp1, cp2);
(d) f2(cp1, cp2);
(e) f1(p1, cp1);
(f) f2(p1, cp1);
```

题目中没有函数没有返回类型，我们认为是void，typename T2后")"替换为">"：  
（a）f1(int*, int*)；  
（b）f2(int*, int*)；  
（c）f1(const int*, const int*)；  
（d）f2(const int*, const int*)；  
（e）出错；  
（f）f2(int*, const int*)。  
  
## 练习16.37

> 标准库 max 函数有两个参数，它返回实参中的较大者。此函数有一个模版类型参数。你能在调用 max 时传递给它一个 int 和一个 double 吗？如果可以，如何做？如果不可以，为什么？

可以，使用指定模板实参。  
```cpp
int a = 1;
double b = 2.0;
max<double>(a, b);
```
  
## 练习16.38

> 当我们调用 make_shared 时，必须提供一个显示模版实参。解释为什么需要显式模版实参以及它是如果使用的。

规定返回类型，推断需要分配多大空间。  
  
## 练习16.39

> 对16.1.1节 中的原始版本的 compare 函数，使用一个显式模版实参，使得可以向函数传递两个字符串字面量。

```cpp
compare<std::string>("a", "bb");
```
  
## 练习16.40

> 下面的函数是否合法？如果不合法，为什么？如果合法，对可以传递的实参类型有什么限制（如果有的话）？返回类型是什么？
```cpp
template <typename It>
auto fcn3(It beg, It end) -> decltype(*beg + 0)
{
	//处理序列
	return *beg;
}
```

合法，传递的实参必须支持+0操作，返回类型由+操作的返回类型决定。  
  
## 练习16.41

> 编写一个新的 sum 版本，它返回类型保证足够大，足以容纳加法结果。

下述代码应该有问题：
```cpp
#include <iostream>

template <typename T>
auto sum(T lhs, T rhs) -> decltype(lhs + rhs)
{
    return lhs + rhs;
}

int main()
{
    auto s = sum(123456789123456789123456789123456789123456789, 123456789123456789123456789123456789123456789);
    // std::cout << s << std::endl;
    return 0;
}
```
  
## 练习16.42

> 对下面每个调用，确定 T 和 val 的类型：
```cpp
template <typename T> void g(T&& val);
int i = 0; const int ci = i;
(a) g(i);
(b) g(ci);
(c) g(i * ci);
```

（a）T为int&，val为int& && -> int&；  
（b）T为const int&，val为const int& && -> const int&；  
（c）T为int，val为int&&。  
  
## 练习16.43

> 使用上一题定义的函数，如果我们调用g(i = ci),g 的模版参数将是什么？

int&  
  
## 练习16.44

> 使用与第一题中相同的三个调用，如果 g 的函数参数声明为 T（而不是T&&），确定T的类型。如果g的函数参数是 const T&呢？

T：  
（a）int；  
（b）int；  
（c）int。  
  
const T&：  
（a）int；  
（b）int；  
（c）int。  
  
## 练习16.45

> 如果下面的模版，如果我们对一个像42这样的字面常量调用g，解释会发生什么？如果我们对一个int 类型的变量调用g 呢？
```cpp
template <typename T> void g(T&& val) { vector<T> v; }
```

42，T为int，val为int&&，vector<int> v；  
int，T为int&，val为int& && -> int&，vector<int&> v，无法对int&进行内存分配，会报错。  
  
## 练习16.46

> 解释下面的循环，它来自13.5节中的 StrVec::reallocate:
```cpp
for (size_t i = 0; i != size(); ++i)
	alloc.construct(dest++, std::move(*elem++));
```

从C++11开始，std::allocator::construct的第二个参数为 Args&&... args，*elem++会返回一个左值，需要我们自行转换为右值。  
  
## 练习16.47

> 编写你自己版本的翻转函数，通过调用接受左值和右值引用参数的函数来测试它。

```cpp
#include <iostream>
#include <memory>

void func_lvalue(std::string &lhs, std::string &rhs)
{
    lhs = "Wang\n";
    rhs = "Alan\n";
}

void func_rvalue(int &&lhs, int &&rhs)
{
    //allocte encough space
    std::allocator<int> alloc;
    int *data(alloc.allocate(3));

    //move into the spaced newly allocated
    alloc.construct(data, lhs);
    alloc.construct(data + 1, 0);
    alloc.construct(data + 2, rhs);

    //print
    for(auto p = data; p != data + 3; ++p)
        std::cout << *p << "\n";

    //destroy and deallocation
    for(auto p = data + 3; p != data; )
        alloc.destroy(--p);
    alloc.deallocate(data, 3);
}

template <typename F, typename T1, typename T2>
void flip(F f, T1 &&t1, T2 &&t2)
{
    f(std::forward<T2>(t2), std::forward<T1>(t1));
}

int main()
{
    //test for lvalue reference
    std::string s1, s2;
    flip(func_lvalue, s1, s2);
    std::cout << s1 << s2;

    //test for rvalue reference
    flip(func_rvalue, 99, 88);

    return 0;
}
```
  
## 练习16.48

> 编写你自己版本的 debug_rep 函数。

```cpp
#include <iostream>
#include <memory>
#include <sstream>

template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);
std::string debug_rep(const std::string &s);
std::string debug_rep(char *p);
std::string debug_rep(const char *p);

template <typename T>
std::string debug_rep(const T &t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
std::string debug_rep(T *p)
{
    std::ostringstream ret;
    ret << "pointer: " << p;

    if(p)
        ret << " " << debug_rep(*p);
    else
        ret << " null pointer";
    return ret.str();
}

std::string debug_rep(const std::string &s)
{
    return '"' + s + '"';
}

std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}

std::string debug_rep(const char *p)
{
    std::cout << "debug_rep(const char *p)" << std::endl;
    return debug_rep(std::string(p));
}

int main()
{
    char ca[] = {'a', 'b', 'c', '\0'};
    std::cout << debug_rep(ca) << std::endl;

    return 0;
}
```
  
## 练习16.49

> 解释下面每个调用会发生什么：
```cpp
template <typename T> void f(T);
tempalte <typename T> void f(const T*);
tempalte <typename T> void g(T);
tempalte <typename T> void g(T*);
int i = 42, *p = &i;
const int ci = 0, *p2 = &ci;
g(42); g(p); g(ci); g(p2);
f(42); f(p); f(ci); f(p2);
```

g(42) g(T)；g(p) g(T*)；g(ci) g(int) g(T)；g(p2)->g(const int*) g(T*)；  
f(42) f(T)；f(p) f(T)；f(ci) f(T)；f(p2) f(const T*)。  
  
## 练习16.50

> 定义上一个练习中的函数，令它们打印一条身份信息。运行该练习中的代码。如果函数调用的行为与你预期不符，确定你理解了原因。

```cpp
#include <iostream>

template <typename T>
void f(T t)
{
    std::cout << "template <typename T> void f(T t)" << std::endl;
}

template <typename T>
void f(const T *t)
{
    std::cout << "template <typename T> void f(const T *t)" << std::endl;
}

template <typename T>
void g(T t)
{
    std::cout << "template <typename T> void g(T t)" << std::endl;
}

template <typename T>
void g(T *t)
{
    std::cout << "template <typename T> void g(T *t)" << std::endl;
}

int main()
{
    int i = 42, *p = &i;
    const int ci = 0, *p2 = &ci;

    g(42);
    g(p);
    g(ci);
    g(p2);

    f(42);
    f(p);
    f(ci);
    f(p2);

    return 0;
}
```
```sh
$ ./ex50 
template <typename T> void g(T t)
template <typename T> void g(T *t)
template <typename T> void g(T t)
template <typename T> void g(T *t)
template <typename T> void f(T t)
template <typename T> void f(T t)
template <typename T> void f(T t)
template <typename T> void f(const T *t)
```
  
## 练习16.51

> 调用本节中的每个 foo，确定 sizeof...(Args) 和 sizeof...(rest)分别返回什么。

foo(i, s, 42, d);
3 3
  
foo(s, 42, "hi");
2 2
  
foo(d, s);
1 1
  
foo("hi");
0 0
  
## 练习16.52

> 编写一个程序验证上一题的答案。

```cpp
#include <iostream>

template <typename T, typename... Args>
void foo(const T &t, const Args& ... rest)
{
    std::cout << sizeof...(Args) << std::endl;
    std::cout << sizeof...(rest) << std::endl;
}

int main()
{
    int i = 0;
    double d = 3.14;
    std::string s = "how now brown cow";
    
    foo(i, s, 42, d);
    foo(s, 42, "hi");
    foo(d, s);
    foo("hi");

    return 0;
}
```
  
## 练习16.53

> 编写你自己版本的 print 函数，并打印一个、两个及五个实参来测试它，要打印的每个实参都应有不同的类型。 

```cpp
#include <iostream>
#include <string>

template <typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    os << t;
}

template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";
    return print(os, rest...);
}

int main()
{
    int i = 1, *p = &i;
    double d = 0.1;
    std::string s = "abc";

    print(std::cout, i);
    std::cout << std::endl;
    print(std::cout, i, d);
    std::cout << std::endl;
    print(std::cout, i, d, s, p, "ccc");
    std::cout << std::endl;

    return 0;
}
```
  
## 练习16.54

> 如果我们对一个没 << 运算符的类型调用 print，会发生什么？

会编译报错。
  
## 练习16.55

> 如果我们的可变参数版本 print 的定义之后声明非可变参数版本，解释可变参数的版本会如何执行。

编译报错：error: no matching function for call to ‘print(std::ostream&)’。  
  
## 练习16.56

> 编写并测试可变参数版本的 errorMsg。

```cpp
#include <iostream>
#include <memory>
#include <sstream>

template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);
std::string debug_rep(const std::string &s);
std::string debug_rep(char *p);
std::string debug_rep(const char *p);

template <typename T>
std::string debug_rep(const T &t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
std::string debug_rep(T *p)
{
    std::ostringstream ret;
    ret << "pointer: " << p;

    if(p)
        ret << " " << debug_rep(*p);
    else
        ret << " null pointer";
    return ret.str();
}

std::string debug_rep(const std::string &s)
{
    return '"' + s + '"';
}

std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}

std::string debug_rep(const char *p)
{
    std::cout << "debug_rep(const char *p)" << std::endl;
    return debug_rep(std::string(p));
}

template <typename T>
std::ostream &print(std::ostream &os, const T &t)
{
    os << t;
}

template <typename T, typename... Args>
std::ostream &print(std::ostream &os, const T &t, const Args&... rest)
{
    os << t << ", ";
    return print(os, rest...);
}

template <typename... Args>
std::ostream &errorMsg(std::ostream &os, const Args&... rest)
{
    return print(os, debug_rep(rest)...);
}

int main()
{
    std::string s = "bb";

    errorMsg(std::cout, 1, 2, "a", s) << std::endl;

    return 0;
}
```
  
## 练习16.57

> 比较你的可变参数版本的 errorMsg 和6.2.6节中的 error_msg函数。两种方法的优点和缺点各是什么？

error_msg函数中使用initializer_list，initializer_list只能接受相同类型（或它们的类型可以转换为同一个公共类型）的可变数目实参的函数；而errorMsg函数可以接受不同类型的可变数目实参，更加灵活。  
  
## 练习16.58

> 为你的 StrVec 类及你为16.1.2节练习中编写的 Vec 类添加 emplace_back 函数。

StrVec.h
```cpp
#ifndef STRVEC_H_
#define STRVEC_H_

#include <string>
#include <utility>
#include <memory>
#include <algorithm>

class StrVec
{
friend bool operator==(StrVec &lhs, StrVec &rhs);
friend bool operator!=(StrVec &lhs, StrVec &rhs);
friend bool operator<(StrVec &lhs, StrVec &rhs);
friend bool operator>(StrVec &lhs, StrVec &rhs);
friend bool operator<=(StrVec &lhs, StrVec &rhs);
friend bool operator>=(StrVec &lhs, StrVec &rhs);
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) { }
    StrVec(std::initializer_list<std::string>);
    StrVec(const StrVec&);
    StrVec(StrVec &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free)), cap(std::move(s.cap)) { s.elements = s.first_free = s.cap = nullptr; }
    template <typename... Args>
    void emplace_back(Args&&... args);
    StrVec &operator=(const StrVec&);
    StrVec &operator=(StrVec&&) noexcept;
    std::string& operator[](std::size_t n) { return elements[n]; }
    const std::string& operator[](std::size_t n) const { return elements[n]; }
    ~StrVec();
    void push_back(const std::string&);
    size_t size() const { return first_free - elements; }
    size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    void reserve(size_t n);
    void resize(size_t n);
    void resize(size_t n, const std::string &s);
private:
    std::allocator<std::string> alloc;
    void chk_n_alloc() { if(size() == capacity()) reallocate(); }
    std::pair<std::string*, std::string*> alloc_n_copy(const std::string*, const std::string*);
    void free();
    void reallocate();
    std::string *elements;
    std::string *first_free;
    std::string *cap;
};

StrVec::StrVec(std::initializer_list<std::string> il)
{
    auto newdata = alloc_n_copy(il.begin(), il.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

template <typename... Args>
inline void StrVec::emplace_back(Args&&... args)
{
    chk_n_alloc();
    alloc.construct(first_free++, std::forward<Args>(args)...);
}

void StrVec::push_back(const std::string &s)
{
    chk_n_alloc();
    alloc.construct(first_free++, s);
}

std::pair<std::string*,std::string*> StrVec::alloc_n_copy(const std::string *b, const std::string *e)
{
    auto data = alloc.allocate(e-b);
    return {data, uninitialized_copy(b, e, data)};
}

void StrVec::free()
{
    if(elements)
    {
        std::for_each(elements, first_free, [this](std::string &p){ alloc.destroy(&p); });
        // for(auto p = first_free; p != elements; )
        //  alloc.destroy(--p);
        alloc.deallocate(elements, cap-elements);
    }
}

StrVec::StrVec(const StrVec &s)
{
    auto newdata = alloc_n_copy(s.begin(), s.end());
    elements = newdata.first;
    first_free = cap = newdata.second;
}

StrVec::~StrVec()
{
    free();
}

void StrVec::reserve(size_t n)
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

void StrVec::resize(size_t n)
{
    resize(n,std::string());
}

void StrVec::resize(size_t n, const std::string &s)
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

StrVec &StrVec::operator=(const StrVec &rhs)
{
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

StrVec &StrVec::operator=(StrVec &&rhs) noexcept
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

void StrVec::reallocate()
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

bool operator==(StrVec &lhs, StrVec &rhs)
{
    return lhs.size() == rhs.size() && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(StrVec &lhs, StrVec &rhs)
{
    return !(lhs == rhs);
}

bool operator<(StrVec &lhs, StrVec &rhs)
{
    return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

bool operator>(StrVec &lhs, StrVec &rhs)
{
    return rhs < lhs;
}

bool operator<=(StrVec &lhs, StrVec &rhs)
{
    return !(rhs < lhs);
}

bool operator>=(StrVec &lhs, StrVec &rhs)
{
    return !(lhs < rhs);
}

#endif
```
  
Vec.h
```cpp
#include "StrVec.h"
#include "Vec.h"

int main()
{
    StrVec s;
    s.emplace_back("a");
    // s.emplace_back("bb", "ccc"); //error

    Vec<std::string> Vs;
    Vs.emplace_back("a");

    return 0;
}
```
  
ex58.cpp
```cpp
#include "StrVec.h"
#include "Vec.h"

int main()
{
    StrVec s;
    s.emplace_back("a");
    // s.emplace_back("bb", "ccc"); //error

    Vec<std::string> Vs;
    Vs.emplace_back("a");

    return 0;
}
```
  
## 练习16.59

> 假定 s 是一个 string，解释调用 svec.emplace_back(s)会发生什么。

会在 construst 函数中转发扩展包。  
  
## 练习16.60

> 解释 make_shared 是如何工作的。

make_shared 是一个可变模版函数，它将参数包转发然后构造一个对象，再然后一个指向该对象的智能指针。  
  
## 练习16.61

> 定义你自己版本的 make_shared。

```cpp
#include <memory>
#include <iostream>

namespace ch16{
    template <typename T, typename... Args>
    std::shared_ptr<T> make_shared(Args&&... args)
    {
        return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
    }
}

int main()
{
    auto sp1 = ch16::make_shared<int>(1);
    std::cout << *sp1 << std::endl;

    auto str = ch16::make_shared<std::string>(10, 'c');
    std::cout << *str << std::endl;

    return 0;
}
```
  
## 练习16.62

> 定义你自己版本的 hash<Sales_data>, 并定义一个 Sales_data 对象的 unorder_multise。将多条交易记录保存到容器中，并打印其内容。

Sales_data.h
```cpp
#ifndef SALES_DATA_H_
#define SALES_DATA_H_

#include <string>

struct Sales_data;

std::istream &operator>>(std::istream &is, Sales_data &item);
std::ostream &operator<<(std::ostream &os, const Sales_data &item);
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs);

struct Sales_data
{
friend std::istream& operator>>(std::istream&, Sales_data&);
friend std::ostream& operator<<(std::ostream&, const Sales_data&);
friend Sales_data operator+(const Sales_data&, const Sales_data&);
friend bool operator==(const Sales_data&, const Sales_data&);
friend class std::hash<Sales_data>;
public:
    Sales_data(const std::string &s, unsigned n, double p) : bookNo(s), units_sold(n), revenue(p*n){std::cout << "Sales_data(const std::string &s, unsigned n, double p)" << std::endl;}
    Sales_data() : Sales_data("", 0, 0){std::cout << "Sales_data() : Sales_data(\"\", 0, 0)" << std::endl;}
    Sales_data(const std::string &s) : Sales_data(s, 0, 0){std::cout << "Sales_data(const std::string &s) : Sales_data" << std::endl;}
    Sales_data(std::istream &is) : Sales_data(){/*read(is, *this);*/ is >> *this; std::cout << "Sales_data(std::istream &is) : Sales_data()" << std::endl;}
    std::string isbn() const {return bookNo;}
    Sales_data& operator=(const std::string&);
    Sales_data& operator+=(const Sales_data&);
    Sales_data& operator-=(const Sales_data&);
private:
    inline double avg_price() const;

    std::string bookNo;
    unsigned units_sold = 0;
    double revenue = 0.0;
};

inline double Sales_data::avg_price() const
{
    if(units_sold)
        return revenue / units_sold;
    else
        return 0;
}

Sales_data& Sales_data::operator=(const std::string &s)
{
    *this = Sales_data(s);
    return *this;
}

Sales_data& Sales_data::operator+=(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;

    return *this;
}

Sales_data& Sales_data::operator-=(const Sales_data &rhs)
{
    units_sold -= rhs.units_sold;
    revenue -= rhs.revenue;

    return *this;
}

std::istream &operator>>(std::istream &is, Sales_data &item)
{
    double price = 0;

    is >> item.bookNo >> item.units_sold >> price;
    if(is)
        item.revenue = price * item.units_sold;
    else
        item = Sales_data();

    return is;
}

std::ostream &operator<<(std::ostream &os, const Sales_data &item)
{
    os << item.isbn() << " " << item.units_sold << " " << item.revenue << " " << item.avg_price();

    return os;
}

Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum += rhs;

    return sum;
}

bool operator==(const Sales_data &lhs, const Sales_data &rhs)
{
    return lhs.isbn() == rhs.isbn() && 
        lhs.units_sold == rhs.units_sold && 
        lhs.revenue == rhs.revenue;
}

#endif
```
  
ex62.cpp
```cpp
#include <iostream>
#include <string>
#include "Sales_data.h"
#include <unordered_set>

namespace std
{
    template <>
    struct hash<Sales_data>
    {
        typedef size_t result_type;
        typedef Sales_data argument_type;
        size_t operator()(const Sales_data &s) const;
    };
    size_t hash<Sales_data>::operator()(const Sales_data &s) const
    {
        return hash<std::string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
    }
}

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2;
    Sales_data sales_data3("001-02");
    // Sales_data sales_data4(std::cin);
    // std::cout << sales_data4 << std::endl;
    std::cout << std::hex << std::hash<std::string>()("001-01") << std::endl;
    std::cout << std::hex << std::hash<unsigned>()(1) << std::endl;
    std::cout << std::hex << std::hash<double>()(100) << std::endl;

    std::unordered_multiset<Sales_data> SDset;
    SDset.emplace(sales_data1);
    SDset.emplace("001-03", 1, 200);
    SDset.emplace(sales_data3);

    for(const auto &item : SDset)
        std::cout << "the hash code of " << item.isbn() <<":\n0x" << std::hex << std::hash<Sales_data>()(item) << "\n";

    return 0;
}
```
  
## 练习16.63

> 定义一个函数模版，统计一个给定值在一个vecor中出现的次数。测试你的函数，分别传递给它一个double的vector，一个int的vector以及一个string的vector。

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
size_t get_number(T t, std::vector<T> const &vt)
{
    size_t n = 0;
    auto iter = vt.begin();

    do{
        iter = std::find(iter, vt.end(), t);
        if(iter != vt.end())
        {
            ++n;
            ++iter;
        }
    }while(iter != vt.end());
    return n;
}

size_t get_number(const char* p, const std::vector<std::string> &vt)
{
    size_t n = 0;
    auto iter = vt.begin();
    std::string s(p);

    do{
        iter = std::find(iter, vt.end(), s);
        if(iter != vt.end())
        {
            ++n;
            ++iter;
        }
    }while(iter != vt.end());
    return n;
}

template <>
size_t get_number(const char* t, std::vector<const char*> const &vt)
{
    size_t n = 0;
    auto iter = vt.begin();

    do{
        iter = std::find(iter, vt.end(), t);
        if(iter != vt.end())
        {
            ++n;
            ++iter;
        }
    }while(iter != vt.end());
    return n;
}

int main()
{
    std::vector<double> vd = {1, 2, 3, 3.14, 4, 3.14, 5, 6.28};
    std::vector<int> vi = {1, 2, 3, 3, 4, 3, 5, 6};
    std::vector<std::string> vs = {"a", "bb", "ccc", "dddd"};
    std::vector<const char*> vcp = {"a", "bb", "ccc", "dddd"};

    std::cout << get_number(3.14, vd) << std::endl;
    std::cout << get_number(3, vi) << std::endl;
    std::cout << get_number("a", vs) << std::endl;
    std::cout << get_number("a", vcp) << std::endl;

    return 0;
}
```
  
## 练习16.64

> 为上一题的模版编写特例化版本来处理vector<const char*>。编写程序使用这个特例化版本。

详见１6.63。
  
## 练习16.65

> 在16.3节中我们定义了两个重载的 debug_rep 版本，一个接受 const char* 参数，另一个接受 char * 参数。将这两个函数重写为特例化版本。

```cpp
#include <iostream>
#include <memory>
#include <sstream>

template <typename T> std::string debug_rep(const T &t);
template <typename T> std::string debug_rep(T *p);
std::string debug_rep(const std::string &s);

template <typename T>
std::string debug_rep(const T &t)
{
    std::ostringstream ret;
    ret << t;
    return ret.str();
}

template <typename T>
std::string debug_rep(T *p)
{
    std::ostringstream ret;
    ret << "pointer: " << p;

    if(p)
        ret << " " << debug_rep(*p);
    else
        ret << " null pointer";
    return ret.str();
}

std::string debug_rep(const std::string &s)
{
    return '"' + s + '"';
}

template <>
std::string debug_rep(char *p)
{
    return debug_rep(std::string(p));
}

template <>
std::string debug_rep(const char *p)
{
    std::cout << "debug_rep(const char *p)" << std::endl;
    return debug_rep(std::string(p));
}

int main()
{
    char ca[] = {'a', 'b', 'c', '\0'};
    std::cout << debug_rep(ca) << std::endl;

    return 0;
}
```
  
## 练习16.66

> 重载debug_rep 函数与特例化它相比，有何优点和缺点？

会改变函数匹配顺序，几个函数都提供同样好的匹配的情况下，编译器会选择非模板版本。  
  
## 练习16.67

> 定义特例化版本会影响 debug_rep 的函数匹配吗？如果不影响，为什么？

不会改变，特例化模板函数不会重载函数，不会影响函数匹配顺序。  

