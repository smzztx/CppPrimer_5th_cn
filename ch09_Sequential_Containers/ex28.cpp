#include <iostream>
#include <forward_list>

using namespace std;

void insert_string(forward_list<string> &flst, const string &find_str, const string &insert_str)
{
	auto prev = flst.before_begin();
	auto curr = flst.begin();

	while(curr != flst.end())
	{
		if(*curr == find_str)
		{
			flst.insert_after(curr, insert_str);
			return;
		}
		else
		{
			prev = curr;
			++curr;
		}
	}
	flst.insert_after(prev, insert_str);
}

int main()
{
	forward_list<string> flst = {"aa", "bb", "cc", "dd"};

	insert_string(flst, "aaa", "bilibili");

	for(const auto s : flst)
		cout << s << " ";
	cout << endl;

	return 0;
}