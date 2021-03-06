#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

class CompareString
{
public:
	CompareString(size_t n) : default_size(n) {};
	bool operator()(const std::string &s) const
	{
		return default_size == s.size();
	}
private:
	size_t default_size;
};

int main()
{
	std::ifstream ifs("../ch09_Sequential_Containers/letter.txt");
    if (!ifs) return -1;

    std::vector<std::string> vs;

    for(std::string curr; ifs >> curr; vs.push_back(curr));

    for(int i = 1, n = 0; i < 11; ++i)
    {
    	for(auto iter = vs.begin(); iter != vs.end(); )
    	{
    		iter = std::find_if(iter+1, vs.end(), CompareString(i));
    		if(iter != vs.end()) ++n;
    	}
    	std::cout << "length:" << i << "," << n << std::endl;
    	n = 0;
    }
    	

	return 0;
}