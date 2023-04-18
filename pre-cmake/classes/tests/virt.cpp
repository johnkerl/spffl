#include <iostream>
#include <iomanip>

// ================================================================
class abs_num_t {
private:
public:
	virtual abs_num_t operator+(abs_num_t that) = 0;
};

// ================================================================
class u8_num_t : public abs_num_t {
public:
	u8_num_t(void);
	u8_num_t(int init);
	u8_num_t(const u8_num_t & that);
	~u8_num_t(void);
	u8_num_t operator=(const u8_num_t & that);
	u8_num_t operator+(abs_num_t & that);
	//friend ostream & operator << (
		//ostream & os,
		//const tvector<ElementType> & v);
	void show(void);

private:
	unsigned char data;
};

u8_num_t::u8_num_t(void)
{
	this->data = 0;
}

u8_num_t::u8_num_t(int init)
{
	this->data = init;
}

u8_num_t u8_num_t::operator=(const u8_num_t & that)
{
	this->data = that.data;
}

u8_num_t::~u8_num_t(void)
{
}

u8_num_t::u8_num_t(const u8_num_t & that)
{
	this->data = that.data;
}

u8_num_t u8_num_t::operator+(abs_num_t & that)
{
	u8_num_t rv;
	rv.data = this->data + ((u8_num_t *)&that)->data;
	return rv;
}

void u8_num_t::show(void)
{
	cout << hex << (unsigned)this->data;
}

// ================================================================
class fe_num_t : public abs_num_t {
public:
	fe_num_t(void);
	fe_num_t(int init);
	fe_num_t(const fe_num_t & that);
	~fe_num_t(void);
	fe_num_t operator=(const fe_num_t & that);
	fe_num_t operator+(abs_num_t & that);
	//friend ostream & operator << (
		//ostream & os,
		//const tvector<ElementType> & v);
	void show(void);

private:
	unsigned char data;
};

fe_num_t::fe_num_t(void)
{
	this->data = 0;
}

fe_num_t::fe_num_t(int init)
{
	this->data = init;
}

fe_num_t fe_num_t::operator=(const fe_num_t & that)
{
	this->data = that.data;
}

fe_num_t::~fe_num_t(void)
{
}

fe_num_t::fe_num_t(const fe_num_t & that)
{
	this->data = that.data;
}

fe_num_t fe_num_t::operator+(abs_num_t & that)
{
	fe_num_t rv;
	rv.data = this->data ^ ((fe_num_t *)&that)->data;
	return rv;
}

void fe_num_t::show(void)
{
	cout << hex << (unsigned)this->data;
}

// ================================================================
static void do_u8(void)
{
	u8_num_t a(0x33);
	u8_num_t b(0x55);
	u8_num_t c;
	c = a + b;
	c.show();
	cout << endl;
}

// ================================================================
static void do_fe(void)
{
	fe_num_t a(0x33);
	fe_num_t b(0x55);
	fe_num_t c;
	c = a + b;
	c.show();
	cout << endl;
}

int main(void)
{
	do_u8();
	do_fe();

	return 0;
}
