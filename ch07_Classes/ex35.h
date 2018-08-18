#ifndef EX35_H_
#define EX35_H_

#include <string>

typedef std::string Type;
Type initVal(); // use `string`
class Exercise {
public:
    typedef double Type;
    Type setVal(Type); // use `double`
    Type initVal(){return 1;} // use `double`
private:
    int val = 0;
};
int val = 10;
Exercise::Type Exercise::setVal(Type parm) {  // first is `string`, second is `double`
    // val = parm + initVal();     // Exercise::initVal()
    return val;
}

#endif