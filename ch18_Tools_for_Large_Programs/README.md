## 18.1
（a）range_error；  
（b）exception。  
throw p，此时抛出的为指向局部对象的指针，我们几乎可以肯定这是一种错误行为。  
  
## 18.2
p的内存将不会被释放，会出现内存泄漏。  
  
## 18.3
使用shared_ptr；自己写个类来实现。  
```cpp
std::shared_ptr<int> p(new int[v.size()], [](int *p) {delete p});
```
```cpp
struct P {
	int *p = nullptr;
	P(std::size_t n):p(new int[n]){}
	~P()
	{
		delete []p;
	}
};
```
  
## 18.4
应该把继承链最底端的类放在前面，而将继承链最顶端的类放在后面。  
```cpp
try{
	//使用C++标准库
}catch(overflow_error eobj){
	//...
}catch(const runtime_error &re){
	//...
}catch(exception){
	//...
}
```
  
## 18.5
```cpp
#include <exception>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <typeinfo>

using namespace std;

int main()
{
	try{
		//使用C++标准库
	}catch(bad_cast &r){
		cout << r.what();
		abort();
	}catch(range_error &r){
		cout << r.what();
		abort();
	}catch(underflow_error &r){
		cout << r.what();
		abort();
	}catch(overflow_error &r){
		cout << r.what();
		abort();
	}catch(runtime_error &r){
		cout << r.what();
		abort();
	}catch(length_error &r){
		cout << r.what();
		abort();
	}catch(out_of_range &r){
		cout << r.what();
		abort();
	}catch(invalid_argument &r){
		cout << r.what();
		abort();
	}catch(domain_error &r){
		cout << r.what();
		abort();
	}catch(logic_error &r){
		cout << r.what();
		abort();
	}catch(bad_alloc &r){
		cout << r.what();
		abort();
	}catch(exception &r){
		cout << r.what();
		abort();
	}

	return 0;
}
```
  
## 18.6
（a）
```cpp
exceptionType *pet;
//...
throw pet;
```
（b）
 可以捕获所有的异常。  
（c）
```cpp
int a;
//...
throw a;
```
  
## 18.7
```cpp
template <typename T>
Blob<T>::Blob()try :data(std::make_shared<vector<T>()>) {}
catch(const std::bad_alloc &e){
	handle_out_of_memory(e);
}
template<typename T>
Blob<T>::Blob(std::initializer_list<T> il) try :data(make_shared<vector<T>>(il)) {}
catch(const std::bad_alloc &e){
	handle_out_of_memory(e);
}
```
```cpp
template <typename T>
BlobPtr<T>::BlobPtr()try:curr(0){}
catch (const std::bad_alloc& e) {
	handle_out_of_memory(e);
}
template <typename T>
BlobPtr<T>::BlobPtr(Blob<T> &a, size_t sz = 0)try : wptr(a.data), curr(sz) {}
catch (const std::bad_alloc& e) {
	handle_out_of_momory(e);
}
```
  
## 18.8
略。  
  
## 18.9

