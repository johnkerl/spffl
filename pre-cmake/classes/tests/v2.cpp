#include <iostream>

// ----------------------------------------------------------------
class A {
public:
	virtual void f(void);
	virtual void g(A & that);
};


void A::f(void)
{
	std::cout << "A::f()" << std::endl;
}

void A::g(A & that)
{
	std::cout << "A::g()" << std::endl;
}

// ----------------------------------------------------------------
class X: public A {
public:
	void f(void);
	void g(X & that);
};

void X::f(void)
{
	std::cout << "X::f()" << std::endl;
}

void X::g(X & that)
{
	std::cout << "X::g()" << std::endl;
}

// ----------------------------------------------------------------
class Y: public A {
public:
	void f(void);
	void g(Y & that);
};

void Y::f(void)
{
	std::cout << "Y::f()" << std::endl;
}

void Y::g(Y & that)
{
	std::cout << "Y::g()" << std::endl;
}

int main(void)
{
	//A a;
	X x;
	Y y;
	X * px = new X;
	Y * py = new Y;
	//a.f();
	px->f();
	px->g(x);
	py->f();
	py->g(y);
	return 0;
}
