#ifndef TEXTQUERY_H_
#define TEXTQUERY_H_

#include <string>
// #include <vector>
#include "StrVec_ex40.h"
#include <map>
#include <fstream>
#include <sstream>
#include <set>
#include <memory>
#include <iostream>
#include <algorithm>
#include <iterator>


class QueryResult;

class TextQuery
{
public:
	using line_no = size_t;
	TextQuery(std::ifstream&);
	QueryResult query(const std::string&) const;
private:
	std::shared_ptr<StrVec> file;
	std::map<std::string, std::shared_ptr<std::set<line_no>>> wm;
};

class QueryResult
{
	friend std::ostream& print(std::ostream&, const QueryResult&);
public:
	QueryResult(std::string s, std::shared_ptr<std::set<TextQuery::line_no>> p, std::shared_ptr<StrVec> f) : sought(s), lines(p), file(f) { }
private:
	std::string sought;
	std::shared_ptr<std::set<TextQuery::line_no>> lines;
	std::shared_ptr<StrVec> file;
};

TextQuery::TextQuery(std::ifstream &ifs) : file(new StrVec)
{
	std::string text;

	while(std::getline(ifs, text))
	{
		file->push_back(text);
		int n = file->size() - 1;
		std::istringstream line(text);
		std::string text;
		while(line >> text)
		{
			std::string word;
			std::copy_if(text.begin(), text.end(), std::back_inserter(word), isalpha);
			// std::cout << word << std::endl;
			auto &lines = wm[word];
			if(!lines)
				lines.reset(new std::set<line_no>);
			lines->insert(n);
		}
	}
}

QueryResult TextQuery::query(const std::string &sought) const
{
	static std::shared_ptr<std::set<TextQuery::line_no>> nodata(new std::set<TextQuery::line_no>);
	auto loc = wm.find(sought);
	if(loc == wm.end())
		return QueryResult(sought, nodata, file);
	else
		return QueryResult(sought, loc->second, file);
	// QueryResult QR;
	// auto count = word_line.count(s);
	// QR.count = count;
	// auto iter = word_line.find(s);

	// while(count)
	// {
	// 	QR.line_num.insert(iter->second);
	// 	++iter;
	// 	--count;
	// }

	// return QR;
	// // for(auto iter = word_line.lower_bound(s), end = word_line.upper_bound(s); iter != end; ++iter)
	// // {
	// // 	line_num.insert(iter->second);
	// // }
}

std::ostream &print(std::ostream &os, const QueryResult &qr)
{
	os << qr.sought << " occurs " << qr.lines->size() << " " /*<< make_plural(qr.lines->size(), "time", "s")*/ << std::endl;
	for(auto num : *qr.lines)
		os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
	return os;
}

#endif