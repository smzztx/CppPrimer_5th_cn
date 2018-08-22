#include <string>
#include <vector>
#include <sstream>
#include <iostream>

using namespace std;

struct PersonInfo {
    string name;
    vector<string> phones;
};

int main()
{
	string line, word;
	vector<PersonInfo> people;
	istringstream record;

	while(getline(cin, line))
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
		cout << person.name << " ";
		for(const auto &ph : person.phones)
		{
			cout << ph << " ";
		}
		cout << endl;
	}

	return 0;
}