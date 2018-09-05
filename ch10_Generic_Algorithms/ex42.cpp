#include <iostream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

list<string> &elimDups(list<string> &words)
{
	// sort(words.begin(), words.end());
	words.sort();
	words.unique();
	// auto end_unique = unique(words.begin(), words.end());
	// words.erase(end_unique, words.end());
	return words;
}

int main()
{
	list<string> vs = {"d","c","b","a","a","c","e"};

	for(const auto s : elimDups(vs))
		cout << s << " ";
	cout << endl;

	return 0;
}