#ifndef TMVRATSCAN_H
#define TMVRATSCAN_H

#include "spffl/bit_t.h"
#include "spffl/intmod_t.h"
#include "spffl/f2_polymod_t.h"
#include "spffl/f2n_polymod_t.h"
#include "spffl/fp_polymod_t.h"
#include "spffl/tmvrat.h"

int tmvrat_f2_polymod_from_string(tmvrat<f2_polymod_t> &f, char *string, f2_poly_t m);

int tmvrat_f2_polymods_from_file(char *file_name, tvector<tmvrat<f2_polymod_t>> &rats, f2_poly_t m);

int tmvrat_f2_polymods_from_stream(
  std::istream &is, tvector<tmvrat<f2_polymod_t>> &rats, f2_poly_t m);

int tmvrat_fp_polymod_from_string(tmvrat<fp_polymod_t> &f, char *string, fp_poly_t m);

// xxx Code up the remaining data types as well.

#endif // TMVRATSCAN_H
