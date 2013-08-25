// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef CMDLINEEDMATOPS_H
#define CMDLINEEDMATOPS_H

// Grammar:
//
//   S := E {terminator}
//   Q := E | E == E | E != E
//   E := T | T + T | T - T
//   T := F | F * F | F / F | F % F
//   F := + U | - U | inv U | det U | kerbas U | rr U | transpose U | U
//   U := P ^ P | P
//   P := ( E ) | NUM

#include <iostream>
#include <sstream>
#include <string>
#include "tmatrix.h"
#include "tstack.h"

template <class element_type>
struct ed_matatom_t {
	tmatrix<element_type> mat_val;
	element_type scalar_val;
	int          int_val;
	int          atom_type;
};

template <class element_type>
struct ed_mat_lex_ctx_t {
	int            argi;
	int            argc;
	char        ** argv;
	ed_matatom_t<element_type> atom;
	int            token;
	int            in_pow_rhs;
	element_type   zero;
	element_type   one;
};

#define ED_L_MAT       100
#define ED_L_EOL       101
#define ED_L_UNDEF     102

#define ED_L_PLUS      110
#define ED_L_MINUS     111
#define ED_L_MUL       112
#define ED_L_EXP       115
#define ED_L_UPLUS     120
#define ED_L_UMINUS    121

#define ED_L_INV       130
#define ED_L_DET       131
#define ED_L_KERBAS    132
#define ED_L_RR        133
#define ED_L_RECH      134
#define ED_L_RECHR     135
#define ED_L_RRNZ      136
#define ED_L_RECHNZ    137
#define ED_L_TRANSPOSE 138

#define ED_L_EQ        140
#define ED_L_NE        141
#define ED_L_RANK      142

#define ED_L_LPAREN    200
#define ED_L_RPAREN    201


#define ED_S_M_OP  3 // scalar = op mat, i.e. det
#define ED_M_M_OP  4 // mat = op mat, i.e. left-unary operators
#define ED_M_MM_OP 5 // mat = mat op mat, e.g. almost all.
#define ED_M_MI_OP 6 // mat = mat op int,  e.g. exponentiation
#define ED_I_MM_OP 7 // int = mat op mat, e.g. equality and ordering.
#define ED_I_M_OP  8 // int = mat, e.g. rank.


#define ED_MAT_ATOM     17
#define ED_SCALAR_ATOM  18
#define ED_INT_ATOM     19

template <class element_type>
static void ed_E(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<ed_matatom_t<element_type> > & rstack);

