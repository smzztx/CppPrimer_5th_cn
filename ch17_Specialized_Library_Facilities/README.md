## 17.1
```cpp
#include <iostream>
#include <tuple>
#include <vector>

int main()
{
	std::tuple<int, int, int> threeI(10, 20, 30);
	std::tuple<std::string, std::vector<std::string>, std::pair<std::string, int>> someVal("constants", {"a", "bb"}, {"ccc", 3});

	return 0;
}
```
  
## 17.2
参见１7.1。
  
## 17.3
第一种设计更好，第二种设计更容易实现，但不容易重构。  
```cpp
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
```
  
## 17.04
```cpp
#include <iostream>
#include <string>
#include "Sales_data.h"
#include <unordered_set>
#include <algorithm>
#include <tuple>

namespace std
{
	template <>
	struct hash<Sales_data>
	{
		typedef size_t result_type;
		typedef Sales_data argument_type;
		size_t operator()(const Sales_data &s) const;
	};
	size_t hash<Sales_data>::operator()(const Sales_data &s) const
	{
		return hash<std::string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
	}
}

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}

typedef std::tuple<std::vector<Sales_data>::size_type, std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator> matches;

std::vector<matches> findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book)
{
	std::vector<matches> ret;
	for(auto it = files.cbegin(); it != files.cend(); ++it)
	{
		auto found = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);
		if(found.first != found.second)
			ret.push_back(std::make_tuple(it - files.cbegin(), found.first, found.second));
	}
	return ret;
}

void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
	std::string s;
	while(in >> s)
	{
		auto trans = findBook(files, s);
		if(trans.empty())
		{
			std::cout << s << " not found in any stores" << std::endl;
			continue;
		}
		for(const auto &store : trans)
			os << "store " << std::get<0>(store) << " sales: " << std::accumulate(std::get<1>(store), std::get<2>(store), Sales_data(s)) << std::endl;
	}
}

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2("001-01", 2, 100);
    Sales_data sales_data3("001-02", 2, 80);

    std::vector<Sales_data> vs1 = {sales_data1, sales_data3};
    std::vector<Sales_data> vs2 = {sales_data2};
    std::vector<std::vector<Sales_data>> vvs = {vs1, vs2};

    reportResults(std::cin, std::cout, vvs);

 //    std::cout << std::hex << std::hash<std::string>()("001-01") << std::endl;
 //    std::cout << std::hex << std::hash<unsigned>()(1) << std::endl;
 //    std::cout << std::hex << std::hash<double>()(100) << std::endl;

 //    std::unordered_multiset<Sales_data> SDset;
 //    SDset.emplace(sales_data1);
 //    SDset.emplace("001-03", 1, 200);
 //    SDset.emplace(sales_data3);

	// for(const auto &item : SDset)
	// 	std::cout << "the hash code of " << item.isbn() <<":\n0x" << std::hex << std::hash<Sales_data>()(item) << "\n";

    return 0;
}
```
  
## 17.05
```cpp
#include <iostream>
#include <string>
#include "Sales_data.h"
#include <unordered_set>
#include <algorithm>
#include <utility>

namespace std
{
	template <>
	struct hash<Sales_data>
	{
		typedef size_t result_type;
		typedef Sales_data argument_type;
		size_t operator()(const Sales_data &s) const;
	};
	size_t hash<Sales_data>::operator()(const Sales_data &s) const
	{
		return hash<std::string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
	}
}

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}

typedef std::pair<std::vector<Sales_data>::size_type, std::pair<std::vector<Sales_data>::const_iterator, std::vector<Sales_data>::const_iterator>> matches;

std::vector<matches> findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book)
{
	std::vector<matches> ret;
	for(auto it = files.cbegin(); it != files.cend(); ++it)
	{
		auto found = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);
		if(found.first != found.second)
			ret.push_back(std::make_pair(it - files.cbegin(), std::make_pair(found.first, found.second)));
	}
	return ret;
}

void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
	std::string s;
	while(in >> s)
	{
		auto trans = findBook(files, s);
		if(trans.empty())
		{
			std::cout << s << " not found in any stores" << std::endl;
			continue;
		}
		for(const auto &store : trans)
			os << "store " << store.first << " sales: " << std::accumulate(store.second.first, store.second.second, Sales_data(s)) << std::endl;
	}
}

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2("001-01", 2, 100);
    Sales_data sales_data3("001-02", 2, 80);

    std::vector<Sales_data> vs1 = {sales_data1, sales_data3};
    std::vector<Sales_data> vs2 = {sales_data2};
    std::vector<std::vector<Sales_data>> vvs = {vs1, vs2};

    reportResults(std::cin, std::cout, vvs);

 //    std::cout << std::hex << std::hash<std::string>()("001-01") << std::endl;
 //    std::cout << std::hex << std::hash<unsigned>()(1) << std::endl;
 //    std::cout << std::hex << std::hash<double>()(100) << std::endl;

 //    std::unordered_multiset<Sales_data> SDset;
 //    SDset.emplace(sales_data1);
 //    SDset.emplace("001-03", 1, 200);
 //    SDset.emplace(sales_data3);

	// for(const auto &item : SDset)
	// 	std::cout << "the hash code of " << item.isbn() <<":\n0x" << std::hex << std::hash<Sales_data>()(item) << "\n";

    return 0;
}
```
  
