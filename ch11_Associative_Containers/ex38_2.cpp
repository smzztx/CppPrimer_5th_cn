#include <unordered_map>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

unordered_map<string, string> buildMap(ifstream &map_file)
{
	unordered_map<string, string> trans_map;
	string key;
	string value;
	while(map_file >> key && getline(map_file, value))
		if(value.size() > 1)
			trans_map[key] = value.substr(1);
		else
			throw runtime_error("no rule for " + key);
	return trans_map;
}

const string &transform(const string &s, const unordered_map<string, string> &m)
{
	auto map_it = m.find(s);
	if(map_it != m.cend())
		return map_it->second;
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