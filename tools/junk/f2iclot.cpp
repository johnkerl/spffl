
//static int f2ipop_main(int argc, char ** argv)
//{
//	cmd_line_parse<f2ipoly_t>(argc-1, argv+1, f2ipoly_t(0));
//	return 0;
//}
//
//static void f2ipgcd_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " [-e] {poly1} {poly2}\n";
//	exit(1);
//}
//
//static int f2ipgcd_main(int argc, char ** argv)
//{
//	f2ipoly_t a, b, g, r, s;
//
//	if (argc == 3) {
//		if (!a.from_string(argv[1]))
//			f2ipgcd_usage(argv[0]);
//		if (!b.from_string(argv[2]))
//			f2ipgcd_usage(argv[0]);
//
//		g = a.gcd(b);
//		std::cout << g << std::endl;
//
//	}
//	else if (argc == 4) {
//		if (strcmp(argv[1], "-e") != 0)
//			f2ipgcd_usage(argv[0]);
//		if (!a.from_string(argv[2]))
//			f2ipgcd_usage(argv[0]);
//		if (!b.from_string(argv[3]))
//			f2ipgcd_usage(argv[0]);
//
//		g = a.ext_gcd(b, r, s);
//		std::cout
//			<< g << " = "
//			<< r << " * "
//			<< a << " + "
//			<< s << " * "
//			<< b << std::endl;
//
//		f2ipoly_t check = a * r + b * s;
//		if (g != check) {
//			std::cerr << "Coding error in extended GCD.\n";
//			exit(1);
//		}
//	}
//	else {
//		f2ipgcd_usage(argv[0]);
//	}
//
//	return 0;
//}
//
//static void f2ipfactor_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {polys ...}\n";
//	exit(1);
//}
//
//static int f2ipfactor_main(int argc, char ** argv)
//{
//	f2ipoly_t a;
//	for (int argi = 1; argi < argc; argi++) {
//		tfacinfo<f2ipoly_t> finfo;
//		if (!a.from_string(argv[argi]))
//			f2ipfactor_usage(argv[0]);
//		if (argc > 2)
//			std::cout << a << ": ";
//		f2ipoly_factor(a, finfo);
//		std::cout << finfo << "\n";
//
//		f2ipoly_t check = finfo.unfactor(f2ipoly_t(1));
//		if (check != a) {
//			std::cerr << "Coding error in f2ipoly_factor.\n";
//			std::cerr << "  Input: " << a << "\n";
//			std::cerr << "  Check: " << check << "\n";
//			std::cerr << "  Factors: " << finfo << "\n";
//			exit(1);
//		}
//	}
//	return 0;
//}
//
//static void f2iprandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {deg} [count]\n";
//	exit(1);
//}
//
//static int f2iprandom_main(int argc, char ** argv)
//{
//	int deg, count = 1;
//
//	if ((argc != 2) && (argc != 3))
//		f2iprandom_usage(argv[0]);
//	if (sscanf(argv[1], "%d", &deg) != 1)
//		f2iprandom_usage(argv[0]);
//	if (argc == 3) {
//		if (sscanf(argv[2], "%d", &count) != 1)
//			f2iprandom_usage(argv[0]);
//	}
//
//	for (int i = 0; i < count; i++)
//		std::cout << f2ipoly_random(deg) << std::endl;
//
//	return 0;
//}
//
//static void f2ipmop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {a} {b}\n";
//	exit(1);
//}
//
//static int f2ipmop_main(int argc, char ** argv)
//{
//	f2ipoly_t m;
//	if (argc < 2)
//		f2ipmop_usage(argv[0]);
//	if (!m.from_string(argv[1]))
//		f2ipmop_usage(argv[0]);
//	cmd_line_parse<f2ipolymod_t>(argc-2, argv+2, f2ipolymod_t(0, m));
//	return 0;
//}
//
//static void f2ipmord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {a}\n";
//	exit(1);
//}
//
//static int f2ipmord_main(int argc, char ** argv)
//{
//	f2ipoly_t m;
//	f2ipolymod_t a;
//
//	if (argc != 3)
//		f2ipmord_usage(argv[0]);
//
//	if (!m.from_string(argv[1]))
//		f2ipmord_usage(argv[0]);
//	if (!a.from_string(argv[2], m))
//		f2ipmord_usage(argv[0]);
//
//	f2ipolymod_t ai;
//	if (!a.recip(ai)) {
//		std::cout << 0 << std::endl;
//		return 0;
//	}
//
//	f2ipolymod_t zero(0, m);
//	f2ipolymod_t one (1, m);
//	int order;
//	f2ipolymod_t apower = a;
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
//static void f2ipmrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} [count]\n";
//	exit(1);
//}
//
//static int f2ipmrandom_main(int argc, char ** argv)
//{
//	f2ipoly_t m;
//	int count = 1;
//
//	if ((argc != 2) && (argc != 3))
//		f2ipmrandom_usage(argv[0]);
//	if (!m.from_string(argv[1]))
//		f2ipmrandom_usage(argv[0]);
//	if (argc == 3) {
//		if (sscanf(argv[2], "%d", &count) != 1)
//			f2ipmrandom_usage(argv[0]);
//	}
//
//	for (int i = 0; i < count; i++)
//		std::cout << f2ipolymod_random(m) << std::endl;
//
//	return 0;
//}
//
//static void f2ipmmatop_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
//	exit(1);
//}
//
//static int f2ipmmatop_main(int argc, char ** argv)
//{
//	f2ipoly_t m = 0;
//	f2ipolymod_t zero, one;
//
//	if (argc < 2)
//		f2ipmmatop_usage(argv[0]);
//	if (!m.from_string(argv[1]))
//		f2ipmmatop_usage(argv[0]);
//	zero = f2ipolymod_t(f2ipoly_t(0), m);
//	one  = f2ipolymod_t(f2ipoly_t(1), m);
//	cmd_line_mat_parse<f2ipolymod_t>(argc-2, argv+2, zero, one);
//	return 0;
//}
//
//static void f2iprmatrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {deg} {num_rows} {num_cols}\n";
//	exit(1);
//}
//
//static int f2iprmatrandom_main(int argc, char ** argv)
//{
//	int deg, nr, nc;
//
//	if (argc != 4)
//		f2iprmatrandom_usage(argv[0]);
//	if (sscanf(argv[1], "%d", &deg) != 1)
//		f2iprmatrandom_usage(argv[0]);
//	if (sscanf(argv[2], "%d", &nr) != 1)
//		f2iprmatrandom_usage(argv[0]);
//	if (sscanf(argv[3], "%d", &nc) != 1)
//		f2iprmatrandom_usage(argv[0]);
//
//	tmatrix<f2ipolyrat_t> A(nr, nc);
//
//	f2ipoly_t zero(0);
//	f2ipoly_t one(1);
//	for (int i = 0; i < nr; i++) {
//		for (int j = 0; j < nc; j++) {
//			f2ipoly_t numer = f2ipoly_random(deg);
//			f2ipoly_t denom = f2ipoly_random(deg);
//			if (denom == zero)
//				denom = one;
//			A[i][j] = f2ipolyrat_t(numer, denom);
//		}
//	}
//	std::cout << A << std::endl;
//
//	return 0;
//}
//
//static void f2ipmmatord_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
//	exit(1);
//}
//
//static int f2ipmmatord_main(int argc, char ** argv)
//{
//	f2ipoly_t m;
//	tmatrix<f2ipolymod_t> A;
//
//	if (argc != 2)
//		f2ipmmatord_usage(argv[0]);
//
//	if (!m.from_string(argv[1]))
//		f2ipmmatord_usage(argv[0]);
//
//	f2ipolymod_t zero(f2ipoly_t(0), m);
//	f2ipolymod_t one (f2ipoly_t(1), m);
//
//	A = zero;
//	std::cin >> A;
//	f2ipolymod_t d = A.det();
//
//	if (d == zero) {
//		std::cout << 0 << std::endl;
//	}
//	else {
//		tmatrix<f2ipolymod_t> I = A.make_I(zero, one);
//		int order;
//		tmatrix<f2ipolymod_t> Apower = A;
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
//static void f2ipmmatrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {m} {# rows} {# cols}\n";
//	exit(1);
//}
//
//static int f2ipmmatrandom_main(int argc, char ** argv)
//{
//	f2ipoly_t m;
//	int nr, nc;
//
//	if (argc != 4)
//		f2ipmmatrandom_usage(argv[0]);
//
//	if (!m.from_string(argv[1]))
//		f2ipmmatrandom_usage(argv[0]);
//	if (sscanf(argv[2], "%d", &nr) != 1)
//		f2ipmmatrandom_usage(argv[0]);
//	if (sscanf(argv[3], "%d", &nc) != 1)
//		f2ipmmatrandom_usage(argv[0]);
//	tmatrix<f2ipolymod_t> A(nr, nc);
//	for (int i = 0; i < nr; i++)
//		for (int j = 0; j < nc; j++)
//			A[i][j] = f2ipolymod_random(m);
//	std::cout << A;
//	return 0;
//}
//
//static int f2iprop_main(int argc, char ** argv)
//{
//	cmd_line_parse<f2ipolyrat_t>(argc-1, argv+1, f2ipolyrat_t(0));
//	return 0;
//}
//
//static void f2iprrandom_usage(char * argv0)
//{
//	std::cerr << "Usage: " << argv0 << " {deg} [count]\n";
//	exit(1);
//}
//
//static int f2iprrandom_main(int argc, char ** argv)
//{
//	int deg, count = 1;
//
//	if ((argc != 2) && (argc != 3))
//		f2iprrandom_usage(argv[0]);
//	if (sscanf(argv[1], "%d", &deg) != 1)
//		f2iprrandom_usage(argv[0]);
//	if (argc == 3) {
//		if (sscanf(argv[2], "%d", &count) != 1)
//			f2iprrandom_usage(argv[0]);
//	}
//
//	f2ipoly_t zero(0);
//	f2ipoly_t one(1);
//	for (int i = 0; i < count; i++) {
//		f2ipoly_t numer = f2ipoly_random(deg);
//		f2ipoly_t denom = f2ipoly_random(deg);
//		if (denom == zero)
//			denom = one;
//		f2ipolyrat_t q(numer, denom);
//		std::cout << q << std::endl;
//	}
//
//	return 0;
//}
//
//static int f2iprmatop_main(int argc, char ** argv)
//{
//	cmd_line_mat_parse<f2ipolyrat_t>(argc-1, argv+1,
//		f2ipolyrat_t(f2ipoly_t(0)), f2ipolyrat_t(f2ipoly_t(1)));
//	return 0;
//}

