#include "DebugDelete.h"

int main()
{
	DebugDelete d;
	int *p = new int;
	d(p);

	return 0;
}