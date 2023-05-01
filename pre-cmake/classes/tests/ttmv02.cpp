#include "spffl/tmvpoly.h"
#include "spffl/bit_t.h"

#define pol  tmvpoly<bit_t>
#define zero bit_t(0)
#define one  bit_t(1)

int main(void)
{
	//pol f = pol(one, 3, 0) + pol(one, 0, 3) + pol(one, 0, 0);
	pol f = pol(one, 4, 0) + pol(one, 0, 4) + pol(one, 0, 0);
	std::cout << "f = " << f << "\n";
	std::cout << "\n";

	for (int i = 0; i <= 1; i++) {
		for (int j = 0; j <= 1; j++) {
			bit_t x(i);
			bit_t y(j);
			std::cout << "f(" << x << "," << y << ") = " << f.eval(x,y) << "\n";
		}
	}

	return 0;
}
