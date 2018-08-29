#include <string>
#include <iostream>

using namespace std;

class my_date
{
public:
	my_date(const string&);
private:
	unsigned int year;
	unsigned int month;
	unsigned int day;
};

my_date::my_date(const string &s)
{
	string date_str = s;
	string::size_type index1 = 0;
	string::size_type index2 = 0;

	if(s.find(',') != string::npos)//January 1, 1900
	{
		index1 = s.find(' ');
		index2 = s.find(',', index1+1);
		cout << "year: " << s.substr(index2+1, s.size()) << "; month: " << s.substr(0, index1) << "; day: " << s.substr(index1+1, index2-index1-1) << endl;
		// month = stoi(s.substr(0, index1));
		if( s.find("Jan") < s.size() )  month = 1;
		if( s.find("Feb") < s.size() )  month = 2;
		if( s.find("Mar") < s.size() )  month = 3;
		if( s.find("Apr") < s.size() )  month = 4;
		if( s.find("May") < s.size() )  month = 5;
		if( s.find("Jun") < s.size() )  month = 6;
		if( s.find("Jul") < s.size() )  month = 7;
		if( s.find("Aug") < s.size() )  month = 8;
		if( s.find("Sep") < s.size() )  month = 9;
		if( s.find("Oct") < s.size() )  month =10;
		if( s.find("Nov") < s.size() )  month =11;
		if( s.find("Dec") < s.size() )  month =12;
		day = stoi(s.substr(index1+1, index2-index1-1));
		year = stoi(s.substr(index2+1, s.size()));
	}else if(s.find('/') != string::npos)//1/1/1900
	{
		index1 = s.find('/');
		index2 = s.find('/', index1+1);
		cout << "year: " << s.substr(index2+1, s.size()) << "; month: " << s.substr(0, index1) << "; day: " << s.substr(index1+1, index2-index1-1) << endl;
		month = stoi(s.substr(0, index1));
		day = stoi(s.substr(index1+1, index2-index1-1));
		year = stoi(s.substr(index2+1, s.size()));
	}else//Jan 1 1900
	{
		index1 = s.find(' ');
		index2 = s.find(' ', index1+1);
		cout << "year: " << s.substr(index2+1, s.size()) << "; month: " << s.substr(0, index1) << "; day: " << s.substr(index1+1, index2-index1-1) << endl;
		// month = stoi(s.substr(0, index1));
		if( s.find("Jan") < s.size() )  month = 1;
		if( s.find("Feb") < s.size() )  month = 2;
		if( s.find("Mar") < s.size() )  month = 3;
		if( s.find("Apr") < s.size() )  month = 4;
		if( s.find("May") < s.size() )  month = 5;
		if( s.find("Jun") < s.size() )  month = 6;
		if( s.find("Jul") < s.size() )  month = 7;
		if( s.find("Aug") < s.size() )  month = 8;
		if( s.find("Sep") < s.size() )  month = 9;
		if( s.find("Oct") < s.size() )  month =10;
		if( s.find("Nov") < s.size() )  month =11;
		if( s.find("Dec") < s.size() )  month =12;
		day = stoi(s.substr(index1+1, index2-index1-1));
		year = stoi(s.substr(index2+1, s.size()));
	}
	cout << "year: " << year << "; month: " << month << "; day: " << day << endl;
}

int main()
{
	my_date my_date1("January 1, 1900");
	my_date my_date2("1/1/1900");
	my_date my_date3("Jan 1 1900");

	return 0;
}