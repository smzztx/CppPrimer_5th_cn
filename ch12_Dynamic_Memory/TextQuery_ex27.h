#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_

#include <string>
#include <vector>
#include <map>

class TextQuery
{
public:
	void get_line_num()
	{
		find_if(word_line.begin(), word_line.end(), )
	}
private:
	std::vector<map<std::string, size_t>> word_line;
	std::set<size_t> line_num;
}

void TextQuery::get_line_num(std::string s)
{
	for(auto iter = word_line.begin(), end = word_line.end(); iter != end; )
	{
		auto iter = find_if(iter, end, [](const map<std::string, size_t> m){ return m.first == s; })
	}
}

#endif