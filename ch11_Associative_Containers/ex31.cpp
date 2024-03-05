#include <map>
#include <string>
#include <iostream>

int main()
{
	std::multimap<std::string, std::string> books = {{"bb", "abc"}, {"aa", "abc"}, {"aa", "bcd"}, {"aa", "cde"}};

	for(const auto &book : books)
		std::cout << book.first << ",《" << book.second << "》  ";
	std::cout << std::endl;

	std::pair<std::string, std::string> delete_book{"bb", "abc"};
	// std::pair<std::string, std::string> delete_book{"bb", "bcd"};
	// std::pair<std::string, std::string> delete_book{"aa", "bcd"};
	// std::pair<std::string, std::string> delete_book{"cc", "bcd"};

	for(auto beg = books.lower_bound(delete_book.first), end = books.upper_bound(delete_book.first); beg != end;)
	{
		if(beg->second == delete_book.second) beg = books.erase(beg);
		else ++beg;
	}

	for(const auto &book : books)
		std::cout << book.first << ",《" << book.second << "》  ";
	std::cout << std::endl;

	return 0;
}