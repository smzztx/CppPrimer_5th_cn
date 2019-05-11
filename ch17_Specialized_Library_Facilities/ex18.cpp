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