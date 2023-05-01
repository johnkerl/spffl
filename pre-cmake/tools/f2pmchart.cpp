// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include "f2_polymod_t.h"
#include "f2_poly_factor.h"
#include "f2_polymod_units.h"
#include "min_char_polys.h"
#include "moebius.h"
#include "log10.h"

// ----------------------------------------------------------------
typedef struct _opts_t {
	int show_orders;
	int show_elements;
	int show_logs;
	int show_normal_rank;
	int show_trace;
	int show_norm;
} opts_t;

// ----------------------------------------------------------------
typedef struct _f2_pm_chart_cell_t {
	f2_polymod_t root;
	int         log;
} f2_pm_chart_cell_t;

typedef struct _f2_pm_chart_row_t {
	f2_poly_t  min_poly;
	int       num_roots;
	int       order;
	f2_pm_chart_cell_t * cells;
} f2_pm_chart_row_t;

typedef struct _f2pm_chart_t {
	int       num_rows;
	f2_polymod_t g;
	f2_pm_chart_row_t * rows;
} f2_pm_chart_t;


// ----------------------------------------------------------------
static int num_irreds_deg_is(
	int       n);

static int num_irreds_deg_divides(
	int       n);

static void find_irreds(
	int       n,
	f2_poly_t * pirreds,
	int       num_irreds);

static f2_pm_chart_t * alloc_f2pm_chart(
	int       num_rows,
	int       num_cols);

static void free_f2pm_chart(
	f2_pm_chart_t ** ppchart);

static int f2pm_chart_row_qcmp(
	const void * pv1,
	const void * pv2);

static void do_f2pm_chart(
	f2_poly_t  m,
	int       n,
	opts_t  * popts);

static void fill_f2pm_chart(
	f2_pm_chart_t * pchart,
	f2_poly_t m,
	int       n);

static void print_f2pm_chart(
	f2_pm_chart_t * pchart,
	f2_poly_t  m,
	int       n,
	opts_t  * popts);

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [options] {m}\n";
	std::cerr << "Or:    " << argv0 << " [options] {:deg}\n";
	std::cerr << "Options:\n";
	std::cerr << "  -o:  Show element orders.\n";
	std::cerr << "  -l:  Show element logs.\n";
	std::cerr << "  -L:  Show elements and logs.\n";
	exit(1);
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	int        argi;
	int        n;
	f2_poly_t  mj;
	int        j;
	opts_t     opts;

	opts.show_orders   = 0;
	opts.show_elements = 1;
	opts.show_logs     = 0;
	opts.show_normal_rank = 0;
	opts.show_trace    = 0;
	opts.show_norm     = 0;

	argi = 1;
	while ((argi < argc) && (argv[argi][0] == '-')) {
		if (strcmp(argv[argi], "-o") == 0) {
			opts.show_orders = 1;
		}
		else if (strcmp(argv[argi], "-l") == 0) {
			opts.show_elements = 0;
			opts.show_logs = 1;
		}
		else if (strcmp(argv[argi], "-L") == 0) {
			opts.show_elements = 1;
			opts.show_logs = 1;
		}
		else if (strcmp(argv[argi], "-nr") == 0) {
			opts.show_normal_rank = 1;
		}
		else if (strcmp(argv[argi], "-t") == 0) {
			opts.show_trace = 1;
		}
		else if (strcmp(argv[argi], "-n") == 0) {
			opts.show_norm = 1;
		}
		else
			usage(argv[0]);
		argi++;
	}

	if ((argc - argi) < 1)
		usage(argv[0]);

	for (; argi < argc; argi++) {

		if (sscanf(argv[argi], ":%u", &n) == 1) {
			int num_irreds = num_irreds_deg_is(n);
			f2_poly_t * pirreds = new f2_poly_t[num_irreds];
			find_irreds(n, pirreds, num_irreds);
			for (j = 0; j < num_irreds; j++) {
				mj = pirreds[j];
				do_f2pm_chart(mj, n, &opts);
			}
			delete [] pirreds;
		}
		else if (mj.from_string(argv[argi])) {
			n = mj.find_degree();
			do_f2pm_chart(mj, n, &opts);
		}
		else {
			usage(argv[0]);
		}
	}

	return 0;
}

