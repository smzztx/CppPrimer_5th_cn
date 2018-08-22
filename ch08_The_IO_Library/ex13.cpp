#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;
};

bool valid(const string &s)
{
	for(const auto c : s)
		if(!isdigit(c)) return false;
	return true;
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
			if(!valid(ph))
			{
				badNums << " " << ph;
			}else
				formatted << " " << format(ph);
		}
		if(badNums.str().empty())
			ofs << person.name << " " << formatted.str() << endl;
		else
			cerr << " input error: " << person.name << " invalid number(s)" << badNums.str() << endl;
	}

	return 0;
}