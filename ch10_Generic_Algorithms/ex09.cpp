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

int main()
{
	vector<string> vs = {"d","c","b","a","a","c","e"};

	for(const auto s : elimDups(vs))
		cout << s << " ";
	cout << endl;

	return 0;
}