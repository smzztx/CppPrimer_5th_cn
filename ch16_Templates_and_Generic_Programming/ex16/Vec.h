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