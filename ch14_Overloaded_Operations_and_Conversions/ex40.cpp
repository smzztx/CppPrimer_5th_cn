#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class bigger
{
public:
	bigger(vector<string>::size_type i) : default_num(i) {};
	bool operator()(const std::string &s)
	{
		return s.size() >= default_num;
	}
private:
	vector<string>::size_type default_num;
};

class str_compare
{
public:
	bool operator()(const std::string &lhs, const std::string &rhs)
	{
		return lhs.size() < rhs.size();
	}	
};

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

		// [](const string &a, const string &b)
		// 	{ return a.size() < b.size(); }
void biggies(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(), str_compare());
	auto wc = find_if(words.begin(), words.end(), bigger(sz));
	auto count = words.end() - wc;
	cout << count << endl;
	for(const auto s : words)
		cout << s << " ";
	cout << endl;
}
// [sz](const string &a)
// 			{ return a.size() >= sz; }
int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	biggies(vs, 5);

	return 0;
}