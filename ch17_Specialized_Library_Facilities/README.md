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
```cpp
#include <iostream>
#include <regex>
int main()
{
	try
	{
		std::regex r1("[[:anum:]]+\\.(cpp|cxx|cc)$", std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}

	try
	{
		std::regex r1("[[:alnum:]+\\.(cpp|cxx|cc)$", std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}	

	try
	{
		std::regex r1("[[:alnum:]]+\\.cpp|cxx|cc)$", std::regex::icase);
	}catch(std::regex_error e)
	{
		std::cout << e.what() << "\ncode: " << e.code() << std::endl;
	}

	return 0;
}
```
  
## 17.15
gcc version 4.8.4 对regex支持有问题，请使用4.9及以上版本。  
```cpp
#include <iostream>
#include <regex>
#include <string>

int main()
{
	/*https://en.wikipedia.org/wiki/I_before_E_except_after_C
	**ie in believe, fierce, collie, die, friend
	**ei after c in receive, ceiling, receipt, ceilidh
	*/
	// std::string pattern("[[:alpha:]]*(cei|[^c]ie)[[:alpha:]]*");
	std::string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
	std::regex r(pattern);
	std::smatch results;
	std::cout << "input a word: ";

	std::string s;
	while(std::cin >> s)
	{
		if(std::regex_search(s, results, r))
			std::cout << s <<  ": error" << std::endl;
		else
			std::cout << s <<  ": correct" << std::endl;
	}

	return 0;
}
```
```sh
$ ./ex15 
believe
believe: correct
freind
freind: error
receipt
receipt: correct
theif
theif: error
receive
receive: correct
```
  
## 14.16
这样只匹配3个字符，（非c）和ei这3个字符，匹配成功后result中只有3个字符。  
这里就按照题意写规则。  
```cpp
#include <iostream>
#include <regex>
#include <string>

int main()
{
	std::string pattern("[^c]ei");
	std::regex r(pattern);
	std::smatch results;

	std::string s;
	while(std::cin >> s)
	{
		if(std::regex_search(s, results, r))
		{
			std::cout << s <<  ": correct" << std::endl;
			for (size_t i = 0; i < results.size(); ++i) 
				std::cout << i << ": " << results[i] << '\n';
		}
		else
		{
			std::cout << s <<  ": error" << std::endl;
		}
	}

	return 0;
}
```
```sh
$ ./ex16 
freind
freind: correct
1: rei 
```
  
## 17.17
```cpp
#include <iostream>
#include <regex>
#include <string>

int main()
{
	std::string pattern("[[:alpha:]]*[^c]ei[[:alpha:]]*");
	std::regex r(pattern, std::regex::icase);
	std::smatch results;
	std::string s("freind receipt theif receive");

	for(std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
	{
		std::cout << it->str() << std::endl;
	}

	return 0;
}
```
```sh
$ ./ex17 
freind
theif
```
  
## 17.18
```cpp
#include <iostream>
#include <regex>
#include <string>
#include <vector>
#include <algorithm>

int main()
{
	std::string pattern("([[:alpha:]]*[^c]ei[[:alpha:]]*)");
	std::regex r(pattern, std::regex::icase);
	std::smatch results;
	std::string s("freind receipt theif receive albeit neighbor");
	std::vector<std::string> vec{"neighbor","albeit","beige","feint","heir","reign","their",
            "counterfeit","foreign","inveigh","rein","veil","deign",
            "forfeit","inveigle","seize","veineiderdown","freight",
            "leisure","skein","weigheight","heifer","neigh","sleigh",
            "weighteither","height","neighbour","sleight","weirfeign",
            "heinous","neither","surfeit","weird"};

	for(std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
	{
		if (find(vec.begin(), vec.end(), it->str()) != vec.end())
			continue;
		std::cout << it->str() << std::endl;
	}

	return 0;
}
```
  
## 17.19
没有匹配则返回为空字符串，也是可以比较的。  
  
## 17.20
```cpp
#include <iostream>
#include <string>
#include <regex>

bool valid(const std::smatch &m)
{
	if(m[1].matched)
		return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
	else
		return !m[3].matched && m[4].str() == m[6].str();
}

//908.555.1500
int main()
{
	std::string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
	std::regex r(phone);
	std::smatch m;
	std::string s;

	while(std::getline(std::cin, s))
	{
		for(std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
			if(valid(*it))
				std::cout << "valid: " << it->str() << std::endl;
			else
				std::cout << "not valid: " << it->str() << std::endl;
	}

	return 0;
}
```
  
