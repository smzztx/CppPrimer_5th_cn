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

    int n = 0;
    for(int i = 1; i < 10; ++i)
    {
    	for(auto iter = vs.begin(); iter != vs.end(); )
    	{
    		iter = std::find_if(iter+1, vs.end(), CompareString(i));
    		if(iter != vs.end()) ++n;
    	}
    }
    std::cout << "length:1-9" << "," << n << std::endl;
    	
    n = 0;
    for(int i = 10; i < 30; ++i)
    {
        for(auto iter = vs.begin(); iter != vs.end(); )
        {
            iter = std::find_if(iter+1, vs.end(), CompareString(i));
            if(iter != vs.end()) ++n;
        }
    }
    std::cout << "length:1-9" << "," << n << std::endl;

	return 0;
}