#include <iostream>
#include <vector>
struct Base1{
    void print(int) const{
        std::cout<<"Base1 Print Used"<<std::endl;
        };
protected:
        int ival;
        double dval;
        char cval;
private:
        int *id;
};
struct Base2 {
    void print(double) const;
protected:
    double fval;
private:
    double dval;
};

struct Derived : public Base1 {
void print(std::string) const;
protected:
    std::string sval;
    double dval;
};

struct MI : public Derived, public Base2{

// void print(std::vector<double>){};
// void print(int x){
//     Base1::print(x);
// }
protected:
    int *ival;
    std::vector<double> dvec;
};

using namespace std;

int main()
{
    MI mi;
    mi.print(42);
    return 0;
}