## 17.21
```cpp
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(const std::smatch &m)
{
	if(m[1].matched)
		return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
	else
		return !m[3].matched && m[4].str() == m[6].str();
}

string format(const string &s)
{
	return s;
}

int main()
{
	string line, word;
	vector<PersonInfo> people;
	istringstream record;
	ifstream ifs("personinfo");
	ofstream ofs("personinfo_new");
	std::string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
	std::regex r(phone);
	std::smatch m;
	std::string s;

	while(getline(ifs, line))
	{
		record.str(line);
		PersonInfo info;
		record >> info.name;
		while(record >> word)
			info.phones.push_back(word);
		record.clear();
		people.push_back(info);
	}

	for(const auto &person : people)
	{
		ostringstream formatted, badNums;
		for(const auto &ph : person.phones)
		{
			for(std::sregex_iterator it(ph.begin(), ph.end(), r), end_it; it != end_it; ++it)
				if(!valid(*it))
				{
					badNums << " " << ph;
				}else
					formatted << " " << (*it)[2] << " " << (*it)[2] << (*it)[2];
		}
		if(badNums.str().empty())
			ofs << person.name << " " << formatted.str() << endl;
		else
			cerr << " input error: " << person.name << " invalid number(s)" << badNums.str() << endl;
	}

	return 0;
}
```
  
## 17.22
```cpp
#include <iostream>
#include <string>
#include <regex>

bool valid(const std::smatch &m)
{
	if(m[1].matched)
		return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
	else
		return !m[3].matched && m[4].str() == m[7].str();
}

//908.555.1500
//(908)5551500
//(908.555.1500
//908   555   1500
int main()
{
	std::string phone = "(\\()?(\\d{3})(\\))?([-. ])?([ ]*)?(\\d{3})([-. ]?)([ ]*)?(\\d{4})";
	std::regex r(phone);
	std::smatch m;
	std::string s;

	while(std::getline(std::cin, s))
	{
		for(std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
			if(valid(*it))
				std::cout << "valid: " << it->str() << std::endl;
			else
				std::cout << "not valid: " << it->str() << std::endl;
	}

	return 0;
}
```
```sh
$ ./ex22 
908.555.1500
valid: 908.555.1500
908   555   1500
valid: 908   555   1500
```
  
## 17.23
```cpp
#include <iostream>
#include <string>
#include <regex>

bool valid(const std::smatch &m)
{
	if(m[3].matched)
		return true;
	else
		return !m[2].matched;
}

//111112222
//11111-2222
//11111
//11111-
int main()
{
	std::string mail = "(\\d{5})([-])?(\\d{4})?";
	std::regex r(mail);
	std::smatch m;
	std::string s;

	while(std::getline(std::cin, s))
	{
		for(std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
			if(valid(*it))
				std::cout << "valid: " << it->str() << std::endl;
			else
				std::cout << "not valid: " << it->str() << std::endl;
	}

	return 0;
}
```
```sh
$ ./ex23
111112222
valid: 111112222
11111-2222
valid: 11111-2222
11111
valid: 11111
11111-
not valid: 11111-
```
  
## 17.24
```cpp
#include <iostream>
#include <string>
#include <regex>

//908.555.1500
//(908)5551500
//(908.555.1500
int main()
{
	std::string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})";
	std::regex r(phone);
	std::smatch m;
	std::string s;
	std::string fmt = "$2.$5.$7";

	while(std::getline(std::cin, s))
	{
		std::cout << std::regex_replace(s, r, fmt) << std::endl;
	}

	return 0;
}
```
  
## 17.25
```cpp
#include <iostream>
#include <string>
#include <regex>

//tx 908.555.1500 (908)5551500
int main()
{
	std::string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ]?)(\\d{4})*";
	std::regex r(phone);
	std::smatch m;
	std::string s;
	std::string fmt = "$2.$5.$7";

	while(std::getline(std::cin, s))
	{
		std::smatch result;
		std::regex_search(s,result,r);
		if(!result.empty())
		{
			std::cout << result.prefix() << result.format(fmt) << std::endl;
		}
		else
		{
			std::cout << "Sorry, No match." << std::endl;
		}
	}

	return 0;
}
```
  
