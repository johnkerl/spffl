#include "spffl/tmvpoly.h"
#include "spffl/f2_polymod_t.h"
#include "spffl/list_elements.h"

// ----------------------------------------------------------------
int main(int argc, char **argv) {
  unsigned im = 0x3;
  if (argc == 2)
    (void)sscanf(argv[1], "%x", &im);

  f2_poly_t m = f2_poly_t::from_base_rep(im);
  f2_polymod_t zero = f2_polymod_t::prime_subfield_element(0, m);
  f2_polymod_t one = f2_polymod_t::prime_subfield_element(1, m);

#if 0
	tmvpoly<f2_polymod_t> f =
		tmvpoly<f2_polymod_t>(one, 3, 0) +
		tmvpoly<f2_polymod_t>(one, 0, 3) +
		tmvpoly<f2_polymod_t>(one, 0, 0);
#endif

#if 1
  tmvpoly<f2_polymod_t> f = tmvpoly<f2_polymod_t>(one, 3, 1) + tmvpoly<f2_polymod_t>(one, 0, 3) +
                            tmvpoly<f2_polymod_t>(one, 1, 0);
#endif

#if 0
	tmvpoly<f2_polymod_t> f =
		tmvpoly<f2_polymod_t>(one, 5, 0) +
		tmvpoly<f2_polymod_t>(one, 0, 5) +
		tmvpoly<f2_polymod_t>(one, 0, 0);
#endif

  std::cout << "f = " << f << "\n";
  tmvpoly<f2_polymod_t> F = f.homogenize();
  std::cout << "F = " << F << "\n";
  std::cout << "\n";

  tvector<f2_polymod_t> Fq = f2_polymod_list(m, 0);
  int oFq = Fq.get_num_elements();

  for (int i = 0; i < oFq; i++) {
    for (int j = 0; j < oFq; j++) {
      f2_polymod_t x = Fq[i];
      f2_polymod_t y = Fq[j];
      f2_polymod_t fxy = f.eval(x, y);
      if (fxy == zero)
        std::cout << "f(" << x << "," << y << ") = " << fxy << "\n";
    }
  }

  return 0;
}
