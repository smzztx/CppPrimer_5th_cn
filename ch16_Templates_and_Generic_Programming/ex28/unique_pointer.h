#ifndef UNIQUE_POINTER_H
#define UNIQUE_POINTER_H

#include "DebugDelete.h"

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