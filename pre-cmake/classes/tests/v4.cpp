#include <iostream>

// ----------------------------------------------------------------
class A {
public:
	virtual void f(void) = 0;
	virtual void g(A & that) = 0;
};

// ----------------------------------------------------------------
class X: public A {
public:
	void f(void);
	void g(A & that);
};

void X::f(void)
{
	std::cout << "X::f()" << std::endl;
}

void X::g(A & that)
{
	std::cout << "X::g()" << std::endl;
}

// ----------------------------------------------------------------
class Y: public A {
public:
	void f(void);
	void g(A & that);
};

void Y::f(void)
{
	std::cout << "Y::f()" << std::endl;
}

void Y::g(A & that)
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
