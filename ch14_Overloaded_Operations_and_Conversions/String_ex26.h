#ifndef STRING_H_
#define STRING_H_

#include <memory>
#include <algorithm>
#include <cstring>
#include <iostream>

class String
{
friend std::ostream &operator<<(std::ostream &os, const String &s);
friend bool operator==(const String lhs, const String rhs);
friend bool operator!=(const String lhs, const String rhs);
friend bool operator<(const String lhs, const String rhs);
friend bool operator>(const String lhs, const String rhs);
friend bool operator<=(const String lhs, const String rhs);
friend bool operator>=(const String lhs, const String rhs);
public:
	String();
	String(const char*);
	String(const String&);
	String(String&&) noexcept;
	String& operator=(const String&);
	String& operator=(String&&) noexcept;
	char& operator[](size_t n) { return elements[n]; }
	const char& operator[](size_t n) const { return elements[n]; }
	char *begin() const { return elements; }
	char *end() const { return first_free; }
	~String();
private:
	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
	void free();

	std::allocator<char> alloc;
	char *elements;
	char *first_free;
};

std::pair<char*, char*> String::alloc_n_copy(const char *begin, const char *end)
{
	char *p = alloc.allocate(end - begin);
	return{p, std::uninitialized_copy(begin, end, p)};
}

String::String(const char* cp)
{
	size_t n = strlen(cp);
	auto newstr = alloc_n_copy(cp, cp + n);
	elements = newstr.first;
	first_free = newstr.second;
}

String::String()
{
	String("");
}

String::String(const String &rhs)
{
	auto newstr = alloc_n_copy(rhs.begin(), rhs.end());
	elements = newstr.first;
	first_free = newstr.second;
	std::cout << "String(const String &rhs)" << std::endl;
}

String::String(String &&s) noexcept : alloc(std::move(s.alloc)), elements(std::move(s.elements)), first_free(std::move(s.first_free))
{
	std::cout << "String::String(String &&s) noexcept" << std::endl;
	s.elements = s.first_free = nullptr;
}

void String::free()
{
	if(elements)
	{
		std::for_each(elements, first_free, [this](char cp){ alloc.destroy(&cp); });
		alloc.deallocate(elements, first_free - elements);
	}
}

String& String::operator=(const String& rhs)
{
	auto newstr = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = newstr.first;
	first_free = newstr.second;
	std::cout << "String& operator=(const String& rhs)" << std::endl;
	return *this;
}

String& String::operator=(String &&rhs) noexcept
{
	std::cout << "String& String::operator=(String &&rhs) noexcept" << std::endl;
	if(&rhs != this)
	{
		free();
		alloc = std::move(rhs.alloc);
		elements = std::move(rhs.elements);
		first_free = std::move(rhs.first_free);
		rhs.elements = rhs.first_free = nullptr;
	}
	return *this;
}

String::~String()
{
	free();
}

std::ostream &operator<<(std::ostream &os, const String &s)
{
	for(auto iter = s.elements; iter != s.first_free; ++iter)
	{
		os << *iter ;
	}
	return os;
}

bool operator==(const String lhs, const String rhs)
{
	return (lhs.first_free - lhs.elements) == (rhs.first_free - rhs.elements) && std::equal(lhs.begin(), lhs.end(), rhs.begin());
}

bool operator!=(const String lhs, const String rhs)
{
	return !(lhs == rhs);
}

bool operator<(const String lhs, const String rhs)
{
	return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), lhs.end());
}

bool operator>(const String lhs, const String rhs)
{
	return rhs < lhs;
}

bool operator<=(const String lhs, const String rhs)
{
	return !(rhs < lhs);
}

bool operator>=(const String lhs, const String rhs)
{
	return !(lhs < rhs);
}

#endif