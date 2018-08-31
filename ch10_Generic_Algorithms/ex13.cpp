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

bool greater_than_5(const string &s)
{
	return s.size() >= 5;
}

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e","bb","aa","aaa","aaaaa"};

	auto iter = partition(vs.begin(), vs.end(), greater_than_5);
	for(const auto s : vs)
		cout << s << " ";
	cout << endl;

	vs.erase(iter, vs.end());
	for(const auto s : vs)
		cout << s << " ";
	cout << endl;

	return 0;
}