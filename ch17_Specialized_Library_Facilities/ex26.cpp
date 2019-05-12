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