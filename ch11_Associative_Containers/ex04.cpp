#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

// using namespace std;

int main()
{
	std::map<std::string, std::size_t> word_count;
	std::string word;

	while(std::cin >> word)
	{
		word.erase(std::find_if(word.begin(), word.end(), ispunct), word.end());
		for_each(word.begin(), word.end(), [](char &c){ c=std::tolower(c); });
		++word_count[word];
	}

	for(const auto &w : word_count)
		std::cout << w.first << "," << w.second << std::endl;

	return 0;
}