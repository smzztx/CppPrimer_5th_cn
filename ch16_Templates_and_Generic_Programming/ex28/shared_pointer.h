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