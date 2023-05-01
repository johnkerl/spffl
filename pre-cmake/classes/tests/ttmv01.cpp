#include "spffl/tmvpoly.h"
#include "spffl/intrat_t.h"

int main(void)
{
	tmvpoly<intrat_t> a(intrat_t(3), 1, 2);
	tmvpoly<intrat_t> b(intrat_t(4), 1, 2);
	tmvpoly<intrat_t> c(intrat_t(5), 2, 2);
	//tmvpoly<intrat_t> c(intrat_t(5), 2, 1);
	tmvpoly<intrat_t> na  = -a;
	tmvpoly<intrat_t> apb = a + b;
	tmvpoly<intrat_t> apc = a + c;
	tmvpoly<intrat_t> bpc = b + c;
	tmvpoly<intrat_t> apbpc = a + b + c;
	tmvpoly<intrat_t> amb = a - b;
	tmvpoly<intrat_t> amc = a - c;
	tmvpoly<intrat_t> bmc = b - c;

	tmvpoly<intrat_t> axb = a * b;
	tmvpoly<intrat_t> axc = a * c;
	tmvpoly<intrat_t> bxc = b * c;
	tmvpoly<intrat_t> axbxc = a * b * c;

	intrat_t x(7);
	intrat_t y(11);

	std::cout << "a     = " << a << "\n";
	std::cout << "b     = " << b << "\n";
	std::cout << "c     = " << c << "\n";
	std::cout << "-a    = " << na << "\n";
	std::cout << "a+b   = " << apb << "\n";
	std::cout << "a+c   = " << apc << "\n";
	std::cout << "b+c   = " << bpc << "\n";
	std::cout << "a-b   = " << amb << "\n";
	std::cout << "a-c   = " << amc << "\n";
	std::cout << "b-c   = " << bmc << "\n";
	std::cout << "a+b+c = " << apbpc << "\n";
	std::cout << "\n";
	std::cout << "a(" << x << "," << y << ") = " << a.eval(x,y) << "\n";
	std::cout << "b(" << x << "," << y << ") = " << b.eval(x,y) << "\n";
	std::cout << "c(" << x << "," << y << ") = " << c.eval(x,y) << "\n";
	std::cout << "a+b+c(" << x << "," << y << ") = " << apbpc.eval(x,y) << "\n";
	std::cout << "\n";
	std::cout << "a*b   = " << axb << "\n";
	std::cout << "a*c   = " << axc << "\n";
	std::cout << "b*c   = " << bxc << "\n";
	std::cout << "a*b*c = " << axbxc << "\n";

	tmvpoly<intrat_t> f =
		tmvpoly<intrat_t>(intrat_t(1), 1, 0) +
		tmvpoly<intrat_t>(intrat_t(2), 0, 1);
	tmvpoly<intrat_t> fxf = f * f;
	std::cout << "f   = " << f << "\n";
	std::cout << "f*f = " << fxf << "\n";

	return 0;
}