// ----------------------------------------------------------------
template <class element_type>
static const char * ed_mat_token_desc(int t)
{
	switch (t) {
	case ED_L_MAT:       return "matrix";    break;
	case ED_L_EOL:       return "EOL";       break;
	case ED_L_UNDEF:     return "undef";     break;

	case ED_L_PLUS:      return "+";         break;
	case ED_L_MINUS:     return "-";         break;
	case ED_L_MUL:       return "*";         break;
	case ED_L_EXP:       return "^";         break;
	case ED_L_UPLUS:     return "u+";        break;
	case ED_L_UMINUS:    return "u-";        break;

	case ED_L_EQ:        return "==";        break;
	case ED_L_NE:        return "!=";        break;
	case ED_L_RANK:      return "rank";      break;

	case ED_L_INV:       return "inv";       break;
	case ED_L_DET:       return "det";       break;
	case ED_L_KERBAS:    return "kerbas";    break;
	case ED_L_RR:        return "rr";        break;
	case ED_L_RECH:      return "rech";      break;
	case ED_L_RECHR:     return "rechr";     break;
	case ED_L_RRNZ:      return "rrnz";      break;
	case ED_L_RECHNZ:    return "rechnz";    break;
	case ED_L_TRANSPOSE: return "transpose"; break;

	case ED_L_LPAREN:    return "(";         break;
	case ED_L_RPAREN:    return ")";         break;

	default:          return "{???}";     break;
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_matlexinit(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	int     argc,
	char ** argv,
	element_type zero,
	element_type one)
{
	rlex_ctx.argi  = 0;
	rlex_ctx.argc  = argc;
	rlex_ctx.argv  = argv;
	rlex_ctx.token = ED_L_UNDEF;
	rlex_ctx.in_pow_rhs = 0;
	rlex_ctx.zero  = zero;
	rlex_ctx.one   = one;
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_matlexan(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx)
{
	if (rlex_ctx.argi >= rlex_ctx.argc) {
		rlex_ctx.token = ED_L_EOL;
		return;
	}
	const char * s = rlex_ctx.argv[rlex_ctx.argi];

	if      (strcmp(s, "+")         == 0) rlex_ctx.token = ED_L_PLUS;
	else if (strcmp(s, "-")         == 0) rlex_ctx.token = ED_L_MINUS;
	else if (strcmp(s, "*")         == 0) rlex_ctx.token = ED_L_MUL;
	else if (strcmp(s, ".")         == 0) rlex_ctx.token = ED_L_MUL;
	else if (strcmp(s, "^")         == 0) rlex_ctx.token = ED_L_EXP;

	else if (strcmp(s, "==")        == 0) rlex_ctx.token = ED_L_EQ;
	else if (strcmp(s, "!=")        == 0) rlex_ctx.token = ED_L_NE;
	else if (strcmp(s, "/=")        == 0) rlex_ctx.token = ED_L_NE;
	else if (strcmp(s, "rank")      == 0) rlex_ctx.token = ED_L_RANK;

	else if (strcmp(s, "det")       == 0) rlex_ctx.token = ED_L_DET;
	else if (strcmp(s, "inv")       == 0) rlex_ctx.token = ED_L_INV;
	else if (strcmp(s, "kerbas")    == 0) rlex_ctx.token = ED_L_KERBAS;
	else if (strcmp(s, "rr")        == 0) rlex_ctx.token = ED_L_RR;
	else if (strcmp(s, "rech")      == 0) rlex_ctx.token = ED_L_RECH;
	else if (strcmp(s, "rechr")     == 0) rlex_ctx.token = ED_L_RECHR;
	else if (strcmp(s, "rrnz")      == 0) rlex_ctx.token = ED_L_RRNZ;
	else if (strcmp(s, "rechnz")    == 0) rlex_ctx.token = ED_L_RECHNZ;
	else if (strcmp(s, "transpose") == 0) rlex_ctx.token = ED_L_TRANSPOSE;

	else if (strcmp(s, "(")         == 0) rlex_ctx.token = ED_L_LPAREN;
	else if (strcmp(s, ")")         == 0) rlex_ctx.token = ED_L_RPAREN;

	else if (strcmp(s, "[")         == 0) rlex_ctx.token = ED_L_LPAREN;
	else if (strcmp(s, "]")         == 0) rlex_ctx.token = ED_L_RPAREN;

	else {
		rlex_ctx.token = ED_L_MAT;
		std::istringstream iss(s, std::ios_base::in);
		if (rlex_ctx.in_pow_rhs) {
			rlex_ctx.atom.atom_type = ED_INT_ATOM;
			iss >> rlex_ctx.atom.int_val;
		}
		else {
			rlex_ctx.atom.mat_val = rlex_ctx.zero; // Set modulus
			rlex_ctx.atom.atom_type = ED_MAT_ATOM;

			if (strchr(rlex_ctx.argv[rlex_ctx.argi], '[')) {
				if (!rlex_ctx.atom.mat_val.bracket_in(
					rlex_ctx.argv[rlex_ctx.argi]))
				{
					std::cerr << "Couldn't scan \""
						<< rlex_ctx.argv[rlex_ctx.argi]
						<< "\"\n";
					exit(1);
				}
			}
			else {
				if (!rlex_ctx.atom.mat_val.load_from_file(
					rlex_ctx.argv[rlex_ctx.argi]))
				{
					std::cerr << "Couldn't read \""
						<< rlex_ctx.argv[rlex_ctx.argi]
						<< "\"\n";
					exit(1);
				}
			}
		}
		if (iss.fail()) {
			std::cerr << "Scan failure at \"" << s << "\".\n";
			exit(1);
		}
	}
	rlex_ctx.argi++;
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_emit(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<ed_matatom_t<element_type> > & rstack)
{
	ed_matatom_t<element_type> A, B, C;
	int msiform;

	if (rlex_ctx.token == ED_L_MAT) {
		rstack.push(rlex_ctx.atom);
		return;
	}

	if (rlex_ctx.token == ED_L_UPLUS) {
		// pop & push back -- amounts to leaving as-is.
		return;
	}


	switch (rlex_ctx.token) {
	case ED_L_UMINUS:
	case ED_L_INV:
	case ED_L_KERBAS:
	case ED_L_RR:
	case ED_L_RECH:
	case ED_L_RECHR:
	case ED_L_RRNZ:
	case ED_L_RECHNZ:
	case ED_L_TRANSPOSE:
		msiform = ED_M_M_OP;
		break;

	case ED_L_DET:
		msiform = ED_S_M_OP;
		break;

	case ED_L_PLUS:
	case ED_L_MINUS:
	case ED_L_MUL:
		msiform = ED_M_MM_OP;
		break;

	case ED_L_EXP:
		msiform = ED_M_MI_OP;
		break;

	case ED_L_EQ:
	case ED_L_NE:
		msiform = ED_I_MM_OP;
		break;

	case ED_L_RANK:
		msiform = ED_I_M_OP;
		break;

	default:
		std::cerr << "Unhandled operator "
			<< ed_mat_token_desc<element_type>(rlex_ctx.token)
			<< ".\n";
		exit(1);
		break;
	}

	if ((msiform == ED_M_M_OP) || (msiform == ED_S_M_OP) || (msiform == ED_I_M_OP)) {
		rstack.pop(A);
	}
	else {
		rstack.pop(B);
		rstack.pop(A);
	}

	switch (msiform) {
	case ED_M_M_OP:
	case ED_S_M_OP:
		if (A.atom_type != ED_MAT_ATOM) {
			std::cerr << "Operator "
				<< ed_mat_token_desc<element_type>(rlex_ctx.token)
				<< " requires matrix argument.\n";
			exit(1);
		}
		break;
	case ED_M_MM_OP:
	case ED_I_MM_OP:
		if ((A.atom_type != ED_MAT_ATOM) || (B.atom_type != ED_MAT_ATOM)) {
			std::cerr << "Operator "
				<< ed_mat_token_desc<element_type>(rlex_ctx.token)
				<< " requires two matrix arguments.\n";
			exit(1);
		}
		break;
	case ED_I_M_OP:
		if (A.atom_type != ED_MAT_ATOM) {
			std::cerr << "Operator "
				<< ed_mat_token_desc<element_type>(rlex_ctx.token)
				<< " requires one matrix argument.\n";
			exit(1);
		}
		break;
	case ED_M_MI_OP:
		if ((A.atom_type != ED_MAT_ATOM) || (B.atom_type != ED_INT_ATOM)) {
			std::cerr << "Operator "
				<< ed_mat_token_desc<element_type>(rlex_ctx.token)
				<< " requires one matrix argument "
				<< " and one integer argument.\n";
			exit(1);
		}
		break;
	}

	switch (rlex_ctx.token) {
	case ED_L_UMINUS: C.mat_val = -A.mat_val; break;
	case ED_L_PLUS:   C.mat_val = A.mat_val + B.mat_val; break;
	case ED_L_MINUS:  C.mat_val = A.mat_val - B.mat_val; break;
	case ED_L_MUL:    C.mat_val = A.mat_val * B.mat_val; break;

	case ED_L_EQ: C.int_val = A.mat_val == B.mat_val; break;
	case ED_L_NE: C.int_val = A.mat_val != B.mat_val; break;
	case ED_L_RANK: C.int_val = A.mat_val.get_rank_rr() ; break;

	case ED_L_EXP:
		if (!A.mat_val.exp(B.int_val, C.mat_val)) {
			std::cerr << "Non-invertible.\n";
			exit(1);
		}
		break;

	case ED_L_INV:
		if (!A.mat_val.ed_inverse(C.mat_val)) {
			std::cerr << "Non-invertible.\n";
			exit(1);
		}
		A.mat_val.check_inverse(C.mat_val);
		break;

	case ED_L_TRANSPOSE:
		C.mat_val = A.mat_val.transpose();
		break;

	case ED_L_KERBAS:
		if (!A.mat_val.get_kernel_basis(C.mat_val, rlex_ctx.zero,
			rlex_ctx.one))
		{
			std::cerr << "{empty)\n";
			exit(1);
		}
		A.mat_val.check_kernel_basis(C.mat_val);
		break;

	case ED_L_RR:
		C.mat_val = A.mat_val;
		C.mat_val.ed_row_reduce_below();
		break;

	case ED_L_RECH:
		C.mat_val = A.mat_val;
		C.mat_val.ed_row_echelon_form();
		break;

	case ED_L_RECHR:
		C.mat_val = A.mat_val.flip_horiz();
		C.mat_val.ed_row_echelon_form();
		C.mat_val = C.mat_val.flip_horiz_vert();
		break;

	case ED_L_RRNZ:
		if (!A.mat_val.get_rr_non_zero_rows(C.mat_val)) {
			std::cerr << "{empty)\n";
			exit(1);
		}
		break;

	case ED_L_RECHNZ:
		if (!A.mat_val.get_rech_non_zero_rows(C.mat_val)) {
			std::cerr << "{empty)\n";
			exit(1);
		}
		break;

	case ED_L_DET: C.scalar_val = A.mat_val.ed_det(); break;

	default:
		std::cerr << "Unhandled operator "
			<< ed_mat_token_desc<element_type>(rlex_ctx.token)
			<< ".\n";
		exit(1);
		break;
	}

	switch (msiform) {
	case ED_M_M_OP:
	case ED_M_MM_OP:
	case ED_M_MI_OP:
		C.atom_type = ED_MAT_ATOM;
		break;
	case ED_S_M_OP:
		C.atom_type = ED_SCALAR_ATOM;
		break;
	case ED_I_MM_OP:
		C.atom_type = ED_INT_ATOM;
		break;
	case ED_I_M_OP:
		C.atom_type = ED_INT_ATOM;
		break;
	}

	rstack.push(C);
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_match(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	int expected_token)
{
	if (rlex_ctx.token == expected_token) {
		ed_matlexan<element_type>(rlex_ctx);
	}
	else {
		std::cerr << "Syntax error.\n";
		std::cerr << "Expected "
			<< ed_mat_token_desc<element_type>(expected_token)
			<< "; got "
			<< ed_mat_token_desc<element_type>(rlex_ctx.token)
			<< ".\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_P(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<ed_matatom_t<element_type> > & rstack)
{
	switch (rlex_ctx.token) {
	case ED_L_LPAREN:
		ed_match<element_type>(rlex_ctx, ED_L_LPAREN);
		ed_E<element_type>(rlex_ctx, rstack);
		ed_match<element_type>(rlex_ctx, ED_L_RPAREN);
		break;
	case ED_L_MAT:
		ed_emit<element_type>(rlex_ctx, rstack);
		ed_match<element_type>(rlex_ctx, ED_L_MAT);
		break;
	default:
		std::cerr << "syntax error at token "
			<< ed_mat_token_desc<element_type>(rlex_ctx.token) << "\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_U(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<ed_matatom_t<element_type> > & rstack)
{
	ed_mat_lex_ctx_t<element_type> save;
	ed_P<element_type>(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case ED_L_EXP:
			// This ed_match() gets the next token after the **.
			// Which might be a number (atom), or might be
			// a more complex expression.
			save = rlex_ctx;
			rlex_ctx.in_pow_rhs++;
			ed_match<element_type>(rlex_ctx, rlex_ctx.token);
			ed_P<element_type>(rlex_ctx, rstack);
			ed_emit<element_type>(save, rstack);
			rlex_ctx.in_pow_rhs--;
			continue;
			break;
		default:
			return;
			break;
		}
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_F(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<ed_matatom_t<element_type> > & rstack)
{
	ed_mat_lex_ctx_t<element_type> save;
	switch (rlex_ctx.token) {
	case ED_L_PLUS:
		save = rlex_ctx;
		ed_match<element_type>(rlex_ctx, rlex_ctx.token);
		ed_U<element_type>(rlex_ctx, rstack);
		save.token = ED_L_UPLUS; // Unary operator here
		ed_emit<element_type>(save, rstack);
		break;

	case ED_L_MINUS:
		save = rlex_ctx;
		ed_match<element_type>(rlex_ctx, rlex_ctx.token);
		ed_U<element_type>(rlex_ctx, rstack);
		save.token = ED_L_UMINUS; // Unary operator here
		ed_emit<element_type>(save, rstack);
		break;

	case ED_L_RANK:
	case ED_L_INV:
	case ED_L_DET:
	case ED_L_KERBAS:
	case ED_L_RR:
	case ED_L_RECH:
	case ED_L_RECHR:
	case ED_L_RRNZ:
	case ED_L_RECHNZ:
	case ED_L_TRANSPOSE:
		save = rlex_ctx;
		ed_match<element_type>(rlex_ctx, rlex_ctx.token);
		ed_U<element_type>(rlex_ctx, rstack);
		ed_emit<element_type>(save, rstack);
		break;

	default:
		ed_U<element_type>(rlex_ctx, rstack);
		return;
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_T(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<ed_matatom_t<element_type> > & rstack)
{
	ed_mat_lex_ctx_t<element_type> save;
	ed_F<element_type>(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case ED_L_MUL:
			save = rlex_ctx;
			ed_match<element_type>(rlex_ctx, rlex_ctx.token);
			ed_F<element_type>(rlex_ctx, rstack);
			ed_emit<element_type>(save, rstack);
			continue;
			break;
		default:
			return;
			break;
		}
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_E(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<ed_matatom_t<element_type> > & rstack)
{
	ed_mat_lex_ctx_t<element_type> save;
	ed_T<element_type>(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case ED_L_PLUS:
		case ED_L_MINUS:
			save = rlex_ctx;
			ed_match<element_type>(rlex_ctx, rlex_ctx.token);
			ed_T<element_type>(rlex_ctx, rstack);
			ed_emit<element_type>(save, rstack);
			continue;
			break;
		default:
			return;
			break;
		}
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void ed_Q(
	ed_mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<ed_matatom_t<element_type> > & rstack)
{
	ed_mat_lex_ctx_t<element_type> save;
	ed_E<element_type>(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case ED_L_EQ:
		case ED_L_NE:
			save = rlex_ctx;
			ed_match<element_type>(rlex_ctx, rlex_ctx.token);
			ed_E<element_type>(rlex_ctx, rstack);
			ed_emit<element_type>(save, rstack);
			continue;
			break;
		default:
			return;
			break;
		}
	}
}

// ----------------------------------------------------------------
// The "zero" argument is needed to set the modulus for parameterized types.
template <class element_type>
void ed_cmd_line_mat_parse(
	int argc,
	char ** argv,
	element_type zero,
	element_type one)
{
	ed_mat_lex_ctx_t<element_type> lex_ctx;
	tstack<ed_matatom_t<element_type> > stack;
	ed_matatom_t<element_type> result;

	ed_matlexinit<element_type>(lex_ctx, argc, argv, zero, one);
	ed_matlexan<element_type>(lex_ctx);

	while (lex_ctx.token != ED_L_EOL) {
		ed_Q<element_type>(lex_ctx, stack);
		if (!stack.pop(result)) {
			std::cerr << "Stack underflow.\n";
			exit(1);
		}

		switch (result.atom_type) {
		case ED_MAT_ATOM:
			std::cout << result.mat_val;
			break;
		case ED_SCALAR_ATOM:
			std::cout << result.scalar_val << "\n";
			break;
		case ED_INT_ATOM:
			std::cout << result.int_val << "\n";
			break;
		default:
			std::cerr << "Coding error file " << __FILE__
				<< " line " << __LINE__ << "\n";
			exit(1);
			break;
		}

		// Check for extraneous text.
		ed_match<element_type>(lex_ctx, ED_L_EOL);
	}
}

#endif // CMDLINEEDMATOPS_H
