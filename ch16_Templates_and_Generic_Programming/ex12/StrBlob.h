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