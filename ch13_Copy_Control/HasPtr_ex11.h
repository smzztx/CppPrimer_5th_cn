#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
    HasPtr& operator=(const HasPtr &rhs_hp) {
        if(this != &rhs_hp){
            std::string *temp_ps = new std::string(*rhs_hp.ps);
            delete ps;
            ps = temp_ps;
            i = rhs_hp.i;
        }
        return *this;
    }
    ~HasPtr()
    {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

#endif