## 17.26
```cpp
#include <iostream>
#include <string>
#include <regex>

bool valid(const std::smatch &m)
{
	if(m[1].matched)
		return m[3].matched && (m[4].matched == 0 || m[4].str() == " ");
	else
		return !m[3].matched && m[4].str() == m[7].str();
}

//tx 908.555.1500 (908)5551500
int main()
{
	std::string phone = "(\\()?(\\d{3})(\\))?([-. ])?([ ]*)?(\\d{3})([-. ]?)([ ]*)?(\\d{4})";
	std::regex r(phone);
	std::smatch m;
	std::string s;

	while(std::getline(std::cin, s))
	{
		std::vector<std::string> vs;
		for(std::sregex_iterator it(s.begin(), s.end(), r), end_it; it != end_it; ++it)
			if(valid(*it))
				vs.push_back(it->str());
		if (vs.size() == 0)
		{
			std::cout << "no matched number" << std::endl;
		}else if(vs.size() == 1)
		{
			std::cout << vs[0] << std::endl;
		}else if(vs.size() >1)
		{
			for(int i = 1; i < vs.size(); ++i)
				std::cout << vs[i] << " ";
			std::cout << std::endl;
		}
	}

	return 0;
}
```
  
## 17.27
```cpp
#include <iostream>
#include <string>
#include <regex>

bool valid(const std::smatch &m)
{
	if(m[3].matched)
		return true;
	else
		return !m[2].matched;
}

//111112222
//11111-2222
//11111
//11111-
int main()
{
	std::string mail = "(\\d{5})([-])?(\\d{4})?";
	std::regex r(mail);
	std::smatch m;
	std::string s;
	std::string fmt = "$1-$3";

	while(std::getline(std::cin, s))
	{
		std::cout << std::regex_replace(s, r, fmt) << std::endl;
	}

	return 0;
}
```
  
## 17.28
```cpp
#include <random>
#include <iostream>

unsigned random_func()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}

int main()
{
	
	std::cout << random_func() << std::endl;

	return 0;
}
```
  
## 17.29
```cpp
#include <random>
#include <iostream>

unsigned random_func()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}

unsigned random_func(unsigned i)
{
	static std::default_random_engine e(i);
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}

int main()
{
	
	std::cout << random_func() << std::endl;	//default 1
	std::cout << random_func(2) << std::endl;

	return 0;
}
```
  
## 17.30
```cpp
#include <random>
#include <iostream>

unsigned random_func()
{
	static std::default_random_engine e;
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}

unsigned random_func(unsigned i)
{
	static std::default_random_engine e(i);
	static std::uniform_int_distribution<unsigned> u;
	return u(e);
}

unsigned random_func(unsigned i, unsigned min, unsigned max)
{
	static std::default_random_engine e(i);
	static std::uniform_int_distribution<unsigned> u(min, max);
	return u(e);
}

int main()
{
	
	std::cout << random_func() << std::endl;	//default 1
	std::cout << random_func(2) << std::endl;
	for(int i = 0; i < 10; ++i)
		std::cout << random_func(1, 0, 10) << std::endl;

	return 0;
}
```
  
## 17.31
每次的随机数都相同。
  
## 17.32
会报错，未定义resp。
  
## 17.33
```cpp
#include <map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <vector>
#include <random>

using namespace std;

map<string, vector<string>> buildMap(ifstream &map_file)
{
	map<string, vector<string>> trans_map;
	string key;
	string value;
	while(map_file >> key && getline(map_file, value))
		if(value.size() > 1)
			trans_map[key].push_back(value.substr(1));
		else
			throw runtime_error("no rule for " + key);
	return trans_map;
}

const string &transform(const string &s, const map<string, vector<string>> &m)
{
	static default_random_engine e(time(0));
	static uniform_int_distribution<unsigned> u(0,1);
	auto map_it = m.find(s);
	if(map_it != m.cend())
		return (map_it->second)[u(e)];
	else
		return s;
}

void word_tranform(ifstream &map_file, ifstream &input)
{
	auto trans_map = buildMap(map_file);
	// for(const auto p : trans_map)
	// 	cout << p.first << "->" << p.second << endl;
	string text;
	while(getline(input, text))
	{
		istringstream stream(text);
		string word;
		bool firstword = true;
		while(stream >> word)
		{
			if(firstword)
				firstword = false;
			else
				cout << " ";
			cout << transform(word, trans_map);
		}
		cout << endl;
	}
}

int main()
{
	ifstream map_file("word_transformation.txt"), input("word_transformation_bad.txt");
	word_tranform(map_file, input);

	return 0;
}
```
  
