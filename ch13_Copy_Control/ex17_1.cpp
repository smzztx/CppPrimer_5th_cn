#include <iostream>
#include <cstdlib>
#include <string>

class numbered
{
friend void f(numbered s);
public:
	numbered() : mysn(std::to_string(std::rand())) { };
	~numbered() { };
private:
	std::string mysn;
};

void f(numbered s)
{
	std::cout << s.mysn << std::endl;
}

int main()
{
	numbered a, b = a, c = b;
	f(a); f(b); f(c);

	return 0;
}