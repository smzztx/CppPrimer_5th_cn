#include <memory>
#include <iostream>

int main()
{
	std::unique_ptr<int> up1(new int(1));
	// std::unique_ptr<int> up2(up1);
	// std::unique_ptr<int> up2 = up1;
	std::unique_ptr<int> up2;
	up2.reset(up1.release());
	std::cout << *up2 << std::endl;

	return 0;
}