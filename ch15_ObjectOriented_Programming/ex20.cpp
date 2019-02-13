class Base
{
public:
	void memfcn(Base &b) { b = *this; };
protected:
	int prot_mem;
private:
	char priv_mem;
};

struct Pub_Derv : public Base
{
public:
	void memfcn(Base &b) { b = *this; };
};

struct Priv_Derv : private Base
{
public:
	void memfcn(Base &b) { b = *this; };
};

struct Prot_Derv : protected Base
{
public:
	void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Public : public Pub_Derv
{
public:
	void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Private : public Priv_Derv
{
public:
	// void memfcn(Base &b) { b = *this; };
};

struct Derived_from_Protected : public Prot_Derv
{
public:
	void memfcn(Base &b) { b = *this; };
};

int main()
{
	Pub_Derv d1;
	Priv_Derv d2;
	Prot_Derv d3;
	Derived_from_Public dd1;
	Derived_from_Private dd2;
	Derived_from_Protected dd3;

	Base *p = &d1;
	// p = &d2;
	// p = &d3;
	p = &dd1;
	// p = &dd2;
	// p = &dd3;

	return 0;
}