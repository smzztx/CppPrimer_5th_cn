## 8.1 
```cpp
std::istream &iofunction(std::istream &is)
{
	std::string s;
	while(is >> s)
		std::cout << s << std::endl;
	is.clear();
	return is;
}
```

## 8.2 
```cpp
#include <iostream>
#include <string>

std::istream &iofunction(std::istream &is)
{
	std::string s;
	while(is >> s)
		std::cout << s << std::endl;
	is.clear();
	return is;
}

int main()
{
	iofunction(std::cin);

	std::string s1;
	while(std::cin >> s1)
		std::cout << s1 << std::endl;

	return 0;
}
```

## 8.3 
badbit、failbit和eofbit任一个被置位，则检测流状态的条件会失败。

## 8.4 
```cpp
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	ifstream ifs("data");
	vector<string> v1;
	string buf;

	if(ifs)
	{
		while(getline(ifs,buf))
		{
			v1.push_back(buf);
		}
	}


	for(const auto &s : v1)
		cout << s << endl;

	return 0;
}
```

## 8.5  
```cpp
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main()
{
	ifstream ifs("data");
	vector<char> v1;
	char buf;

	if(ifs)
	{
		while(ifs >> buf)
		{
			v1.push_back(buf);
		}
	}


	for(const auto &c : v1)
		cout << c << endl;

	return 0;
}
```

## 8.6  
本题使用习题7.26的代码，和题目中略有不同，并不影响。
```cpp
#include <iostream>
#include <string>
#include <fstream>
#include "../ch07_Classes/Sales_data_ex26.h"

int main(int argc, char **argv)
{
    std::ifstream ifs(argv[1]);

    if(!ifs) return 1;

    Sales_data total(ifs);

    if (!total.isbn().empty())
    {
        Sales_data trans;

        while (read(ifs, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(std::cout, total);
                std::cout << std::endl;
                total = trans;
            }
        }
        print(std::cout, total);
        std::cout << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```

## 8.7  
```cpp
#include <iostream>
#include <string>
#include <fstream>
#include "../ch07_Classes/Sales_data_ex26.h"

int main(int argc, char **argv)
{
    std::ifstream ifs(argv[1]);
    std::ofstream ofs(argv[2]);

    if(!ifs) return 1;

    Sales_data total(ifs);

    if (!total.isbn().empty())
    {
        Sales_data trans;

        while (read(ifs, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(ofs, total);
                ofs << std::endl;
                total = trans;
            }
        }
        print(ofs, total);
        ofs << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```

## 8.8  
```cpp
#include <iostream>
#include <string>
#include <fstream>
#include "../ch07_Classes/Sales_data_ex26.h"

int main(int argc, char **argv)
{
    std::ifstream ifs(argv[1]);
    std::ofstream ofs(argv[2], std::ofstream::app);

    if(!ifs) return 1;

    Sales_data total(ifs);

    if (!total.isbn().empty())
    {
        Sales_data trans;

        while (read(ifs, trans))
        {
            if (total.isbn() == trans.isbn())
            {
                total.combine(trans);
            }
            else
            {
                print(ofs, total);
                ofs << std::endl;
                total = trans;
            }
        }
        print(ofs, total);
        ofs << std::endl;

        return 0;
    }
    else
    {
        std::cerr << "No data?!" << std::endl;
        return -1;  // indicate failure
    }
}
```

## 8.9  
```cpp
#include <iostream>
#include <string>
#include <sstream>

std::istream &iofunction(std::istream &is)
{
	std::string s;
	while(is >> s)
		std::cout << s << std::endl;
	is.clear();
	return is;
}

int main()
{
	std::istringstream istrs("aa\nbb\ncc dd");
	iofunction(istrs);

	std::string s1;
	while(std::cin >> s1)
		std::cout << s1 << std::endl;

	return 0;
}
```

## 8.10
```cpp
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<string> v1;
	ifstream is("book_sales");
	string buf;

	if(!is)
	{
		cerr << "open error" << endl;
		return -1;
	}

	while(getline(is, buf))
		v1.push_back(buf);

	for(const auto &s : v1)
	{
		// cout << s << endl;
		istringstream iss(s);
		while(iss >> buf)
			cout << buf << endl;
	}

	return 0;
}
```

## 8.11  
```cpp
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
```

## 8.12  
string和vector可以自己初始化，并不会出现未定义的情况。

## 8.13
```cpp
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
```
