#include <queue>
#include <iostream>

int main(void)
{
	std::queue<int> q1;

	for (int i = 0; i < 101; ++i)
	{
		q1.push(i);
		if(q1.size() > 4)
		{
			std::cout << q1.front() << " ";
			q1.pop();
		}
	}
	std::cout << std::endl;

	std::cout << q1.size() << std::endl;
	int count = q1.size();
	for (int i = 0; i < count; ++i)
	{
		std::cout << q1.front() << " ";
		q1.pop();
	}
	std::cout << std::endl;

	return 0;
}