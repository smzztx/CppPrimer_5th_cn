#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "StrBlob.h"
#include "DebugDelete.h"
#include <tuple>

class QueryResult;

class TextQuery
{
public:
	using line_no = std::vector<std::string>::size_type;
	TextQuery(std::ifstream&);
	std::tuple<std::string, std::shared_ptr<std::set<TextQuery::line_no>>, StrBlob> query(const std::string&) const;
private:
	StrBlob file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> word_map;
};

class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, StrBlob f) : sought(s), lines(p), file(f) { }
	std::set<StrBlob::size_type>::iterator begin() const { return lines->begin(); }
	std::set<StrBlob::size_type>::iterator end() const { return lines->end(); }
	// std::shared_ptr<StrBlob> get_file() const { return std::make_shared<StrBlob>(file); }
	const StrBlob& get_file() const { return file; }
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	StrBlob file;
};

TextQuery::TextQuery(std::ifstream &ifs)
{
	std::string text_line;

	while(std::getline(ifs, text_line))
	{
		file.push_back(text_line);
		int line_number = file.size() - 1;
		std::istringstream line(text_line);
		std::string text_word;
		while(line >> text_word)
		{
			std::string word;
			std::copy_if(text_word.begin(), text_word.end(), std::back_inserter(word), isalpha);
			// std::cout << word << std::endl;
			auto &wm_lines = word_map[word];
			if(!wm_lines)
				wm_lines.reset(new std::set<line_no>, DebugDelete());
			wm_lines->insert(line_number);
		}
	}
}

std::tuple<std::string, std::shared_ptr<std::set<TextQuery::line_no>>, StrBlob> TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<TextQuery::line_no>> nodata(new std::set<TextQuery::line_no>);
	auto loc = word_map.find(sought);
	if(loc == word_map.end())
		return std::tuple<std::string, std::shared_ptr<std::set<TextQuery::line_no>>, StrBlob>(sought, nodata, file);
	else
		return std::tuple<std::string, std::shared_ptr<std::set<TextQuery::line_no>>, StrBlob>(sought, loc->second, file);
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " /*<< make_plural(qr.lines->size(), "time", "s")*/ << std::endl;
	for(auto num : *qr.lines)
	{
		ConstStrBlobPtr p(qr.file, num);
		os << "\t(line " << num + 1 << ") " << p.deref() << std::endl;
	}
		
	return os;
}

#endif