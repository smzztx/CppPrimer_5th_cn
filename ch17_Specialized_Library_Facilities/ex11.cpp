#include <bitset>

template <unsigned N>
class quiz
{
public:
	quiz(std::string &s) : bset(s) {}
	
private:
	std::bitset<N> bset;
};

int main()
{
	std::string s1("0101010101");
	std::string s2("0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
	quiz<10> q1(s1);
	quiz<100> q2(s2);

	return 0;
}