## 17.06
```cpp
#include <iostream>
#include <string>
#include "Sales_data.h"
#include <unordered_set>
#include <algorithm>
#include <utility>

namespace std
{
	template <>
	struct hash<Sales_data>
	{
		typedef size_t result_type;
		typedef Sales_data argument_type;
		size_t operator()(const Sales_data &s) const;
	};
	size_t hash<Sales_data>::operator()(const Sales_data &s) const
	{
		return hash<std::string>()(s.bookNo) ^ hash<unsigned>()(s.units_sold) ^ hash<double>()(s.revenue);
	}
}

bool compareIsbn(const Sales_data &lhs, const Sales_data &rhs)
{
	return lhs.isbn() < rhs.isbn();
}

struct matches
{
	std::vector<Sales_data>::size_type index;
	std::vector<Sales_data>::const_iterator first;
	std::vector<Sales_data>::const_iterator last;
	matches(std::vector<Sales_data>::size_type index_, std::vector<Sales_data>::const_iterator first_, std::vector<Sales_data>::const_iterator last_) : index(index_), first(first_), last(last_) {}
};

std::vector<matches> findBook(const std::vector<std::vector<Sales_data>> &files, const std::string &book)
{
	std::vector<matches> ret;
	for(auto it = files.cbegin(); it != files.cend(); ++it)
	{
		auto found = std::equal_range(it->cbegin(), it->cend(), Sales_data(book), compareIsbn);
		if(found.first != found.second)
			ret.push_back(matches(it - files.cbegin(), found.first, found.second));
	}
	return ret;
}

void reportResults(std::istream &in, std::ostream &os, const std::vector<std::vector<Sales_data>> &files)
{
	std::string s;
	while(in >> s)
	{
		auto trans = findBook(files, s);
		if(trans.empty())
		{
			std::cout << s << " not found in any stores" << std::endl;
			continue;
		}
		for(const auto &store : trans)
			os << "store " << store.index << " sales: " << std::accumulate(store.first, store.last, Sales_data(s)) << std::endl;
	}
}

int main()
{
    Sales_data sales_data1("001-01", 1, 100);
    Sales_data sales_data2("001-01", 2, 100);
    Sales_data sales_data3("001-02", 2, 80);

    std::vector<Sales_data> vs1 = {sales_data1, sales_data3};
    std::vector<Sales_data> vs2 = {sales_data2};
    std::vector<std::vector<Sales_data>> vvs = {vs1, vs2};

    reportResults(std::cin, std::cout, vvs);

 //    std::cout << std::hex << std::hash<std::string>()("001-01") << std::endl;
 //    std::cout << std::hex << std::hash<unsigned>()(1) << std::endl;
 //    std::cout << std::hex << std::hash<double>()(100) << std::endl;

 //    std::unordered_multiset<Sales_data> SDset;
 //    SDset.emplace(sales_data1);
 //    SDset.emplace("001-03", 1, 200);
 //    SDset.emplace(sales_data3);

	// for(const auto &item : SDset)
	// 	std::cout << "the hash code of " << item.isbn() <<":\n0x" << std::hex << std::hash<Sales_data>()(item) << "\n";

    return 0;
}
```
  
## 17.07
tuple版本的findBook，更简洁。  
  
## 17.08
返回的Sales_data中的bookNo成员为空。  
  
## 17.09
（a）用unsigned值初始化：0000000000000000000000000000000000000000000000000000000000100000；  
（b）用unsigned值初始化：00000000000011110110100110110101；  
（c）用string初始化：取决于cin。  
  
## 17.10
```cpp
#include <bitset>
#include <vector>
#include <iostream>

int main()
{
	std::vector<int> vi = {1, 2, 3, 5, 8, 13, 21};
	std::bitset<32> bset;
	for(auto const i : vi)
	{
		bset.set(i);
	}
	std::cout << bset << std::endl;

	return 0;
}
```
  
## 17.11
```cpp
#include <bitset>

template <unsigned N>
class quiz
{
public:
	quiz(std::string &s) : bset(s) {}
	
private:
	std::bitset<N> bset;
};

int main()
{
	std::string s1("0101010101");
	std::string s2("0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
	quiz<10> q1(s1);
	quiz<100> q2(s2);

	return 0;
}
```
  
## 17.12
```cpp
#include <bitset>
#include <iostream>

template <unsigned N>
class quiz
{
template <unsigned M>
friend std::ostream &operator<<(std::ostream&, const quiz<M>&);
public:
	quiz(std::string &s) : bset(s) {}
	void update(size_t n, bool b)
	{
		bset[n] = b;
	}
	
private:
	std::bitset<N> bset;
};

template <unsigned M>
std::ostream &operator<<(std::ostream &os, const quiz<M> &q)
{
	os << q.bset;
	return os;
}

int main()
{
	std::string s1("0101010101");
	std::string s2("0101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101010101");
	quiz<10> q1(s1);
	quiz<100> q2(s2);

	q1.update(1,true);
	std::cout << q1 << std::endl;

	return 0;
}
```
  
## 17.13
```cpp
#include <bitset>
#include <iostream>

template <unsigned N>
class quiz
{
template <unsigned M>
friend std::ostream &operator<<(std::ostream&, const quiz<M>&);

template <unsigned M>
friend size_t grade(const quiz<M>&, const quiz<M>&);
public:
	quiz(std::string &s) : bset(s) {}
	void update(size_t n, bool b)
	{
		bset[n] = b;
	}
	
private:
	std::bitset<N> bset;
};

template <unsigned M>
std::ostream &operator<<(std::ostream &os, const quiz<M> &q)
{
	os << q.bset;
	return os;
}

template <unsigned M>
size_t grade(const quiz<M> &lhsQ, const quiz<M> &rhsQ)
{
	return (lhsQ.bset ^ rhsQ.bset).flip().count();
}

int main()
{
	std::string s1("0101010101");
	std::string s2("0101010100");

	quiz<10> q1(s1);
	quiz<10> q2(s2);

	std::cout << grade(q1, q2) << std::endl;

	return 0;
}
```
  
## 17.14
