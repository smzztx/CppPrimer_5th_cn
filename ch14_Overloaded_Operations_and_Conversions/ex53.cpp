#include <cstddef>

class SmallInt
{
friend SmallInt operator+(const SmallInt &si1, const SmallInt &si2) { SmallInt si_sum(si1.val + si2.val); return si_sum; }
public:
	SmallInt(int i = 0) : val(i) {}
	operator int() const { return val; }
private:
	std::size_t val;
};

int main()
{
	SmallInt s1;
	// double d = s1 + 3.14;
	double d1 = s1 + SmallInt(3.14);
	double d2 = s1.operator int() + 3.14;

	return 0;
}