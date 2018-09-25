## 13.1
如果一个构造函数的第一个参数是自身类类型的引用，且任何额外的参数都有默认值，则次构造函数是拷贝构造函数。  
1) 一个对象作为函数参数，以值传递的方式传入函数体；  
2) 一个对象作为函数返回值，以值传递的方式从函数返回；  
3) 一个对象用于给另外一个对象进行初始化（常称为赋值初始化）；  
4) 用花括号列表初始化一个数组中的元素或一个聚合类成员。  

## 13.2
永远也不会调用成功，为了调用拷贝构造函数，我们需要拷贝它的实参，但为了拷贝实参，我们又需要调用拷贝构造函数，如此无限循环。  

## 13.3
拷贝StrBlob时shared_ptr+1，拷贝StrBlobPtr不会。  

## 13.4
```cpp
Point global;
Point foo_bar(Point arg) //1 函数参数
{
    Point local = arg, *heap = new Point(global); //2,3 赋值初始化
    *heap = local;
    Point pa[ 4 ] = { local, *heap }; //4,5 列表初始化
    return *heap; //6 返回值
}
```

## 13.5
```cpp
class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr& hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
private:
    std::string *ps;
    int i;
};
```

## 13.6
拷贝赋值运算符是一个名为operator=的函数，它接受与类相同类型的参数；  
当赋值发生时使用该运算符；  
将右侧运算对象的每个非static成员赋予左侧运算对象的对应成员，对于数组类型的成员，逐个赋值数组元素，合成拷贝赋值运算符返回一个指向其左侧运算对象的引用；  
如果一个类未定义自己的拷贝赋值运算符。  

## 13.7
同13.3一样，赋值StrBlob时shared_ptr+1，赋值StrBlobPtr不会。  

## 13.8
```cpp
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
private:
    std::string *ps;
    int i;
};
```

## 13.9