// ----------------------------------------------------------------
static int num_irreds_deg_is(
	int       n)
{
	int d, sum = 0;

	for (d = 1; d <= n; d++)
		if ((n % d) == 0)
			sum += calc_moebius(n/d) * (1 << d);
	return sum / n;
}

// ----------------------------------------------------------------
static int num_irreds_deg_divides(
	int       n)
{
	int d, sum = 0;
	for (d = 1; d <= n; d++)
		if ((n % d) == 0)
			sum += num_irreds_deg_is(d);
	return sum;
}

// ----------------------------------------------------------------
static void find_irreds(
	int       n,
	f2_poly_t * pirreds,
	int       num_irreds)
{
	int count = 0;
	f2_poly_t f, flo, fhi;

	flo = f2_poly_t::from_base_rep(1 << n);
	fhi = f2_poly_t::from_base_rep((1 << n+1) - 1);
	for (f = flo; f <= fhi; f.increment()) {
		if (!f2_poly_is_irreducible(f))
			continue;

		if (count >= num_irreds) {
			std::cerr << "Coding error:  too many factors.\n";
			exit(1);
		}
		pirreds[count] = f;
		count++;
	}
}

// ----------------------------------------------------------------
static f2_pm_chart_t * alloc_f2pm_chart(
	int       num_rows,
	int       num_cols)
{
	f2_pm_chart_t * pchart;
	int i, j;

	pchart = new f2_pm_chart_t;
	pchart->num_rows = num_rows;
	pchart->rows = new f2_pm_chart_row_t[num_rows];
	for (i = 0; i < num_rows; i++)
		pchart->rows[i].cells = new f2_pm_chart_cell_t[num_cols];

	for (i = 0; i < num_rows; i++) {
		pchart->rows[i].num_roots = 0;
		pchart->rows[i].order = 0;
		for (j = 0; j < num_cols; j++)
			pchart->rows[i].cells[j].log = 0;
	}

	return pchart;
}

// ----------------------------------------------------------------
static void free_f2pm_chart(
	f2_pm_chart_t ** ppchart)
{
	f2_pm_chart_t * pchart = *ppchart;
	int i;
	for (i = 0; i < pchart->num_rows; i++)
		delete [] pchart->rows[i].cells;
	delete [] pchart->rows;
	delete pchart;
	*ppchart = 0;
}

// ----------------------------------------------------------------
static int f2pm_chart_row_qcmp(
	const void * pv1,
	const void * pv2)
{
	const f2_pm_chart_row_t * prow1 = (const f2_pm_chart_row_t *)pv1;
	const f2_pm_chart_row_t * prow2 = (const f2_pm_chart_row_t *)pv2;
	return (prow1->min_poly > prow2->min_poly);
}

// ----------------------------------------------------------------
static void do_f2pm_chart(
	f2_poly_t m,
	int       n,
	opts_t  * popts)
{
	int num_rows = num_irreds_deg_divides(n);
	num_rows = num_rows;
	f2_pm_chart_t  * pchart = alloc_f2pm_chart(num_rows, n);

	fill_f2pm_chart(pchart, m, n);
	print_f2pm_chart(pchart, m, n, popts);

	free_f2pm_chart(&pchart);
}

