#include <iostream>
#include <string>

class Employee
{
friend void print(const Employee&);
public:
	Employee() { id = n; ++n; };
	Employee(const std::string &s) { id = n; ++n; name = s; };
	Employee(const Employee&) = delete;
	Employee &operator=(const Employee&) = delete;
private:
	std::string name;
	int id;
	static int n;
};

void print(const Employee &e)
{
	std::cout << e.name << " " << e.id << std::endl;
}

int Employee::n = 0;

int main()
{
	Employee a;
	Employee b("bbb");

	print(a);
	print(b);

	return 0;
}