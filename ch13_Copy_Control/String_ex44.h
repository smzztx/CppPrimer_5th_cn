#include <memory>
#include <algorithm>

class String
{
public:
	String();
	String(char*);
	~String();
private:
	std::allocator<char> alloc;
	void chk_n_alloc() { if(size() == capacity()) reallocate(); }
	std::pair<char*, char*> alloc_n_copy(const char*, const char*);
	void free();
	void reallocate();
	char *elements;
	char *first_free;
};

String::String()
{
	char* p = alloc.allocate(1);
	alloc.construct(p, '\0');
}

String::String(char* cp)
{
	size_t n = strlen(cp) + 1;
	char* p = alloc.allocate(n);

	for(int i = 0; i < n; ++i)
		alloc.construct(p+i, *(cp+i));
	// std::for_each(cp, cp+n, [](char c){ allocate.construct(p, c); })
}

String::~String()
{
	
}