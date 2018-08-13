#ifndef PERSON_H_
#define PERSON_H_

#include <string>

struct Person
{
    std::string name;
    std::string address;

    std::string get_name() const{return name;}
    std::string get_address() const{return address;}
};

std::istream &read(std::istream &is, Person &item)
{
	return is >> item.name >> item.address;
}

std::ostream &print(std::ostream &os, const Person &item)
{
	return os << item.name << " " << item.address;
}

#endif