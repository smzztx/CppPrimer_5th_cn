#include <iostream>
#include <vector>
struct Base1{
    void print(int) const{
        std::cout<<"Base1 Print Used"<<std::endl;
        };
protected:
        int ival;
        double dval;
        char cval = 'b';
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
    std::string sval = "aaa";
    double dval;
};

struct MI : public Derived, public Base2{

void print(std::vector<double>){};
void print(int x){
    Base1::print(x);
}
void foo(double);

protected:
    int *ival;
    std::vector<double> dvec = {1.0, 2.0, 3.0};
};

int iva;
double dval;
void MI::foo(double cval)
{
    int dval;
    dval = Base1::dval + Derived::dval;
    Base2::fval = dvec.back();
    sval.at(0) = Base1::cval;
}

int main()
{
    MI mi;
    mi.print(42);
    return 0;
}