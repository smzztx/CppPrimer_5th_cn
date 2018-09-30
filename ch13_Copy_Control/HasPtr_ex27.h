#ifndef HASPTR_EX11_H
#define HASPTR_EX11_H

#include <string>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new std::size_t(1)) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { ++*use;}
    HasPtr& operator=(const HasPtr &rhs_hp) {
        ++*rhs_hp.use;
        if(--*use == 0)
        {
            delete ps;
            delete use;
        }
        ps = rhs_hp.ps;
        i = rhs_hp.i;
        use = rhs_hp.use;
        return *this;
    }
    ~HasPtr()
    {
        if(--*use == 0)
        {
            delete ps;
            delete use;
        }
    }
private:
    std::string *ps;
    int i;
    std::size_t *use;
};

#endif