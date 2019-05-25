## 练习8.1

> 编写函数，接受一个istream&参数，返回值类型也是istream&。此函数须从给定流中读取数据，直至遇到文件结束标识时停止。它将读取的数据打印在标准输出上。完成这些操作后，在返回流之前，对流进行复位，使其处于有效状态。

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
  
## 练习8.2

> 测试函数，调用参数为cin。

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
  
## 练习8.3

> 什么情况下，下面的while循环会终止？
```cpp
while (cin >> i) /*  ...    */
```

badbit、failbit和eofbit任一个被置位，则检测流状态的条件会失败。
  
## 练习8.4

> 编写函数，以读模式打开一个文件，将其内容读入到一个string的vector中，将每一行作为一个独立的元素存于vector中。

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
  
## 练习8.5

> 重写上面的程序，将每个单词作为一个独立的元素进行存储。

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
  
## 练习8.6

> 重写7.1.1节的书店程序，从一个文件中读取交易记录。将文件名作为一个参数传递给main。

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
  
## 练习8.7

> 修改上一节的书店程序，将结果保存到一个文件中。将输出文件名作为第二个参数传递给main函数。

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
  
## 练习8.8

> 修改上一题的程序，将结果追加到给定的文件末尾。对同一个输出文件，运行程序至少两次，检验数据是否得以保留。

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
  
## 练习8.9

> 使用你为8.1.2节第一个练习所编写的函数打印一个istringstream对象的内容。

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
  
## 练习8.10

> 编写程序，将来自一个文件中的行保存在一个vector<string>中。然后使用一个istringstream从vector读取数据元素，每次读取一个单词。

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
  
## 练习8.11

> 本节的程序在外层while循环中定义了istringstream 对象。如果record 对象定义在循环之外，你需要对程序进行怎样的修改？重写程序，将record的定义移到while 循环之外，验证你设想的修改方法是否正确。

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
  
## 练习8.12

> 我们为什么没有在PersonInfo中使用类内初始化？

string和vector可以自己初始化，并不会出现未定义的情况。
  
## 练习8.13

> 重写本节的电话号码程序，从一个命名文件而非cin读取数据。

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
  
## 练习8.14

> 我们为什么将entry和nums定义为 const auto& ？

它们都是类类型，因此使用引用避免拷贝，提高了效率；在循环当中不会改变它们的值，因此用const。  