## 17.34
略。  
  
## 17.35
[Missing ios_base::hexfloat format specifier](https://gcc.gnu.org/bugzilla/show_bug.cgi?id=59987)
  
## 17.36
```cpp
#include <iostream>
#include <cmath>
#include <iomanip>

int main()
{
	std::cout << std::left << std::setw(16) <<"default format: " << std::right << std::setw(25) << sqrt(2.0) << '\n'
		<< std::left << std::setw(16) << "scientific: " << std::scientific << std::right << std::setw(25) << sqrt(2.0) << '\n'
		<< std::left << std::setw(16) << "fixed decimal: " << std::fixed << std::right << std::setw(25) << sqrt(2.0) << '\n'
		<< std::left << std::setw(16) << "hexidecimal: " << std::uppercase << std::hexfloat << std::right << std::setw(25) << sqrt(2.0) << '\n'
		<< std::left << std::setw(16) << "use defaults: " << std::defaultfloat << std::right << std::setw(25) << sqrt(2.0)
		<< "\n\n";

	return 0;
}
```
  
## 17.37
[basic_istream::getline, if it extracts no characters, if it fills in the provided buffer without encountering the delimiter, or if the provided buffer size is less than 1.](https://en.cppreference.com/w/cpp/io/ios_base/iostate)
```cpp
#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::fstream fs("../ch08_The_IO_Library/data");
	char tmp[200];
	fs.getline(tmp, 2, '\n');
	std::cout << tmp << std::endl;
	std::cout << fs.gcount() << std::endl;

	fs.getline(tmp, 2, '\n');
	std::cout << tmp << std::endl;
	std::cout << fs.gcount() << std::endl;
	std::cout << std::boolalpha << (fs.rdstate() == std::ios_base::failbit) << std::endl;
	// std::cout << std::ios_base::goodbit << std::endl;
	// std::cout << std::ios_base::badbit << std::endl;
	// std::cout << std::ios_base::failbit << std::endl;
	// std::cout << std::ios_base::eofbit << std::endl;
	//https://en.cppreference.com/w/cpp/io/ios_base/iostate

	return 0;
}
```
  
## 17.38
```cpp
#include <fstream>
#include <iostream>
#include <string>

int main()
{
	std::fstream fs("../ch08_The_IO_Library/data");
	char tmp[200];

	// while(fs.getline(tmp, 200, ' '))
	// 	std::cout << tmp << std::endl;
	fs.getline(tmp, 200, ' ');
	std::cout << tmp << std::endl;
	std::cout << fs.gcount() << std::endl;
	std::cout <<fs.rdstate() << std::endl;
	fs.getline(tmp, 200, ' ');
	std::cout <<fs.rdstate() << std::endl;

	return 0;
}
```
  
## 13.39
```cpp
#include <iostream>
#include <fstream>

int main()
{
	std::fstream inOut("copyOut", std::fstream::ate | std::fstream::in | std::fstream::out);

	if(!inOut)
	{
		std::cerr << "Unable to open file!" << std::endl;
		return EXIT_FAILURE;
	}

	auto end_mark = inOut.tellg();
	inOut.seekg(0, std::fstream::beg);
	size_t cnt = 0;
	std::string line;

	while(inOut && inOut.tellg() != end_mark && getline(inOut, line))
	{
		cnt += line.size() + 1;
		auto mark = inOut.tellg();
		inOut.seekp(0, std::fstream::end);
		inOut << cnt;
		if(mark != end_mark) inOut << " ";
		inOut.seekg(mark);
	}
	inOut.seekp(0, std::fstream::end);
	inOut << "\n";

	return 0;
}
```