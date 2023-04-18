
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

