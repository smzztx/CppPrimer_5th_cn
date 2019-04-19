#include "Blob.h"
#include <vector>

int main()
{
	std::vector<int> vi = {1, 2, 3};
	Blob<int> b(vi.begin(), vi.end());

	return 0;
}