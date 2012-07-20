#include <iostream>

class B
{
public:
	B(void) {}
	virtual void foo(void) { std::cout << "Bfoo\n"; }
};

class D : public B
{
public:
	D(void) {}
	void foo(void) { std::cout << "Dfoo\n"; }
};

int main(void)
{
	B * pb = new B();
	B * pd = new D();
	pb->foo();
	pd->foo();
	return 0;
}
