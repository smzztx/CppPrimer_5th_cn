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

bool isShorter(const string &s1, const string &s2)
{
	return s1.size() < s2.size();
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa"};

	for(const auto s : elimDups(vs))
		cout << s << " ";
	cout << endl;

	stable_sort(vs.begin(), vs.end(), isShorter);

	for(const auto s : vs)
		cout << s << " ";
	cout << endl;

	return 0;
}