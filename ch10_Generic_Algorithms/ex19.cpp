#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> &elimDups(vector<string> &words)
{
	sort(words.begin(), words.end());
	auto end_unique = unique(words.begin(), words.end());
	words.erase(end_unique, words.end());
	return words;
}

void biggies(vector<string> &words, vector<string>::size_type sz)
{
	elimDups(words);
	stable_sort(words.begin(), words.end(),
		[](const string &a, const string &b)
			{ return a.size() < b.size(); });
	auto wc = stable_partition(words.begin(), words.end(),
		[sz](const string &a)
			{ return a.size() >= sz; });
	auto count = wc - words.begin();
	cout << count << endl;
	for(const auto s : words)
		cout << s << " ";
	cout << endl;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	biggies(vs, 5);

	return 0;
}