#include <memory>
#include <iostream>

namespace ch16{
	template <typename T, typename... Args>
	std::shared_ptr<T> make_shared(Args&&... args)
	{
		return std::shared_ptr<T>(new T(std::forward<Args>(args)...));
	}
}

int main()
{
	auto sp1 = ch16::make_shared<int>(1);
	std::cout << *sp1 << std::endl;

	auto str = ch16::make_shared<std::string>(10, 'c');
	std::cout << *str << std::endl;

	return 0;
}