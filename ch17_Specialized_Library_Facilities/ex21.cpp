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