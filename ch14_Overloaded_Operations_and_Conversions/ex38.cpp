#include <string>
#include <iostream>
#include <fstream>

class CompareString
{
public:
	CompareString(size_t n) : default_size(n) {};
	bool operator()(const string &s) const
	{
		return n == s.size();
	}
private:
	size_t default_size;
};

int main()
{
	ifstream ifs("../ch09_Sequential_Containers/letter.txt");
    if (!ifs) return -1;

    for(std::string curr; ifs >> curr; )
    	

	return 0;
}