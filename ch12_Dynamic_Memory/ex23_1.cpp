#include <string>
#include <iostream>
#include <cstring>

int main()
{
	const char a[] = "aaa";
	const char b[] = "bbb";
	char *pca = new char[strlen("aaa" "bbb")+1];

	std::strcat(pca, a);
	std::strcat(pca, b);
	std::cout << std::string(pca) << std::endl;
	delete [] pca;

	return 0;
}