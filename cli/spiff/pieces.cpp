
//#include "tmatrix.h"
//
//#include "int_gcd.h"
//#include "int_totient.h"
//#include "int_random.h"
//#include "int_factor.h"
//#include "isprime.h"
//
//#include "bit_t.h"
//#include "intmod_t.h"
//#include "intrat_t.h"
//#include "intmod_random.h"
//#include "fp_units.h"
//
//#include "spminchar.h"

//#include "f2linalg.h"
//#include "f2poly_t.h"
//#include "f2polymod_t.h"
//#include "f2polyrat_t.h"
//#include "f2poly_random.h"
//#include "f2poly_factor.h"
//#include "f2poly_totient.h"
//#include "f2polymod_random.h"
//#include "f2polymod_units.h"
//#include "f2polymod_convert.h"

//#include "f2npoly_t.h"
//#include "f2npolymod_t.h"
//#include "f2npolyrat_t.h"
//#include "f2npoly_random.h"
//#include "f2npoly_factor.h"
//#include "f2npoly_totient.h"
//#include "f2pmlinalg.h"
//
//#include "f2npolymod_random.h"
//#include "f2npolymod_units.h"
//
//#include "fppoly_t.h"
//#include "fppolymod_t.h"
//#include "fppolyrat_t.h"
//#include "fplinalg.h"
//#include "fppoly_random.h"
//#include "fppoly_factor.h"
//#include "fppoly_totient.h"
//#include "fppolymod_random.h"
//
//#include "fpnpoly_t.h"
//#include "fpnpolymod_t.h"
//
//#include "cmdlineops.h"
//#include "cmdlinematops.h"
//#include "cmdlineedmatops.h"
//#include "cmdlinevecops.h"
//
//#include "sp_list_elts.h"
//
//#include "qff.h"
//#include "cyclopoly.h"

//// ================================================================
//int qop_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_parse<intrat_t>(argc-1, argv+1, intrat_t(0), intrat_t(1));
//	return 0;
//}
//
//int qmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_mat_parse<intrat_t>(argc-1, argv+1, intrat_t(0), intrat_t(1));
//	return 0;
//}
//
//int qvecop_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_vec_parse<intrat_t>(argc-1, argv+1, intrat_t(0), intrat_t(1));
//	return 0;
//}
//
//void qcyclo_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {n}\n";
//	exit(1);
//}
//
//int qpop_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_parse<qpoly_t>(argc-1, argv+1,
//		qpoly_t(intrat_t(0)), qpoly_t(intrat_t(1)));
//	return 0;
//}
//
//int qcyclo_main(int argc, char ** argv, usage_t * pusage)
//{
//	int n;
//	if (argc < 2)
//		pusage(argv[0]);
//	for (int argi = 1; argi < argc; argi++) {
//		if (sscanf(argv[argi], "%d", &n) != 1)
//			pusage(argv[0]);
//		std::cout << get_cyclo_qpoly(n) << std::endl;
//	}
//	return 0;
//}

//int f2op_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_parse<bit_t>(argc-1, argv+1, bit_t(0), bit_t(1));
//	return 0;
//}
//
//void f2random_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [count]\n";
//	exit(1);
//}
//
//int f2random_main(int argc, char ** argv, usage_t * pusage)
//{
//	int count = 1;
//
//	if ((argc != 1) && (argc != 2))
//		pusage(argv[0]);
//	if (argc == 2) {
//		if (sscanf(argv[1], "%d", &count) != 1)
//			pusage(argv[0]);
//	}
//
//	for (int i = 0; i < count; i++)
//		std::cout << (get_random_int() & 1) << std::endl;
//
//	return 0;
//}
//
//int f2matop_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_mat_parse<bit_t>(argc-1, argv+1, bit_t(0), bit_t(1));
//	return 0;
//}
//
//int f2vecop_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_vec_parse<bit_t>(argc-1, argv+1, bit_t(0), bit_t(1));
//	return 0;
//}
//
//void f2matchpol_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {goes here}\n";
//	exit(1);
//}
//
//int f2matchpol_main(int argc, char ** argv, usage_t * pusage)
//{
//	tmatrix<bit_t> A;
//
//	if (argc != 2)
//		pusage(argv[0]);
//	A = bit_t(0);
//	if (!A.load_from_file(argv[1]))
//		pusage(argv[0]);
//	f2poly_t chpol = f2_char_poly(A);
//	std::cout << chpol << std::endl;
//
//	return 0;
//}
//
//void f2matord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {goes here}\n";
//	exit(1);
//}
//
//int f2matord_main(int argc, char ** argv, usage_t * pusage)
//{
//	tmatrix<bit_t> A;
//
//	if (argc != 1)
//		pusage(argv[0]);
//
//	bit_t zero(0);
//	bit_t one (1);
//
//	A = zero;
//	std::cin >> A;
//	bit_t d = A.det();
//
//	if (d == zero) {
//		std::cout << 0 << std::endl;
//	}
//	else {
//		tmatrix<bit_t> I = A.make_I(zero, one);
//		int order;
//		tmatrix<bit_t> Apower = A;
//
//		for (order = 1; ; order++) {
//			if (Apower == I) {
//				std::cout << order << std::endl;
//				return 0;
//			}
//			Apower *= A;
//		}
//
//		std::cout << order << std::endl;
//	}
//
//	return 0;
//}
//
//void f2matrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {# rows} {# cols}\n";
//	exit(1);
//}
//
//int f2matrandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	int nr, nc;
//
//	if (argc != 3)
//		pusage(argv[0]);
//
//	if (sscanf(argv[1], "%d", &nr) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d", &nc) != 1)
//		pusage(argv[0]);
//	tmatrix<bit_t> A(nr, nc);
//	for (int i = 0; i < nr; i++)
//		for (int j = 0; j < nc; j++)
//			A[i][j] = bit_t(get_random_unsigned() & 1);
//	std::cout << A;
//	return 0;
//}

//void f2pqp_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {qpolys ...}\n";
//	exit(1);
//}
//
//int f2pqp_main(int argc, char ** argv, usage_t * pusage)
//{
//	qpoly_t qp;
//	f2poly_t f2p;
//	if (argc < 2)
//		pusage(argv[0]);
//	for (int argi = 1; argi < argc; argi++) {
//		if (!qp.from_string(argv[argi]))
//			pusage(argv[0]);
//		f2p = f2poly_from_qpoly(qp);
//		std::cout << f2p << std::endl;
//	}
//	return 0;
//}

