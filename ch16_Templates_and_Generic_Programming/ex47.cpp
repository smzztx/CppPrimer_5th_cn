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