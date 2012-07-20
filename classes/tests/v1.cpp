#include <iostream>

class A {
public:
	virtual void f(void) = 0;
};

class X: public A {
public:
	void f(void);
};

class Y: public A {
public:
	void f(void);
};


void A::f(void)
{
	std::cout << "A::f()" << std::endl;
}

void X::f(void)
{
	std::cout << "X::f()" << std::endl;
}

void Y::f(void)
{
	std::cout << "Y::f()" << std::endl;
}

int main(void)
{
	//A a;
	X * px = new X;
	Y * py = new Y;
	//a.f();
	px->f();
	py->f();
	return 0;
}