//int f2prop_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_parse<f2polyrat_t>(argc-1, argv+1,
//		f2polyrat_t(0), f2polyrat_t(1));
//	return 0;
//}
//
//void f2prrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {deg} [count]\n";
//	exit(1);
//}
//
//int f2prrandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	int deg, count = 1;
//
//	if ((argc != 2) && (argc != 3))
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &deg) != 1)
//		pusage(argv[0]);
//	if (argc == 3) {
//		if (sscanf(argv[2], "%d", &count) != 1)
//			pusage(argv[0]);
//	}
//
//	f2poly_t zero(0);
//	f2poly_t one(1);
//	for (int i = 0; i < count; i++) {
//		f2poly_t numer = f2poly_random(deg);
//		f2poly_t denom = f2poly_random(deg);
//		if (denom == zero)
//			denom = one;
//		f2polyrat_t q(numer, denom);
//		std::cout << q << std::endl;
//	}
//
//	return 0;
//}
//
//int f2prmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	cmd_line_mat_parse<f2polyrat_t>(argc-1, argv+1,
//		f2polyrat_t(f2poly_t(0)), f2polyrat_t(f2poly_t(1)));
//	return 0;
//}
//
//void f2prmatrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {deg} {num_rows} {num_cols}\n";
//	exit(1);
//}
//
//int f2prmatrandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	int deg, nr, nc;
//
//	if (argc != 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &deg) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d", &nr) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[3], "%d", &nc) != 1)
//		pusage(argv[0]);
//
//	tmatrix<f2polyrat_t> A(nr, nc);
//
//	f2poly_t zero(0);
//	f2poly_t one(1);
//	for (int i = 0; i < nr; i++) {
//		for (int j = 0; j < nc; j++) {
//			f2poly_t numer = f2poly_random(deg);
//			f2poly_t denom = f2poly_random(deg);
//			if (denom == zero)
//				denom = one;
//			A[i][j] = f2polyrat_t(numer, denom);
//		}
//	}
//	std::cout << A << std::endl;
//
//	return 0;
//}
//
//void f2nplist_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {deglo[-deghi]}\n";
//	exit(1);
//}
//
//int f2nplist_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	int deglo, deghi;
//	if (argc != 3)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//
//	if (sscanf(argv[2], "%d-%d", &deglo, &deghi) == 2)
//		;
//	else if (sscanf(argv[2], "%d", &deglo) == 1)
//		deghi = deglo;
//	else
//		pusage(argv[0]);
//	for (int deg = deglo; deg <= deghi; deg++) {
//		tvector<f2npoly_t> elts = f2npoly_list(m, deg);
//		elts.crout(std::cout);
//	}
//	return 0;
//}
//
//void f2npop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {...}\n";
//	exit(1);
//}
//
//int f2npop_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	f2npoly_t zero = f2npoly_t::prime_sfld_elt(0, m);
//	f2npoly_t one  = f2npoly_t::prime_sfld_elt(1, m);
//	cmd_line_parse<f2npoly_t>(argc-2, argv+2, zero, one);
//	return 0;
//}
//
//void f2npmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {...}\n";
//	exit(1);
//}
//
//int f2npmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	f2npoly_t zero = f2npoly_t::prime_sfld_elt(0, m);
//	f2npoly_t one  = f2npoly_t::prime_sfld_elt(1, m);
//	ed_cmd_line_mat_parse<f2npoly_t>(argc-2, argv+2, zero, one);
//	return 0;
//}
//
//void f2npdeg_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
//	exit(1);
//}
//
//int f2npdeg_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//
//	for (int argi = 2; argi < argc; argi++) {
//		f2npoly_t a;
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		if (argc > 3)
//			std::cout << a << ": ";
//		std::cout << a.find_degree() << std::endl;
//	}
//	return 0;
//}
//
//void f2npgcd_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-e] {m} {a} {b}\n";
//	exit(1);
//}
//
//int f2npgcd_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	f2npoly_t a, b, g, r, s;
//
//	if (argc == 4) {
//		if (!m.from_string(argv[1]))
//			pusage(argv[0]);
//		if (!a.from_string(argv[2], m))
//			pusage(argv[0]);
//		if (!b.from_string(argv[3], m))
//			pusage(argv[0]);
//		g = a.gcd(b);
//		std::cout << g << std::endl;
//
//	}
//	else if (argc == 5) {
//		if (strcmp(argv[1], "-e") != 0)
//			pusage(argv[0]);
//		if (!m.from_string(argv[2]))
//			pusage(argv[0]);
//		if (!a.from_string(argv[3], m))
//			pusage(argv[0]);
//		if (!b.from_string(argv[4], m))
//			pusage(argv[0]);
//
//		g = a.ext_gcd(b, r, s);
//		std::cout
//			<< g << " = "
//			<< r << " * "
//			<< a << " + "
//			<< s << " * "
//			<< b << std::endl;
//
//		f2npoly_t check = a * r + b * s;
//		if (g != check) {
//			std::cerr << "Coding error in extended GCD.\n";
//			exit(1);
//		}
//	}
//	else {
//		pusage(argv[0]);
//	}
//
//	return 0;
//}
//
//void f2nplcm_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
//	exit(1);
//}
//
//int f2nplcm_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	f2npoly_t a, l;
//
//	if (argc < 3)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!a.from_string(argv[2], m))
//		pusage(argv[0]);
//	l = a;
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		l = (l * a) / l.gcd(a);
//	}
//	std::cout << l << std::endl;
//	return 0;
//}
//
//void f2nptotient_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
//	exit(1);
//}
//
//int f2nptotient_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	f2npoly_t a;
//	int phi;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	for (int argi = 2; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		phi = f2npoly_totient(a);
//		if (argc > 3)
//			std::cout << a << ": ";
//		std::cout << phi << std::endl;
//	}
//	return 0;
//}
//
//void f2nptest_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
//	exit(1);
//}
//
//int f2nptest_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//
//	for (int argi = 2; argi < argc; argi++) {
//		f2npoly_t a;
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		if (argc > 3)
//			std::cout << a << ": ";
//		if (f2npoly_is_irreducible(a))
//			std::cout << "IRREDUCIBLE\n";
//		else
//			std::cout << "reducible\n";
//	}
//	return 0;
//}
//
//void f2npfind_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-1|-r] {m} {deglo[-deghi]}\n";
//	exit(1);
//}
//
//int f2npfind_main(int argc, char ** argv, usage_t * pusage)
//{
//	int do_random = 0, deglo, deghi;
//	f2poly_t m;
//
//	if (argc != 4)
//		pusage(argv[0]);
//	if (strcmp(argv[1], "-1") == 0)
//		do_random = 0;
//	else if (strcmp(argv[1], "-r") == 0)
//		do_random = 1;
//	else
//		pusage(argv[0]);
//	if (!m.from_string(argv[2]))
//		pusage(argv[0]);
//
//	if (sscanf(argv[3], "%d-%d", &deglo, &deghi) == 2)
//		;
//	else if (sscanf(argv[3], "%d", &deglo) == 1)
//		deghi = deglo;
//	else
//		pusage(argv[0]);
//
//	for (int deg = deglo; deg <= deghi; deg++) {
//		f2npoly_t a;
//		if (do_random)
//			a = f2npoly_random_irr(m, deg);
//		else
//			a = f2npoly_find_irr(m, deg);
//		std::cout << a << std::endl;
//	}
//	return 0;
//}
//
//void f2npfactor_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
//	exit(1);
//}
//
//int f2npfactor_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//
//	for (int argi = 2; argi < argc; argi++) {
//		f2npoly_t a;
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		if (argc > 3)
//			std::cout << a << " = ";
//		tfacinfo<f2npoly_t> finfo = f2npoly_factor(a);
//		std::cout << finfo << std::endl;
//
//		f2poly_t z(1);
//		f2npoly_t one(f2polymod_t(z, m));
//		f2npoly_t check = finfo.unfactor(one);
//		if (check != a) {
//			std::cerr << "Coding error in f2npoly_factor.\n";
//			std::cerr << "  Input: " << a << std::endl;
//			std::cerr << "  Check: " << check << std::endl;
//			std::cerr << "  Factors: " << finfo << std::endl;
//			exit(1);
//		}
//	}
//	return 0;
//}
//
//void f2npdivisors_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-mp] {m} {polys ...}\n";
//	exit(1);
//}
//
//int f2npdivisors_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	f2npoly_t a;
//	int argb = 1;
//	int maximal_proper_only = 0;
//	if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
//		maximal_proper_only = 1;
//		argb++;
//	}
//	if ((argc - argb) < 2)
//		pusage(argv[0]);
//	if (!m.from_string(argv[argb]))
//		pusage(argv[0]);
//	argb++;
//	f2polymod_t c1(f2poly_t(1), m);
//	f2npoly_t one(c1);
//	for (int argi = argb; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		if ((argc - argb) > 1)
//			std::cout << a << ": ";
//		tfacinfo<f2npoly_t> finfo = f2npoly_factor(a);
//		tvector<f2npoly_t> divisors;
//		if (maximal_proper_only) {
//			if (!finfo.get_maximal_proper_divisors(divisors, one)) {
//				std::cout << "(none)\n";
//				continue;
//			}
//		}
//		else {
//			divisors = finfo.get_all_divisors(one);
//		}
//		int nd = divisors.get_num_elements();
//		for (int k = 0; k < nd; k++) {
//			if (k > 0)
//				std::cout << " ";
//			std::cout << divisors[k];
//		}
//		std::cout << std::endl;
//	}
//	return 0;
//}
//
//void f2npeval_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {f} {elements of Fq ...}\n";
//	exit(1);
//}
//
//int f2npeval_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	f2npoly_t f;
//	f2polymod_t a, b;
//
//	if (argc < 4)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!f.from_string(argv[2], m))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		b = f.eval(a);
//		std::cout << b << std::endl;
//	}
//
//	return 0;
//}
//
//void f2nprandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {deg} [count]\n";
//	exit(1);
//}
//
//int f2nprandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	int deg, count = 1;
//
//	if ((argc != 3) && (argc != 4))
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d", &deg) != 1)
//		pusage(argv[0]);
//	if (argc == 4) {
//		if (sscanf(argv[3], "%d", &count) != 1)
//			pusage(argv[0]);
//	}
//
//	for (int i = 0; i < count; i++)
//		std::cout << f2npoly_random(m, deg) << std::endl;
//
//	return 0;
//}
//
//void f2npcompmx_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {poly}\n";
//	exit(1);
//}
//
//int f2npcompmx_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	f2npoly_t chpol;
//
//	if (argc != 3)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!chpol.from_string(argv[2], m))
//		pusage(argv[0]);
//
//	tmatrix<f2polymod_t> A = f2np_companion_matrix(chpol);
//	std::cout << A << std::endl;
//
//	return 0;
//}
//
//void f2npqp_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {qpolys ...}\n";
//	exit(1);
//}
//
//int f2npqp_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	qpoly_t qp;
//	f2npoly_t f2np;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	for (int argi = 2; argi < argc; argi++) {
//		if (!qp.from_string(argv[argi]))
//			pusage(argv[0]);
//		f2np = f2npoly_from_qpoly(qp, m);
//		std::cout << f2np << std::endl;
//	}
//	return 0;
//}
//
//void f2nprop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {...}\n";
//	exit(1);
//}
//
//int f2nprop_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	f2npolyrat_t zero = f2npolyrat_t::prime_sfld_elt(0, m);
//	f2npolyrat_t one  = f2npolyrat_t::prime_sfld_elt(1, m);
//	cmd_line_parse<f2npolyrat_t>(argc-2, argv+2, zero, one);
//	return 0;
//}
//
//void f2npmlist_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-a|-u] {im} {om}\n";
//	exit(1);
//}
//
//int f2npmlist_main(int argc, char ** argv, usage_t * pusage)
//{
//	sp_list_type_t type = SP_LIST_ALL;
//	f2poly_t  im;
//	f2npoly_t om;
//	if (argc != 4)
//		pusage(argv[0]);
//	if (strcmp(argv[1], "-a") == 0)
//		type = SP_LIST_ALL;
//	else if (strcmp(argv[1], "-u") == 0)
//		type = SP_LIST_UNITS;
//	else if (strcmp(argv[1], "-nu") == 0)
//		type = SP_LIST_NON_UNITS;
//	else
//		pusage(argv[0]);
//	if (!im.from_string(argv[2]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[3], im))
//		pusage(argv[0]);
//	tvector<f2npolymod_t> elts = f2npolymod_list(om, type);
//	elts.crout(std::cout);
//	return 0;
//}
//
//void f2npmop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
//	exit(1);
//}
//
//int f2npmop_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[2], im))
//		pusage(argv[0]);
//	f2npolymod_t zero = f2npolymod_t::prime_sfld_elt(0, om);
//	f2npolymod_t one  = f2npolymod_t::prime_sfld_elt(1, om);
//	cmd_line_parse<f2npolymod_t>(argc-3, argv+3, zero, one);
//	return 0;
//}
//
//
//void f2npmtbl_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0
//		<< " {im} {om} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
//	exit(1);
//}
//
//int f2npmtbl_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	f2npolymod_t g;
//	int tbl_type = TBL_TYPE_PLUS;
//	if (argc != 4)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[2], im))
//		pusage(argv[0]);
//
//	if (strcmp(argv[3], "+") == 0)
//		tbl_type = TBL_TYPE_PLUS;
//	else if (strcmp(argv[3], "-") == 0)
//		tbl_type = TBL_TYPE_MINUS;
//	else if (strcmp(argv[3], "*") == 0)
//		tbl_type = TBL_TYPE_MUL;
//	else if (strcmp(argv[3], ".") == 0)
//		tbl_type = TBL_TYPE_MUL;
//	else if (strcmp(argv[3], "u*") == 0)
//		tbl_type = TBL_TYPE_UNIT_MUL;
//	else if (strcmp(argv[3], "u.") == 0)
//		tbl_type = TBL_TYPE_UNIT_MUL;
//	else if (strcmp(argv[3], "/") == 0)
//		tbl_type = TBL_TYPE_UNIT_DIV;
//
//	else if (strncmp(argv[3], "log:", 4) == 0) {
//		if (!g.from_string(&argv[3][4], om))
//			pusage(argv[0]);
//		tbl_type = TBL_TYPE_LOG;
//	}
//	else if (strcmp(argv[3], "log") == 0) {
//		if (!f2npolymod_find_generator(om, g)) {
//			std::cerr << "Couldn't find generator mod "
//				<< om << "\n";
//			exit(1);
//		}
//		tbl_type = TBL_TYPE_LOG;
//	}
//	else if (strncmp(argv[3], "alog:", 5) == 0) {
//		if (!g.from_string(&argv[3][5], om))
//			pusage(argv[0]);
//		tbl_type = TBL_TYPE_ALOG;
//	}
//	else if (strcmp(argv[3], "alog") == 0) {
//		if (!f2npolymod_find_generator(om, g)) {
//			std::cerr << "Couldn't find generator mod "
//				<< om << "\n";
//			exit(1);
//		}
//		tbl_type = TBL_TYPE_ALOG;
//	}
//	else
//		pusage(argv[0]);
//
//	tvector<f2npolymod_t> elts;
//	if ((tbl_type == TBL_TYPE_UNIT_MUL)
//	|| (tbl_type == TBL_TYPE_UNIT_DIV)
//	|| (tbl_type == TBL_TYPE_LOG)
//	|| (tbl_type == TBL_TYPE_ALOG))
//		elts = f2npolymod_list(om, SP_LIST_UNITS);
//	else
//		elts = f2npolymod_list(om, SP_LIST_ALL);
//	int n = elts.get_num_elements();
//
//	if (tbl_type == TBL_TYPE_LOG) {
//		std::cout << "element power\n";
//		std::cout << "------- -----\n";
//		for (int i = 0; i < n; i++) {
//			int e = f2npolymod_log(g, elts[i]);
//			std::cout << elts[i] << " " << e << "\n";
//		}
//		return 0;
//	}
//	if (tbl_type == TBL_TYPE_ALOG) {
//		std::cout << "power element\n";
//		std::cout << "----- -------\n";
//		f2npolymod_t gp = g / g;
//		for (int i = 0; i < n; i++) {
//			std::cout << i << " " << gp << "\n";
//			gp *= g;
//		}
//		return 0;
//	}
//
//	f2npolymod_t a, b, c;
//
//	for (int i = 0; i < n; i++) {
//		a = elts[i];
//		for (int j = 0; j < n; j++) {
//			b = elts[j];
//			switch (tbl_type) {
//			case TBL_TYPE_PLUS:     c = a + b; break;
//			case TBL_TYPE_MINUS:    c = a - b; break;
//			case TBL_TYPE_MUL:      c = a * b; break;
//			case TBL_TYPE_UNIT_MUL: c = a * b; break;
//			case TBL_TYPE_UNIT_DIV: c = a / b; break;
//			}
//			if (j > 0)
//				std::cout << " ";
//			std::cout << c;
//		}
//		std::cout << "\n";
//	}
//
//	return 0;
//}
//
//void f2npmord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {im} {om} {a}\n";
//	exit(1);
//}
//
//int f2npmord_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	f2npolymod_t a;
//	if (argc < 4)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[2], im))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], om))
//			pusage(argv[0]);
//		if (argc > 4)
//			std::cout << a << ": ";
//		std::cout << f2npolymod_order(a) << "\n";
//	}
//	return 0;
//}
//
//void f2npmfindgen_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {im} {om}\n";
//	exit(1);
//}
//
//int f2npmfindgen_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	f2npolymod_t g;
//	int rv = 0;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	for (int argi = 2; argi < argc; argi++) {
//		if (!om.from_string(argv[argi], im))
//			pusage(argv[0]);
//		if (argc > 3)
//			std::cout << om << ": ";
//		if (f2npolymod_find_generator(om, g)) {
//			std::cout << g << "\n";
//		}
//		else {
//			std::cout << "Generator not found.\n";
//			rv = 1;
//		}
//	}
//	return rv;
//}
//
//void f2npmlog_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {im} {om} {g} {a}\n";
//	exit(1);
//}
//
//int f2npmlog_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	f2npolymod_t g, a;
//	if (argc < 5)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[2], im))
//		pusage(argv[0]);
//	if (!g.from_string(argv[3], om))
//		pusage(argv[0]);
//	for (int argi = 4; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], om))
//			pusage(argv[0]);
//		if (argc > 5)
//			std::cout << a << ": ";
//		std::cout << f2npolymod_log(g, a) << "\n";
//	}
//	return 0;
//}
//
//void f2npmchpol_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {im} {m} {residues ...}\n";
//	exit(1);
//}
//
//int f2npmchpol_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t m;
//	f2npolymod_t a;
//
//	if (argc < 4)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], im))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		f2npoly_t cp = f2npm_char_poly(a);
//		if (argc > 4)
//			std::cout << a << ": ";
//		std::cout << cp << "\n";
//	}
//
//	return 0;
//}
//
//void f2npmminpol_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {im} {m} {residues ...}\n";
//	exit(1);
//}
//
//int f2npmminpol_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t m;
//	f2npolymod_t a;
//
//	if (argc < 4)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], im))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		f2npoly_t mp = f2npm_min_poly(a);
//		if (argc > 4)
//			std::cout << a << ": ";
//		std::cout << mp << "\n";
//	}
//
//	return 0;
//}
//
//void f2npmrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} [count]\n";
//	exit(1);
//}
//
//int f2npmrandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	int count = 1;
//
//	if ((argc != 3) && (argc != 4))
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[2], im))
//		pusage(argv[0]);
//	if (argc == 4) {
//		if (sscanf(argv[3], "%d", &count) != 1)
//			pusage(argv[0]);
//	}
//
//	for (int i = 0; i < count; i++)
//		std::cout << f2npolymod_random(im, om) << std::endl;
//
//	return 0;
//}
//
//void f2npmmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
//	exit(1);
//}
//
//int f2npmmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[2], im))
//		pusage(argv[0]);
//	f2npolymod_t zero = f2npolymod_t::prime_sfld_elt(0, om);
//	f2npolymod_t one  = f2npolymod_t::prime_sfld_elt(1, om);
//	cmd_line_mat_parse<f2npolymod_t>(argc-3, argv+3, zero, one);
//	return 0;
//}
//
//void f2npmvecop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
//	exit(1);
//}
//
//int f2npmvecop_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[2], im))
//		pusage(argv[0]);
//	f2npolymod_t zero = f2npolymod_t::prime_sfld_elt(0, om);
//	f2npolymod_t one  = f2npolymod_t::prime_sfld_elt(1, om);
//	cmd_line_vec_parse<f2npolymod_t>(argc-3, argv+3, zero, one);
//	return 0;
//}
//
//void f2npmmatrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0
//		<< " {inner m} {outer m} {# rows} {# cols}\n";
//	exit(1);
//}
//
//int f2npmmatrandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t im;
//	f2npoly_t om;
//	int nr, nc;
//
//	if (argc != 5)
//		pusage(argv[0]);
//	if (!im.from_string(argv[1]))
//		pusage(argv[0]);
//	if (!om.from_string(argv[2], im))
//		pusage(argv[0]);
//	if (sscanf(argv[3], "%d", &nr) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[4], "%d", &nc) != 1)
//		pusage(argv[0]);
//
//	tmatrix<f2npolymod_t> A(nr, nc);
//	for (int i = 0; i < nr; i++)
//		for (int j = 0; j < nc; j++)
//			A[i][j] = f2npolymod_random(im, om);
//	std::cout << A << "\n";
//
//	return 0;
//}
//
//void f2nprmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {inner m} {...}\n";
//	exit(1);
//}
//
//int f2nprmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	f2poly_t m;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (!m.from_string(argv[1]))
//		pusage(argv[0]);
//	f2npolyrat_t zero = f2npolyrat_t::prime_sfld_elt(0, m);
//	f2npolyrat_t one  = f2npolyrat_t::prime_sfld_elt(1, m);
//	cmd_line_mat_parse<f2npolyrat_t>(argc-2, argv+2, zero, one);
//	return 0;
//}
//
//void fplist_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-a|-u] {p}\n";
//	exit(1);
//}
//
//int fplist_main(int argc, char ** argv, usage_t * pusage)
//{
//	sp_list_type_t type = SP_LIST_ALL;
//	int m;
//	// -g
//	// -o {spec}
//	if (argc == 3) {
//		if (strcmp(argv[1], "-a") == 0)
//			type = SP_LIST_ALL;
//		else if (strcmp(argv[1], "-u") == 0)
//			type = SP_LIST_UNITS;
//		else if (strcmp(argv[1], "-nu") == 0)
//			type = SP_LIST_NON_UNITS;
//		else
//			pusage(argv[0]);
//		if (sscanf(argv[2], "%d", &m) != 1)
//			pusage(argv[0]);
//		tvector<intmod_t> elts = intmod_list(m, type);
//		elts.crout(std::cout);
//	}
//	else if (argc == 4) {
//		intmod_t g;
//		if (strcmp(argv[1], "-m") == 0)
//			type = SP_LIST_MULTIPLES;
//		else if (strcmp(argv[1], "-rp") == 0)
//			type = SP_LIST_REL_PRIME;
//		else
//			pusage(argv[0]);
//		if (sscanf(argv[3], "%d", &m) != 1)
//			pusage(argv[0]);
//		if (!g.from_string(argv[2], m))
//			pusage(argv[0]);
//		tvector<intmod_t> elts = intmod_glist(g, type);
//		elts.crout(std::cout);
//	}
//	else {
//		pusage(argv[0]);
//	}
//	return 0;
//}
//void fpop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {...}\n";
//	exit(1);
//}
//
//int fpop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	cmd_line_parse<intmod_t>(argc-2, argv+2,
//		intmod_t(0, p), intmod_t(1, p));
//	return 0;
//}
//
//void fptbl_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
//	exit(1);
//}
//
//int fptbl_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	int tbl_type = TBL_TYPE_PLUS;
//	intmod_t g;
//
//	if (argc != 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//
//	if (strcmp(argv[2], "+") == 0)
//		tbl_type = TBL_TYPE_PLUS;
//	else if (strcmp(argv[2], "-") == 0)
//		tbl_type = TBL_TYPE_MINUS;
//	else if (strcmp(argv[2], "*") == 0)
//		tbl_type = TBL_TYPE_MUL;
//	else if (strcmp(argv[2], ".") == 0)
//		tbl_type = TBL_TYPE_MUL;
//	else if (strcmp(argv[2], "u*") == 0)
//		tbl_type = TBL_TYPE_UNIT_MUL;
//	else if (strcmp(argv[2], "u.") == 0)
//		tbl_type = TBL_TYPE_UNIT_MUL;
//	else if (strcmp(argv[2], "/") == 0)
//		tbl_type = TBL_TYPE_UNIT_DIV;
//
//	else if (strncmp(argv[2], "log:", 4) == 0) {
//		if (!g.from_string(&argv[2][4], p))
//			pusage(argv[0]);
//		tbl_type = TBL_TYPE_LOG;
//	}
//	else if (strcmp(argv[2], "log") == 0) {
//		if (!fp_find_generator(p, g)) {
//			std::cerr << "Couldn't find generator mod "
//				<< p << "\n";
//			exit(1);
//		}
//		tbl_type = TBL_TYPE_LOG;
//	}
//	else if (strncmp(argv[2], "alog:", 5) == 0) {
//		if (!g.from_string(&argv[2][5], p))
//			pusage(argv[0]);
//		tbl_type = TBL_TYPE_ALOG;
//	}
//	else if (strcmp(argv[2], "alog") == 0) {
//		if (!fp_find_generator(p, g)) {
//			std::cerr << "Couldn't find generator mod "
//				<< p << "\n";
//			exit(1);
//		}
//		tbl_type = TBL_TYPE_ALOG;
//	}
//	else
//		pusage(argv[0]);
//
//	tvector<intmod_t> elts;
//	if ((tbl_type == TBL_TYPE_UNIT_MUL)
//	|| (tbl_type == TBL_TYPE_UNIT_DIV)
//	|| (tbl_type == TBL_TYPE_LOG)
//	|| (tbl_type == TBL_TYPE_ALOG))
//		elts = intmod_list(p, SP_LIST_UNITS);
//	else
//		elts = intmod_list(p, SP_LIST_ALL);
//	int n = elts.get_num_elements();
//
//	if (tbl_type == TBL_TYPE_LOG) {
//		std::cout << "element power\n";
//		std::cout << "------- -----\n";
//		for (int i = 0; i < n; i++) {
//			int e = fp_log(g, elts[i]);
//			std::cout << elts[i] << " " << e << "\n";
//		}
//		return 0;
//	}
//	if (tbl_type == TBL_TYPE_ALOG) {
//		std::cout << "power element\n";
//		std::cout << "----- -------\n";
//		intmod_t gp = g / g;
//		for (int i = 0; i < n; i++) {
//			std::cout << i << " " << gp << "\n";
//			gp *= g;
//		}
//		return 0;
//	}
//
//	intmod_t a, b, c;
//
//	for (int i = 0; i < n; i++) {
//		a = elts[i];
//		for (int j = 0; j < n; j++) {
//			b = elts[j];
//			switch (tbl_type) {
//			case TBL_TYPE_PLUS:     c = a + b; break;
//			case TBL_TYPE_MINUS:    c = a - b; break;
//			case TBL_TYPE_MUL:      c = a * b; break;
//			case TBL_TYPE_UNIT_MUL: c = a * b; break;
//			case TBL_TYPE_UNIT_DIV: c = a / b; break;
//			}
//			if (j > 0)
//				std::cout << " ";
//			std::cout << c;
//		}
//		std::cout << "\n";
//	}
//
//	return 0;
//}
//
//void fpord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {a}\n";
//	exit(1);
//}
//
//int fpord_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	intmod_t a;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	for (int argi = 2; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		if (argc > 3)
//			std::cout << a << ": ";
//		std::cout << fp_order(a) << "\n";
//	}
//	return 0;
//}
//
//void fpmaxord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p}\n";
//	exit(1);
//}
//
//int fpmaxord_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	if (argc != 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	tvector<intmod_t> elts = intmod_list(p, SP_LIST_UNITS);
//	int n = elts.get_num_elements();
//	int max = 0;
//	for (int i = 0; i < n; i++) {
//		int cur = fp_order(elts[i]);
//		if (cur > max)
//			max = cur;
//	}
//	std::cout << max << "\n";
//	return 0;
//}
//
//void fporbit_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {a} [a0]\n";
//	exit(1);
//}
//
//int fporbit_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p, a, apower;
//	int a0 = 1;
//	if ((argc != 3) && (argc != 4))
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d", &a) != 1)
//		pusage(argv[0]);
//	if (argc == 4) {
//		if (sscanf(argv[3], "%d", &a0) != 1)
//			pusage(argv[0]);
//	}
//	if (gcd(a, p) != 1) {
//		std::cerr << "fporbit_main: a must be coprime to p.\n";
//		exit(1);
//	}
//
//	a  %= p;
//	a0 %= p;
//	apower = a;
//
//	int counter = 0;
//	while (1) {
//		std::cout << ((apower*a0)%p) << "\n";
//
//		if (apower == 1)
//			break;
//
//		counter++;
//		if (counter > p) {
//			std::cerr << "Internal error finding orbit of "
//				<< a0 << " mod " << p << "\n";
//			exit(1);
//		}
//
//		apower = (apower * a) % p;
//	}
//
//	return 0;
//}
//
//void fpfindgen_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p}\n";
//	exit(1);
//}
//
//int fpfindgen_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	intmod_t g;
//	int rv = 0;
//	if (argc < 2)
//		pusage(argv[0]);
//	for (int argi = 1; argi < argc; argi++) {
//		if (sscanf(argv[argi], "%d", &p) != 1)
//			pusage(argv[0]);
//		if (argc > 2)
//			std::cout << p << ": ";
//		if (fp_find_generator(p, g)) {
//			std::cout << g << "\n";
//		}
//		else {
//			std::cout << "Generator not found.\n";
//			rv = 1;
//		}
//	}
//	return rv;
//}
//
//void fplog_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {g} {a}\n";
//	exit(1);
//}
//
//int fplog_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	intmod_t g, a;
//	if (argc < 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!g.from_string(argv[2], p))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		if (argc > 4)
//			std::cout << a << ": ";
//		std::cout << fp_log(g, a) << "\n";
//	}
//	return 0;
//}
//
//void fprandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} [count]\n";
//	exit(1);
//}
//
//int fprandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	int m, count = 1;
//
//	if ((argc != 2) && (argc != 3))
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &m) != 1)
//		pusage(argv[0]);
//	if (argc == 3) {
//		if (sscanf(argv[2], "%d", &count) != 1)
//			pusage(argv[0]);
//	}
//
//	for (int i = 0; i < count; i++)
//		std::cout << intmod_random(m) << std::endl;
//
//	return 0;
//}
//
//void fpmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
//	exit(1);
//}
//
//int fpmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p = 0;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	cmd_line_mat_parse<intmod_t>(argc-2, argv+2,
//		intmod_t(0, p), intmod_t(1, p));
//	return 0;
//}
//
//void fpvecop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
//	exit(1);
//}
//
//int fpvecop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p = 0;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	cmd_line_vec_parse<intmod_t>(argc-2, argv+2,
//		intmod_t(0, p), intmod_t(1, p));
//	return 0;
//}
//
//void fpmatchpol_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
//	exit(1);
//}
//
//int fpmatchpol_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	tmatrix<intmod_t> A;
//
//	if (argc != 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	A = intmod_t(0, p);
//	if (!A.load_from_file(argv[2]))
//		pusage(argv[0]);
//
//	fppoly_t chpol = fp_char_poly(A);
//	std::cout << chpol << std::endl;
//
//	return 0;
//}
//
//void fpmatord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
//	exit(1);
//}
//
//int fpmatord_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	tmatrix<intmod_t> A;
//
//	if (argc != 2)
//		pusage(argv[0]);
//
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	intmod_t zero(0, p);
//	intmod_t one (1, p);
//
//	A = zero;
//	std::cin >> A;
//	intmod_t d = A.det();
//
//	if (d == zero) {
//		std::cout << 0 << std::endl;
//	}
//	else {
//		tmatrix<intmod_t> I = A.make_I(zero, one);
//		int order;
//		tmatrix<intmod_t> Apower = A;
//
//		for (order = 1; ; order++) {
//			if (Apower == I) {
//				std::cout << order << std::endl;
//				return 0;
//			}
//			Apower *= A;
//		}
//
//		std::cout << order << std::endl;
//	}
//
//	return 0;
//}
//
//void fpmatrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {# rows} {# cols}\n";
//	exit(1);
//}
//
//int fpmatrandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p, nr, nc;
//
//	if (argc != 4)
//		pusage(argv[0]);
//
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d", &nr) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[3], "%d", &nc) != 1)
//		pusage(argv[0]);
//	tmatrix<intmod_t> A(nr, nc);
//	for (int i = 0; i < nr; i++)
//		for (int j = 0; j < nc; j++)
//			A[i][j] = intmod_random(p);
//	std::cout << A;
//	return 0;
//}
//
//void fpplist_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {deglo[-deghi]}\n";
//	exit(1);
//}
//
//int fpplist_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p, deglo, deghi;
//	if (argc != 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d-%d", &deglo, &deghi) == 2)
//		;
//	else if (sscanf(argv[2], "%d", &deglo) == 1)
//		deghi = deglo;
//	else
//		pusage(argv[0]);
//	for (int deg = deglo; deg <= deghi; deg++) {
//		tvector<fppoly_t> elts = fppoly_list(p, deg);
//		elts.crout(std::cout);
//	}
//	return 0;
//}
//
//void fppop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
//	exit(1);
//}
//
//int fppop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	cmd_line_parse<fppoly_t>(argc-2, argv+2,
//		fppoly_t(0, p), fppoly_t(1, p));
//	return 0;
//}
//
//void fppmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
//	exit(1);
//}
//
//int fppmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	ed_cmd_line_mat_parse<fppoly_t>(argc-2, argv+2,
//		fppoly_t(0, p), fppoly_t(1, p));
//	return 0;
//}
//
//void fppcompmx_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {poly}\n";
//	exit(1);
//}
//
//int fppcompmx_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t chpol;
//
//	if (argc != 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!chpol.from_string(argv[2], p))
//		pusage(argv[0]);
//
//	tmatrix<intmod_t> A = fp_companion_matrix(chpol);
//	std::cout << A << "\n";
//
//	return 0;
//}
//
//void fppdeg_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
//	exit(1);
//}
//
//int fppdeg_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//
//	for (int argi = 2; argi < argc; argi++) {
//		fppoly_t a;
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		if (argc > 3)
//			std::cout << a << ": ";
//		std::cout << a.find_degree() << "\n";
//	}
//	return 0;
//}
//
//void fppgcd_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} [-e] {a} {b}\n";
//	exit(1);
//}
//
//int fppgcd_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t a, b, g, r, s;
//
//	if (argc == 4) {
//		if (sscanf(argv[1], "%d", &p) != 1)
//			pusage(argv[0]);
//		if (!a.from_string(argv[2], p))
//			pusage(argv[0]);
//		if (!b.from_string(argv[3], p))
//			pusage(argv[0]);
//		g = a.gcd(b);
//		std::cout << g << std::endl;
//	}
//	else if (argc == 5) {
//		if (strcmp(argv[1], "-e") != 0)
//			pusage(argv[0]);
//		if (sscanf(argv[2], "%d", &p) != 1)
//			pusage(argv[0]);
//		if (!a.from_string(argv[3], p))
//			pusage(argv[0]);
//		if (!b.from_string(argv[4], p))
//			pusage(argv[0]);
//		g = a.ext_gcd(b, r, s);
//		std::cout
//			<< g << " = "
//			<< r << " * "
//			<< a << " + "
//			<< s << " * "
//			<< b << std::endl;
//	}
//	else {
//		pusage(argv[0]);
//	}
//
//	return 0;
//}
//
//void fpplcm_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
//	exit(1);
//}
//
//int fpplcm_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t a, l;
//
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!a.from_string(argv[2], p))
//		pusage(argv[0]);
//	l = a;
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		l = (l * a) / l.gcd(a);
//	}
//	std::cout << l << std::endl;
//	return 0;
//}
//
//void fpptotient_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
//	exit(1);
//}
//
//int fpptotient_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t a;
//	int phi;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	for (int argi = 2; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		phi = fppoly_totient(a);
//		if (argc > 3)
//			std::cout << a << ": ";
//		std::cout << phi << std::endl;
//	}
//	return 0;
//}
//
//void fpptest_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
//	exit(1);
//}
//
//int fpptest_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//
//	for (int argi = 2; argi < argc; argi++) {
//		fppoly_t a;
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		if (argc > 3)
//			std::cout << a << ": ";
//		if (fppoly_is_irreducible(a))
//			std::cout << "IRREDUCIBLE\n";
//		else
//			std::cout << "reducible\n";
//	}
//	return 0;
//}
//
//void fppfind_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-1|-r] {p} {deglo[-deghi]}\n";
//	exit(1);
//}
//
//int fppfind_main(int argc, char ** argv, usage_t * pusage)
//{
//	int do_random = 0, deglo, deghi;
//	int p;
//
//	if (argc != 4)
//		pusage(argv[0]);
//	if (strcmp(argv[1], "-1") == 0)
//		do_random = 0;
//	else if (strcmp(argv[1], "-r") == 0)
//		do_random = 1;
//	else
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d", &p) != 1)
//		pusage(argv[0]);
//
//	if (sscanf(argv[3], "%d-%d", &deglo, &deghi) == 2)
//		;
//	else if (sscanf(argv[3], "%d", &deglo) == 1)
//		deghi = deglo;
//	else
//		pusage(argv[0]);
//
//	for (int deg = deglo; deg <= deghi; deg++) {
//		fppoly_t a;
//		if (do_random)
//			a = fppoly_random_irr(p, deg);
//		else
//			a = fppoly_find_irr(p, deg);
//		std::cout << a << "\n";
//	}
//	return 0;
//}
//
//void fppfactor_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
//	exit(1);
//}
//
//int fppfactor_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t a;
//
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//
//	for (int argi = 2; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		if (argc > 3)
//			std::cout << a << " = ";
//		tfacinfo<fppoly_t> finfo = fppoly_factor(a);
//		std::cout << finfo << "\n";
//
//		fppoly_t check = finfo.unfactor(fppoly_t(intmod_t(1, p)));
//		if (check != a) {
//			std::cerr << "Coding error in fppoly_factor.\n";
//			std::cerr << "  Input: " << a << "\n";
//			std::cerr << "  Check: " << check << "\n";
//			std::cerr << "  Factors: " << finfo << "\n";
//			exit(1);
//		}
//	}
//	return 0;
//}
//
//void fppdivisors_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-mp] {p} {polys ...}\n";
//	exit(1);
//}
//
//int fppdivisors_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t a;
//	int argb = 1;
//	int maximal_proper_only = 0;
//	if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
//		maximal_proper_only = 1;
//		argb++;
//	}
//	if ((argc - argb) < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[argb], "%d", &p) != 1)
//		pusage(argv[0]);
//	argb++;
//	fppoly_t one(intmod_t(1, p));
//	for (int argi = argb; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		if ((argc - argb) > 1)
//			std::cout << a << ": ";
//		tfacinfo<fppoly_t> finfo = fppoly_factor(a);
//		tvector<fppoly_t> divisors;
//		if (maximal_proper_only) {
//			if (!finfo.get_maximal_proper_divisors(divisors, one)) {
//				std::cout << "(none)\n";
//				continue;
//			}
//		}
//		else {
//			divisors = finfo.get_all_divisors(one);
//		}
//		int nd = divisors.get_num_elements();
//		for (int k = 0; k < nd; k++) {
//			if (k > 0)
//				std::cout << " ";
//			std::cout << divisors[k];
//		}
//		std::cout << "\n";
//	}
//	return 0;
//}
//
//void fppeval_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {f} {elements of Fp ...}\n";
//	exit(1);
//}
//
//int fppeval_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t f;
//	intmod_t a, b;
//
//	if (argc < 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!f.from_string(argv[2], p))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], p))
//			pusage(argv[0]);
//		b = f.eval(a);
//		std::cout << b << "\n";
//	}
//
//	return 0;
//}
//
//void fpprandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {deg} [count]\n";
//	exit(1);
//}
//
//int fpprandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p, deg, count = 1;
//
//	if ((argc != 3) && (argc != 4))
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d", &deg) != 1)
//		pusage(argv[0]);
//	if (argc == 4) {
//		if (sscanf(argv[3], "%d", &count) != 1)
//			pusage(argv[0]);
//	}
//
//	for (int i = 0; i < count; i++)
//		std::cout << fppoly_random(p, deg) << std::endl;
//
//	return 0;
//}
//
//void fppqp_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {qpolys ...}\n";
//	exit(1);
//}
//
//int fppqp_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	qpoly_t qp;
//	fppoly_t fpp;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	for (int argi = 2; argi < argc; argi++) {
//		if (!qp.from_string(argv[argi]))
//			pusage(argv[0]);
//		fpp = fppoly_from_qpoly(qp, p);
//		std::cout << fpp << "\n";
//	}
//	return 0;
//}
//
//void fppmlist_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-a|-u] {p} {m}\n";
//	exit(1);
//}
//
//int fppmlist_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//	sp_list_type_t type = SP_LIST_ALL;
//	if (argc != 4)
//		pusage(argv[0]);
//	if (strcmp(argv[1], "-a") == 0)
//		type = SP_LIST_ALL;
//	else if (strcmp(argv[1], "-u") == 0)
//		type = SP_LIST_UNITS;
//	else if (strcmp(argv[1], "-nu") == 0)
//		type = SP_LIST_NON_UNITS;
//	else
//		pusage(argv[0]);
//	if (sscanf(argv[2], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[3], p))
//		pusage(argv[0]);
//	tvector<fppolymod_t> elts = fppolymod_list(m, type);
//	elts.crout(std::cout);
//	return 0;
//}
//
//void fppmop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} {...}\n";
//	exit(1);
//}
//
//int fppmop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	cmd_line_parse<fppolymod_t>(argc-3, argv+3,
//		fppolymod_t::prime_sfld_elt(0, m),
//		fppolymod_t::prime_sfld_elt(1, m));
//	return 0;
//}
//
//void fppmtbl_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} {+|-|*|u*|/}\n";
//	exit(1);
//}
//
//int fppmtbl_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//	fppolymod_t g;
//
//	int tbl_type = TBL_TYPE_PLUS;
//	if (argc != 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//
//	if (strcmp(argv[3], "+") == 0)
//		tbl_type = TBL_TYPE_PLUS;
//	else if (strcmp(argv[3], "-") == 0)
//		tbl_type = TBL_TYPE_MINUS;
//	else if (strcmp(argv[3], "*") == 0)
//		tbl_type = TBL_TYPE_MUL;
//	else if (strcmp(argv[3], ".") == 0)
//		tbl_type = TBL_TYPE_MUL;
//	else if (strcmp(argv[3], "u*") == 0)
//		tbl_type = TBL_TYPE_UNIT_MUL;
//	else if (strcmp(argv[3], "u.") == 0)
//		tbl_type = TBL_TYPE_UNIT_MUL;
//	else if (strcmp(argv[3], "/") == 0)
//		tbl_type = TBL_TYPE_UNIT_DIV;
//
//#if 0
//	else if (strncmp(argv[3], "log:", 4) == 0) {
//		if (!g.from_string(&argv[3][4], m))
//			pusage(argv[0]);
//		tbl_type = TBL_TYPE_LOG;
//	}
//	else if (strcmp(argv[3], "log") == 0) {
//		if (!fppolymod_find_generator(m, g)) {
//			std::cerr << "Couldn't find generator mod "
//				<< m << "\n";
//			exit(1);
//		}
//		tbl_type = TBL_TYPE_LOG;
//	}
//	else if (strncmp(argv[3], "alog:", 5) == 0) {
//		if (!g.from_string(&argv[3][5], m))
//			pusage(argv[0]);
//		tbl_type = TBL_TYPE_ALOG;
//	}
//	else if (strcmp(argv[3], "alog") == 0) {
//		if (!fppolymod_find_generator(m, g)) {
//			std::cerr << "Couldn't find generator mod "
//				<< m << "\n";
//			exit(1);
//		}
//		tbl_type = TBL_TYPE_ALOG;
//	}
//#endif
//	else
//		pusage(argv[0]);
//
//	tvector<fppolymod_t> elts;
//	if ((tbl_type == TBL_TYPE_UNIT_MUL)
//	|| (tbl_type == TBL_TYPE_UNIT_DIV)
//	|| (tbl_type == TBL_TYPE_LOG)
//	|| (tbl_type == TBL_TYPE_ALOG))
//		elts = fppolymod_list(m, SP_LIST_UNITS);
//	else
//		elts = fppolymod_list(m, SP_LIST_ALL);
//	int n = elts.get_num_elements();
//
//#if 0
//	if (tbl_type == TBL_TYPE_LOG) {
//		std::cout << "element power\n";
//		std::cout << "------- -----\n";
//		for (int i = 0; i < n; i++) {
//			int e = fppolymod_log(g, elts[i]);
//			std::cout << elts[i] << " " << e << "\n";
//		}
//		return 0;
//	}
//	if (tbl_type == TBL_TYPE_ALOG) {
//		std::cout << "power element\n";
//		std::cout << "----- -------\n";
//		fppolymod_t gp = g / g;
//		for (int i = 0; i < n; i++) {
//			std::cout << i << " " << gp << "\n";
//			gp *= g;
//		}
//		return 0;
//	}
//#endif
//
//	fppolymod_t a, b, c;
//
//	for (int i = 0; i < n; i++) {
//		a = elts[i];
//		for (int j = 0; j < n; j++) {
//			b = elts[j];
//			switch (tbl_type) {
//			case TBL_TYPE_PLUS:     c = a + b; break;
//			case TBL_TYPE_MINUS:    c = a - b; break;
//			case TBL_TYPE_MUL:      c = a * b; break;
//			case TBL_TYPE_UNIT_MUL: c = a * b; break;
//			case TBL_TYPE_UNIT_DIV: c = a / b; break;
//			}
//			if (j > 0)
//				std::cout << " ";
//			std::cout << c;
//		}
//		std::cout << "\n";
//	}
//
//	return 0;
//}
//
//int fppmmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	cmd_line_mat_parse<fppolymod_t>(argc-3, argv+3,
//		fppolymod_t::prime_sfld_elt(0, m),
//		fppolymod_t::prime_sfld_elt(1, m));
//	return 0;
//}
//
//int fppmvecop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	cmd_line_vec_parse<fppolymod_t>(argc-3, argv+3,
//		fppolymod_t::prime_sfld_elt(0, m),
//		fppolymod_t::prime_sfld_elt(1, m));
//	return 0;
//}
//
//void fppmmatord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} {goes here}\n";
//	exit(1);
//}
//
//int fppmmatord_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//
//	if ((argc != 3) && (argc != 4))
//		pusage(argv[0]);
//
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//
//	fppolymod_t zero = fppolymod_t::prime_sfld_elt(0, m);
//	fppolymod_t one  = fppolymod_t::prime_sfld_elt(1, m);
//
//	tmatrix<fppolymod_t> A;
//	A = zero;
//	std::cin >> A;
//	fppolymod_t d = A.det();
//
//	if (d == zero) {
//		std::cout << 0 << std::endl;
//	}
//	else {
//		tmatrix<fppolymod_t> I = A.make_I(zero, one);
//		int order;
//		tmatrix<fppolymod_t> Apower = A;
//
//		for (order = 1; ; order++) {
//			if (Apower == I) {
//				std::cout << order << std::endl;
//				return 0;
//			}
//			Apower *= A;
//		}
//
//		std::cout << order << std::endl;
//	}
//
//	return 0;
//}
//
//void fppmmatrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} {# rows} {# cols}\n";
//	exit(1);
//}
//
//int fppmmatrandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p, nr, nc;
//	fppoly_t m;
//
//	if (argc != 5)
//		pusage(argv[0]);
//
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	if (sscanf(argv[3], "%d", &nr) != 1)
//		pusage(argv[0]);
//	if (sscanf(argv[4], "%d", &nc) != 1)
//		pusage(argv[0]);
//
//	tmatrix<fppolymod_t> A(nr, nc);
//	for (int i = 0; i < nr; i++)
//		for (int j = 0; j < nc; j++)
//			A[i][j] = fppolymod_random(m);
//	std::cout << A;
//	return 0;
//}
//
//void fppmord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} {a}\n";
//	exit(1);
//}
//
//int fppmord_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//	fppolymod_t a;
//
//	if (argc != 4)
//		pusage(argv[0]);
//
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	if (!a.from_string(argv[3], m))
//		pusage(argv[0]);
//
//	fppolymod_t ai;
//	if (!a.recip(ai)) {
//		std::cout << 0 << std::endl;
//		return 0;
//	}
//
//	fppolymod_t zero(intmod_t(0, p), m);
//	fppolymod_t one (intmod_t(1, p), m);
//	int order;
//	fppolymod_t apower = a;
//
//	for (order = 1; ; order++) {
//		if (apower == one) {
//			std::cout << order << std::endl;
//			return 0;
//		}
//		apower *= a;
//	}
//
//	std::cout << order << std::endl;
//
//	return 0;
//}
//
//void fppmchpol_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} {residues ...}\n";
//	exit(1);
//}
//
//int fppmchpol_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//	fppolymod_t a;
//
//	if (argc < 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		fppoly_t cp = fppm_char_poly(a);
//		if (argc > 4)
//			std::cout << a << ": ";
//		std::cout << cp << "\n";
//	}
//
//	return 0;
//}
//
//void fppmminpol_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} {residues ...}\n";
//	exit(1);
//}
//
//int fppmminpol_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//	fppolymod_t a;
//
//	if (argc < 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!a.from_string(argv[argi], m))
//			pusage(argv[0]);
//		fppoly_t cp = fppm_min_poly(a);
//		if (argc > 4)
//			std::cout << a << ": ";
//		std::cout << cp << "\n";
//	}
//
//	return 0;
//}
//
//void fppmrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} [count]\n";
//	exit(1);
//}
//
//int fppmrandom_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p, count = 1;
//	fppoly_t m;
//
//	if ((argc != 3) && (argc != 4))
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	if (argc == 4) {
//		if (sscanf(argv[3], "%d", &count) != 1)
//			pusage(argv[0]);
//	}
//
//	for (int i = 0; i < count; i++)
//		std::cout << fppolymod_random(m) << std::endl;
//
//	return 0;
//}
//
//void fpprop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {...}\n";
//	exit(1);
//}
//
//int fpprop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	cmd_line_parse<fppolyrat_t>(argc-2, argv+2,
//		fppolyrat_t::prime_sfld_elt(0, p),
//		fppolyrat_t::prime_sfld_elt(1, p));
//	return 0;
//}
//
//void fpprmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {...}\n";
//	exit(1);
//}
//
//int fpprmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	if (argc < 2)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	cmd_line_mat_parse<fppolyrat_t>(argc-2, argv+2,
//		fppolyrat_t::prime_sfld_elt(0, p),
//		fppolyrat_t::prime_sfld_elt(1, p));
//	return 0;
//}
//
//// ----------------------------------------------------------------
//void fpnpop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {im} {...}\n";
//	exit(1);
//}
//
//int fpnpop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t im;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!im.from_string(argv[2], p))
//		pusage(argv[0]);
//	fpnpoly_t zero = fpnpoly_t::prime_sfld_elt(0, im);
//	fpnpoly_t one  = fpnpoly_t::prime_sfld_elt(1, im);
//	cmd_line_parse<fpnpoly_t>(argc-3, argv+3, zero, one);
//	return 0;
//}
//
//// ----------------------------------------------------------------
//void fpnpmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {im} {...}\n";
//	exit(1);
//}
//
//int fpnpmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t im;
//	if (argc < 3)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!im.from_string(argv[2], p))
//		pusage(argv[0]);
//	fpnpoly_t zero = fpnpoly_t::prime_sfld_elt(0, im);
//	fpnpoly_t one  = fpnpoly_t::prime_sfld_elt(1, im);
//	ed_cmd_line_mat_parse<fpnpoly_t>(argc-3, argv+3, zero, one);
//	return 0;
//}
//
//void fpnpgcd_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-e] {p} {im} {a} {b}\n";
//	exit(1);
//}
//
//int fpnpgcd_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t im;
//	fpnpoly_t a, b, g, r, s;
//
//	if (argc == 5) {
//		if (sscanf(argv[1], "%d", &p) != 1)
//			pusage(argv[0]);
//		if (!im.from_string(argv[2], p))
//			pusage(argv[0]);
//		if (!a.from_string(argv[3], im))
//			pusage(argv[0]);
//		if (!b.from_string(argv[4], im))
//			pusage(argv[0]);
//		g = a.gcd(b);
//		std::cout << g << std::endl;
//	}
//	else if (argc == 6) {
//		if (strcmp(argv[1], "-e") != 0)
//			pusage(argv[0]);
//		if (sscanf(argv[2], "%d", &p) != 1)
//			pusage(argv[0]);
//		if (!im.from_string(argv[3], p))
//			pusage(argv[0]);
//		if (!a.from_string(argv[4], im))
//			pusage(argv[0]);
//		if (!b.from_string(argv[5], im))
//			pusage(argv[0]);
//		g = a.ext_gcd(b, r, s);
//		std::cout
//			<< g << " = "
//			<< r << " * "
//			<< a << " + "
//			<< s << " * "
//			<< b << std::endl;
//	}
//	else {
//		pusage(argv[0]);
//	}
//
//	return 0;
//}
//
//void fpnpqp_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {m} {qpolys ...}\n";
//	exit(1);
//}
//
//int fpnpqp_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t m;
//	qpoly_t qp;
//	fpnpoly_t fpnp;
//	if (argc < 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!m.from_string(argv[2], p))
//		pusage(argv[0]);
//	for (int argi = 3; argi < argc; argi++) {
//		if (!qp.from_string(argv[argi]))
//			pusage(argv[0]);
//		fpnp = fpnpoly_from_qpoly(qp, m);
//		std::cout << fpnp << "\n";
//	}
//	return 0;
//}
//
//// ----------------------------------------------------------------
//void fpnpmop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
//	exit(1);
//}
//
//int fpnpmop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t im;
//	fpnpoly_t om;
//	if (argc < 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!im.from_string(argv[2], p))
//		pusage(argv[0]);
//	if (!om.from_string(argv[3], im))
//		pusage(argv[0]);
//	fpnpolymod_t zero = fpnpolymod_t::prime_sfld_elt(0, om);
//	fpnpolymod_t one  = fpnpolymod_t::prime_sfld_elt(1, om);
//	cmd_line_parse<fpnpolymod_t>(argc-4, argv+4, zero, one);
//	return 0;
//}
//
//// ----------------------------------------------------------------
//void fpnpmmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
//	exit(1);
//}
//
//int fpnpmmatop_main(int argc, char ** argv, usage_t * pusage)
//{
//	int p;
//	fppoly_t im;
//	fpnpoly_t om;
//	if (argc < 4)
//		pusage(argv[0]);
//	if (sscanf(argv[1], "%d", &p) != 1)
//		pusage(argv[0]);
//	if (!im.from_string(argv[2], p))
//		pusage(argv[0]);
//	if (!om.from_string(argv[3], im))
//		pusage(argv[0]);
//	fpnpolymod_t zero = fpnpolymod_t::prime_sfld_elt(0, om);
//	fpnpolymod_t one  = fpnpolymod_t::prime_sfld_elt(1, om);
//	cmd_line_mat_parse<fpnpolymod_t>(argc-4, argv+4, zero, one);
//	return 0;
//}