// ----------------------------------------------------------------
static void fill_f2pm_chart(
	f2_pm_chart_t * pchart,
	f2_poly_t m,
	int       n)
{
	int pn1 = (1 << n) - 1;
	int i, d, pd1, sfld_log, elt_log, orbit_log, j;
	char * marks;
	f2_polymod_t g, elt;
	int    rowi = 0;
	f2_pm_chart_row_t * prow;

	if (!f2_polymod_find_generator(m, g)) {
		std::cerr << "Couldn't find generator for " << m << ".\n";
		exit(1);
	}
	pchart->g = g;
	marks = new char[pn1];
	for (i = 0; i < pn1; i++)
		marks[i] = 0;

	// Zero
	pchart->rows[rowi].num_roots = 1;
	pchart->rows[rowi].order = 0;
	pchart->rows[rowi].cells[0].log  = 0;
	pchart->rows[rowi].min_poly = f2_polymod_minimal_polynomial(g-g);
	rowi++;

	for (d = 1; d <= n; d++) {
		if ((n % d) != 0)
			continue;
		pd1 = (1 << d) - 1;
		sfld_log = pn1 / pd1;

		for (elt_log = 0; elt_log < pn1; elt_log += sfld_log) {
			if (marks[elt_log])
				continue;

			prow = &pchart->rows[rowi];

			orbit_log = elt_log;
			elt = g.exp(orbit_log);

			prow->min_poly = f2_polymod_minimal_polynomial(elt);
			pchart->rows[rowi].num_roots = d;
			pchart->rows[rowi].order = f2_polymod_order(elt);

			for (j = 0; j < d; j++) {
				marks[orbit_log] = 1;

				prow->cells[j].root = elt;
				prow->cells[j].log  = orbit_log;

				orbit_log *= 2;
				orbit_log %= pn1;
				elt = g.exp(orbit_log);
			}
			rowi++;
		}
	}

	qsort(pchart->rows, pchart->num_rows, sizeof(pchart->rows[0]),
		f2pm_chart_row_qcmp);

	delete [] marks;
}

// ----------------------------------------------------------------
static void print_f2pm_chart(
	f2_pm_chart_t * pchart,
	f2_poly_t  m,
	int       n,
	opts_t  * popts)
{
	int i, j;
	f2_pm_chart_cell_t * pc;
	f2_polymod_t z;
	//int width = calc_log10_unsigned(1<<n, IFLOOR) + 1;

	//std::cout << "Root chart for " << m;
	std::cout << "m=" << m;
	if (popts->show_logs) {
		std::cout << " g=" << pchart->g;
	}
	printf("\n");

	for (i = 0; i < pchart->num_rows; i++) {
		pchart->rows[i].min_poly.dprint(std::cout, n);
		std::cout << ":";

		if (popts->show_orders) {
			//printf(" [o= %*d]", width, pchart->rows[i].order);
			std::cout << " [o= " << pchart->rows[i].order << "]";
		}

//		if (popts->show_normal_rank) {
//			// xxx make getf2pm_chart_tank function
//			int nroots = pchart->rows[i].num_roots;
//			int rank;
//			f2_poly_t * M = malloc_check(
//				nroots * sizeof(f2_poly_t));
//			for (j = 0; j < nroots; j++)
//				M[j] = pchart->rows[i].cells[j].root;
//			z2ila_row_echelon_form(M, nroots);
//			rank = z2ila_find_rank(M, nroots);
//			printf(" [nr= %*d]", width, rank);
//			free(M);
//		}

//		if (popts->show_trace) {
//			// Sum of conjugates
//			printf(" tr=");
//			z2ipoly_print(z2ipolymod_trace(
//				pchart->rows[i].cells[0].root, m));
//		}

//		if (popts->show_norm) {
//			// Product of conjugates
//			printf(" nm=");
//			z2ipoly_print(z2ipolymod_norm(
//				pchart->rows[i].cells[0].root, m));
//		}

		for (j = 0; j < pchart->rows[i].num_roots; j++) {
			pc = &pchart->rows[i].cells[j];
			z  = pc->root;

			std::cout << " ";
			if (popts->show_elements) {
				std::cout << z;
			}
			if (popts->show_logs) {
				if (popts->show_elements)
					std::cout << "(";
				if (z == 0LL)
					//printf("%*s", width, "-");
					std::cout << "-";
				else
					//printf("%*d", width, pchart->rows[i].cells[j].log);
					std::cout << pchart->rows[i].cells[j].log;
				if (popts->show_elements)
					std::cout << ")";
			}
		}
		std::cout << "\n";
	}
	std::cout << "\n";
}
