#include "DebugDelete.h"
#include "TextQuery.h"

int main()
{
	// DebugDelete d;
	// int *p = new int;
	// d(p);
	std::ifstream file("../../ch12_Dynamic_Memory/storyDataFile");
    // runQueries(file);
    TextQuery t(file);

	return 0;
}