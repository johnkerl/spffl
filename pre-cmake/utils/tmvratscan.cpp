#include <iostream>
#include "tmvratscan.h"
#include "tmvpolyscan.h"

// ----------------------------------------------------------------
// Expected format matches that from tmvrat's ostream operator.
// E.g. 2 x^3 y + 4 y z is:
//
//   "2.3.1.0+4.0.1.1"

int tmvrat_f2_polymod_from_string(
	tmvrat<f2_polymod_t> & f,
	char                 * string,
	f2_poly_t               m)
{
	char * cpstring = strdup(string);
	char * pslash = strchr(cpstring, '/');
	if (!pslash) {
		// I don't know how to construct a generic 1.
		std::cerr << "tmvrat_f2_polymod_from_string:  need numerator and denominator.\n";
		exit(1);
	}
	*pslash = 0;
	char * numer_string = cpstring;
	char * denom_string = pslash + 1;
	tmvpoly<f2_polymod_t> numer, denom;

	if (!tmvpoly_f2_polymod_from_string(numer, numer_string, m)) {
		free(cpstring);
		return 0;
	}
	if (!tmvpoly_f2_polymod_from_string(denom, denom_string, m)) {
		free(cpstring);
		return 0;
	}

	tmvrat<f2_polymod_t> rv(numer, denom);
	f = rv;
	return 1;
}

// ----------------------------------------------------------------
int tmvrat_f2_polymods_from_file(
	char                           * file_name,
	tvector< tmvrat<f2_polymod_t> > & rats,
	f2_poly_t                         m)
{
	if ((strcmp(file_name, "-") == 0) || (strcmp(file_name, "@") == 0))
		return tmvrat_f2_polymods_from_stream(std::cin, rats, m);

	std::ifstream ifs;
	ifs.open(file_name, std::ifstream::in);
	if (ifs.fail()) {
		std::cerr << "tmvrat_f2_polymods_from_file:  couldn't open \""
			<< file_name << "\"\n";
		return 0;
	}

	if (!tmvrat_f2_polymods_from_stream(ifs, rats, m)) {
		std::cerr << "tmvrat_f2_polymods_from_file:  scan failure reading \""
			<< file_name << "\"\n";
		ifs.close();
		return 0;
	}
	ifs.close();
	return 1;
}

// ----------------------------------------------------------------
int tmvrat_f2_polymods_from_stream(
	std::istream                   & is,
	tvector< tmvrat<f2_polymod_t> > & rats,
	f2_poly_t                         m)
{
	char line[2048];
	int  rv = 1;

	const int init_num_rats = 10;
	const int more_num_rats = 10;
	tmvrat<f2_polymod_t> * prats = new tmvrat<f2_polymod_t>[init_num_rats];
	int alloc_num_rats = init_num_rats;
	int num_rats = 0;

	while (1) {
		if (is.eof())
			break;

		if (num_rats >= alloc_num_rats) {
			alloc_num_rats += more_num_rats;
			tmvrat<f2_polymod_t> * ptemp = new tmvrat<f2_polymod_t>[alloc_num_rats];
			for (int i = 0; i < num_rats; i++)
				ptemp[i] = prats[i];
			delete [] prats;
			prats = ptemp;
		}

		// Read a line of text.
		is.getline(line, sizeof(line));
		if (is.eof()) {
			is.clear();
			break;
		}
		else if (is.fail()) {
			break;
		}

		// Allow comments.
		char * phash = strstr(line, "#");
		if (phash)
			*phash = 0;

		// Scan
		if (!tmvrat_f2_polymod_from_string(prats[num_rats], line, m)) {
			rv = 0;
			break;
		}
		num_rats++;
	}

	if (is.peek() == EOF)
		is.setstate(std::ios::eofbit);

	if (num_rats == 0) {
		is.setstate(std::ios::badbit);
		std::cerr << "tmvrat_f2_polymods_from_stream >>:  empty file.\n";
	}

	rats = tvector< tmvrat<f2_polymod_t> >(num_rats);
	for (int i = 0; i < num_rats; i++)
		rats[i] = prats[i];
	delete [] prats;
	return rv;
}

// ----------------------------------------------------------------
// Expected format matches that from tmvrat's ostream operator.
// E.g. 2 x^3 y + 4 y z is:
//
//   "2.3.1.0+4.0.1.1"

int tmvrat_fp_polymod_from_string(
	tmvrat<fp_polymod_t> & f,
	char                * string,
	fp_poly_t              m)
{
	char * cpstring = strdup(string);
	char * pslash = strchr(cpstring, '/');
	if (!pslash) {
		// I don't know how to construct a generic 1.
		std::cerr << "tmvrat_fp_polymod_from_string:  need numerator and denominator.\n";
		exit(1);
	}
	*pslash = 0;
	const char * numer_string = cpstring;
	const char * denom_string = pslash + 1;
	tmvpoly<fp_polymod_t> numer, denom;

	if (!tmvpoly_fp_polymod_from_string(numer, numer_string, m)) {
		free(cpstring);
		return 0;
	}
	if (!tmvpoly_fp_polymod_from_string(denom, denom_string, m)) {
		free(cpstring);
		return 0;
	}

	tmvrat<fp_polymod_t> rv(numer, denom);
	f = rv;
	return 1;
}
