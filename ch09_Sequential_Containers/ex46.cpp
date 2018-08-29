#include <string>
#include <iostream>

using namespace std;

string add_pre_post(const string &name, const string &pre, const string &post)
{
	string s = name;
	s.insert(0, pre);
	return s.insert(s.size(), post);
}

int main()
{
	string name("tx");

	cout << add_pre_post(name, "Mr.", "Jr.") << endl;

	cout << add_pre_post("TX", "Mr.", "Jr.") << endl;

	return 0;
}