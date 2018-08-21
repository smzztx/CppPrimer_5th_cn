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
```cpp
