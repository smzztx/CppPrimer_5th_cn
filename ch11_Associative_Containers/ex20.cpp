#include <map>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	map<string, size_t> word_count;
	string word;
	while(cin >> word)
	{
		auto ret = word_count.insert({word, 1});
		if(!ret.second)
			++ret.first->second;
	}
		// ++word_count[word];

	for(const auto &w : word_count)
		cout << w.first << "," << w.second << endl;

	return 0;
}