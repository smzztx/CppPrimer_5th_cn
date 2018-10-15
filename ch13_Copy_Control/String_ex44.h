#include <memory>

class String
{
public:
	String();
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