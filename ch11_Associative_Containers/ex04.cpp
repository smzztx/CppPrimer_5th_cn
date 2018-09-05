#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

int main()
{
	map<string, size_t> word_count;
	string word;

	while(cin >> word)
	{
		word.erase(find_if(word.begin(), word.end(), ::ispunct), word.end());
		for_each(word.begin(), word.end(), [](char &c){ c=tolower(c); });
		++word_count[word];
	}

	for(const auto &w : word_count)
		cout << w.first << "," << w.second << endl;

	return 0;
}