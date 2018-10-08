#include "HasPtr_ex31.h"
#include <vector>
#include <algorithm>

int main()
{
	HasPtr hp1("aaa"),hp2("bbb");
	std::vector<HasPtr> vh{hp1, hp2};
	std::sort(vh.begin(), vh.end());

	return 0;
}