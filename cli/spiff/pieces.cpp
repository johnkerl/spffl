
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

