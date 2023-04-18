
//void f2nprop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {...}\n";
//	exit(1);
//}
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
