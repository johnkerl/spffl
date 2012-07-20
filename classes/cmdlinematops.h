// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place, Suite 330, Boston, MA  02111-1307  USA
// ================================================================

#ifndef CMDLINEMATOPS_H
#define CMDLINEMATOPS_H

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
struct matatom_t {
	tmatrix<element_type> mat_val;
	element_type scalar_val;
	int          int_val;
	int          atom_type;
};

template <class element_type>
struct mat_lex_ctx_t {
	int            argi;
	int            argc;
	char        ** argv;
	matatom_t<element_type> atom;
	int            token;
	int            in_pow_rhs;
	element_type   zero;
	element_type   one;
};

#define L_MAT       100
#define L_EOL       101
#define L_UNDEF     102

#define L_PLUS      110
#define L_MINUS     111
#define L_MUL       112
#define L_EXP       115
#define L_UPLUS     120
#define L_UMINUS    121

#define L_INV       130
#define L_DET       131
#define L_KERBAS    132
#define L_RR        133
#define L_RECH      134
#define L_RECHR     135
#define L_RRNZ      136
#define L_RECHNZ    137
#define L_TRANSPOSE 138

#define L_EQ        140
#define L_NE        141
#define L_RANK      142

#define L_LPAREN    200
#define L_RPAREN    201


#define S_M_OP  3 // scalar = op mat, i.e. det
#define M_M_OP  4 // mat = op mat, i.e. left-unary operators
#define M_MM_OP 5 // mat = mat op mat, e.g. almost all.
#define M_MI_OP 6 // mat = mat op int,  e.g. exponentiation
#define I_MM_OP 7 // int = mat op mat, e.g. equality and ordering.
#define I_M_OP  8 // int = mat, e.g. rank.


#define MAT_ATOM     17
#define SCALAR_ATOM  18
#define INT_ATOM     19

template <class element_type>
static void E(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<matatom_t<element_type> > & rstack);

// ----------------------------------------------------------------
template <class element_type>
static const char * mat_token_desc(int t)
{
	switch (t) {
	case L_MAT:       return "matrix";    break;
	case L_EOL:       return "EOL";       break;
	case L_UNDEF:     return "undef";     break;

	case L_PLUS:      return "+";         break;
	case L_MINUS:     return "-";         break;
	case L_MUL:       return "*";         break;
	case L_EXP:       return "^";         break;
	case L_UPLUS:     return "u+";        break;
	case L_UMINUS:    return "u-";        break;

	case L_EQ:        return "==";        break;
	case L_NE:        return "!=";        break;
	case L_RANK:      return "rank";      break;

	case L_INV:       return "inv";       break;
	case L_DET:       return "det";       break;
	case L_KERBAS:    return "kerbas";    break;
	case L_RR:        return "rr";        break;
	case L_RECH:      return "rech";      break;
	case L_RECHR:     return "rechr";     break;
	case L_RRNZ:      return "rrnz";      break;
	case L_RECHNZ:    return "rechnz";    break;
	case L_TRANSPOSE: return "transpose"; break;

	case L_LPAREN:    return "(";         break;
	case L_RPAREN:    return ")";         break;

	default:          return "{???}";     break;
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void matlexinit(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	int     argc,
	char ** argv,
	element_type zero,
	element_type one)
{
	rlex_ctx.argi  = 0;
	rlex_ctx.argc  = argc;
	rlex_ctx.argv  = argv;
	rlex_ctx.token = L_UNDEF;
	rlex_ctx.in_pow_rhs = 0;
	rlex_ctx.zero  = zero;
	rlex_ctx.one   = one;
}

// ----------------------------------------------------------------
template <class element_type>
static void matlexan(
	mat_lex_ctx_t<element_type> & rlex_ctx)
{
	if (rlex_ctx.argi >= rlex_ctx.argc) {
		rlex_ctx.token = L_EOL;
		return;
	}
	char * s = rlex_ctx.argv[rlex_ctx.argi];

	if      (strcmp(s, "+")         == 0) rlex_ctx.token = L_PLUS;
	else if (strcmp(s, "-")         == 0) rlex_ctx.token = L_MINUS;
	else if (strcmp(s, "*")         == 0) rlex_ctx.token = L_MUL;
	else if (strcmp(s, ".")         == 0) rlex_ctx.token = L_MUL;
	else if (strcmp(s, "^")         == 0) rlex_ctx.token = L_EXP;

	else if (strcmp(s, "==")        == 0) rlex_ctx.token = L_EQ;
	else if (strcmp(s, "!=")        == 0) rlex_ctx.token = L_NE;
	else if (strcmp(s, "/=")        == 0) rlex_ctx.token = L_NE;
	else if (strcmp(s, "rank")      == 0) rlex_ctx.token = L_RANK;

	else if (strcmp(s, "det")       == 0) rlex_ctx.token = L_DET;
	else if (strcmp(s, "inv")       == 0) rlex_ctx.token = L_INV;
	else if (strcmp(s, "kerbas")    == 0) rlex_ctx.token = L_KERBAS;
	else if (strcmp(s, "rr")        == 0) rlex_ctx.token = L_RR;
	else if (strcmp(s, "rech")      == 0) rlex_ctx.token = L_RECH;
	else if (strcmp(s, "rechr")     == 0) rlex_ctx.token = L_RECHR;
	else if (strcmp(s, "rrnz")      == 0) rlex_ctx.token = L_RRNZ;
	else if (strcmp(s, "rechnz")    == 0) rlex_ctx.token = L_RECHNZ;
	else if (strcmp(s, "transpose") == 0) rlex_ctx.token = L_TRANSPOSE;

	else if (strcmp(s, "(")         == 0) rlex_ctx.token = L_LPAREN;
	else if (strcmp(s, ")")         == 0) rlex_ctx.token = L_RPAREN;

	else if (strcmp(s, "[")         == 0) rlex_ctx.token = L_LPAREN;
	else if (strcmp(s, "]")         == 0) rlex_ctx.token = L_RPAREN;

	else {
		rlex_ctx.token = L_MAT;
		std::istringstream iss(s, std::ios_base::in);
		if (rlex_ctx.in_pow_rhs) {
			rlex_ctx.atom.atom_type = INT_ATOM;
			iss >> rlex_ctx.atom.int_val;
		}
		else {
			rlex_ctx.atom.mat_val = rlex_ctx.zero; // Set modulus
			rlex_ctx.atom.atom_type = MAT_ATOM;

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
static void emit(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<matatom_t<element_type> > & rstack)
{
	matatom_t<element_type> A, B, C;
	int msiform;

	if (rlex_ctx.token == L_MAT) {
		rstack.push(rlex_ctx.atom);
		return;
	}

	if (rlex_ctx.token == L_UPLUS) {
		// pop & push back -- amounts to leaving as-is.
		return;
	}


	switch (rlex_ctx.token) {
	case L_UMINUS:
	case L_INV:
	case L_KERBAS:
	case L_RR:
	case L_RECH:
	case L_RECHR:
	case L_RRNZ:
	case L_RECHNZ:
	case L_TRANSPOSE:
		msiform = M_M_OP;
		break;

	case L_DET:
		msiform = S_M_OP;
		break;

	case L_PLUS:
	case L_MINUS:
	case L_MUL:
		msiform = M_MM_OP;
		break;

	case L_EXP:
		msiform = M_MI_OP;
		break;

	case L_EQ:
	case L_NE:
		msiform = I_MM_OP;
		break;

	case L_RANK:
		msiform = I_M_OP;
		break;

	default:
		std::cerr << "Unhandled operator "
			<< mat_token_desc<element_type>(rlex_ctx.token)
			<< ".\n";
		exit(1);
		break;
	}

	if ((msiform == M_M_OP) || (msiform == S_M_OP) || (msiform == I_M_OP)) {
		rstack.pop(A);
	}
	else {
		rstack.pop(B);
		rstack.pop(A);
	}

	switch (msiform) {
	case M_M_OP:
	case S_M_OP:
		if (A.atom_type != MAT_ATOM) {
			std::cerr << "Operator "
				<< mat_token_desc<element_type>(rlex_ctx.token)
				<< " requires matrix argument.\n";
			exit(1);
		}
		break;
	case M_MM_OP:
	case I_MM_OP:
		if ((A.atom_type != MAT_ATOM) || (B.atom_type != MAT_ATOM)) {
			std::cerr << "Operator "
				<< mat_token_desc<element_type>(rlex_ctx.token)
				<< " requires two matrix arguments.\n";
			exit(1);
		}
		break;
	case I_M_OP:
		if (A.atom_type != MAT_ATOM) {
			std::cerr << "Operator "
				<< mat_token_desc<element_type>(rlex_ctx.token)
				<< " requires one matrix argument.\n";
			exit(1);
		}
		break;
	case M_MI_OP:
		if ((A.atom_type != MAT_ATOM) || (B.atom_type != INT_ATOM)) {
			std::cerr << "Operator "
				<< mat_token_desc<element_type>(rlex_ctx.token)
				<< " requires one matrix argument "
				<< " and one integer argument.\n";
			exit(1);
		}
		break;
	}

	switch (rlex_ctx.token) {
	case L_UMINUS: C.mat_val = -A.mat_val; break;
	case L_PLUS:   C.mat_val = A.mat_val + B.mat_val; break;
	case L_MINUS:  C.mat_val = A.mat_val - B.mat_val; break;
	case L_MUL:    C.mat_val = A.mat_val * B.mat_val; break;

	case L_EQ: C.int_val = A.mat_val == B.mat_val; break;
	case L_NE: C.int_val = A.mat_val != B.mat_val; break;
	case L_RANK: C.int_val = A.mat_val.get_rank() ; break;

	case L_EXP:
		if (!A.mat_val.exp(B.int_val, C.mat_val)) {
			std::cerr << "Singular.\n";
			exit(1);
		}
		break;

	case L_INV:
		if (!A.mat_val.inverse(C.mat_val)) {
			std::cerr << "Singular.\n";
			exit(1);
		}
		A.mat_val.check_inverse(C.mat_val);
		break;

	case L_TRANSPOSE:
		C.mat_val = A.mat_val.transpose();
		break;

	case L_KERBAS:
		if (!A.mat_val.get_kernel_basis(C.mat_val, rlex_ctx.zero,
			rlex_ctx.one))
		{
			std::cerr << "{empty)\n";
			exit(1);
		}
		A.mat_val.check_kernel_basis(C.mat_val);
		break;

	case L_RR:
		C.mat_val = A.mat_val;
		C.mat_val.row_reduce_below();
		break;

	case L_RECH:
		C.mat_val = A.mat_val;
		C.mat_val.row_echelon_form();
		break;

	case L_RECHR:
		C.mat_val = A.mat_val.flip_horiz();
		C.mat_val.row_echelon_form();
		C.mat_val = C.mat_val.flip_horiz_vert();
		break;

	case L_RRNZ:
		if (!A.mat_val.get_rr_non_zero_rows(C.mat_val)) {
			std::cerr << "{empty)\n";
			exit(1);
		}
		break;

	case L_RECHNZ:
		if (!A.mat_val.get_rech_non_zero_rows(C.mat_val)) {
			std::cerr << "{empty)\n";
			exit(1);
		}
		break;

	case L_DET: C.scalar_val = A.mat_val.det(); break;

	default:
		std::cerr << "Unhandled operator "
			<< mat_token_desc<element_type>(rlex_ctx.token)
			<< ".\n";
		exit(1);
		break;
	}

	switch (msiform) {
	case M_M_OP:
	case M_MM_OP:
	case M_MI_OP:
		C.atom_type = MAT_ATOM;
		break;
	case S_M_OP:
		C.atom_type = SCALAR_ATOM;
		break;
	case I_MM_OP:
		C.atom_type = INT_ATOM;
		break;
	case I_M_OP:
		C.atom_type = INT_ATOM;
		break;
	}

	rstack.push(C);
}

// ----------------------------------------------------------------
template <class element_type>
static void match(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	int expected_token)
{
	if (rlex_ctx.token == expected_token) {
		matlexan<element_type>(rlex_ctx);
	}
	else {
		std::cerr << "Syntax error.\n";
		std::cerr << "Expected "
			<< mat_token_desc<element_type>(expected_token)
			<< "; got "
			<< mat_token_desc<element_type>(rlex_ctx.token)
			<< ".\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void P(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<matatom_t<element_type> > & rstack)
{
	switch (rlex_ctx.token) {
	case L_LPAREN:
		match<element_type>(rlex_ctx, L_LPAREN);
		E<element_type>(rlex_ctx, rstack);
		match<element_type>(rlex_ctx, L_RPAREN);
		break;
	case L_MAT:
		emit<element_type>(rlex_ctx, rstack);
		match<element_type>(rlex_ctx, L_MAT);
		break;
	default:
		std::cerr << "syntax error at token "
			<< mat_token_desc<element_type>(rlex_ctx.token) << "\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void U(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<matatom_t<element_type> > & rstack)
{
	mat_lex_ctx_t<element_type> save;
	P<element_type>(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case L_EXP:
			// This match() gets the next token after the **.
			// Which might be a number (atom), or might be
			// a more complex expression.
			save = rlex_ctx;
			rlex_ctx.in_pow_rhs++;
			match<element_type>(rlex_ctx, rlex_ctx.token);
			P<element_type>(rlex_ctx, rstack);
			emit<element_type>(save, rstack);
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
static void F(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<matatom_t<element_type> > & rstack)
{
	mat_lex_ctx_t<element_type> save;
	switch (rlex_ctx.token) {
	case L_PLUS:
		save = rlex_ctx;
		match<element_type>(rlex_ctx, rlex_ctx.token);
		U<element_type>(rlex_ctx, rstack);
		save.token = L_UPLUS; // Unary operator here
		emit<element_type>(save, rstack);
		break;

	case L_MINUS:
		save = rlex_ctx;
		match<element_type>(rlex_ctx, rlex_ctx.token);
		U<element_type>(rlex_ctx, rstack);
		save.token = L_UMINUS; // Unary operator here
		emit<element_type>(save, rstack);
		break;

	case L_RANK:
	case L_INV:
	case L_DET:
	case L_KERBAS:
	case L_RR:
	case L_RECH:
	case L_RECHR:
	case L_RRNZ:
	case L_RECHNZ:
	case L_TRANSPOSE:
		save = rlex_ctx;
		match<element_type>(rlex_ctx, rlex_ctx.token);
		U<element_type>(rlex_ctx, rstack);
		emit<element_type>(save, rstack);
		break;

	default:
		U<element_type>(rlex_ctx, rstack);
		return;
	}
}

// ----------------------------------------------------------------
template <class element_type>
static void T(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<matatom_t<element_type> > & rstack)
{
	mat_lex_ctx_t<element_type> save;
	F<element_type>(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case L_MUL:
			save = rlex_ctx;
			match<element_type>(rlex_ctx, rlex_ctx.token);
			F<element_type>(rlex_ctx, rstack);
			emit<element_type>(save, rstack);
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
static void E(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<matatom_t<element_type> > & rstack)
{
	mat_lex_ctx_t<element_type> save;
	T<element_type>(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case L_PLUS:
		case L_MINUS:
			save = rlex_ctx;
			match<element_type>(rlex_ctx, rlex_ctx.token);
			T<element_type>(rlex_ctx, rstack);
			emit<element_type>(save, rstack);
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
static void Q(
	mat_lex_ctx_t<element_type> & rlex_ctx,
	tstack<matatom_t<element_type> > & rstack)
{
	mat_lex_ctx_t<element_type> save;
	E<element_type>(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case L_EQ:
		case L_NE:
			save = rlex_ctx;
			match<element_type>(rlex_ctx, rlex_ctx.token);
			E<element_type>(rlex_ctx, rstack);
			emit<element_type>(save, rstack);
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
void cmd_line_mat_parse(
	int argc,
	char ** argv,
	element_type zero,
	element_type one)
{
	mat_lex_ctx_t<element_type> lex_ctx;
	tstack<matatom_t<element_type> > stack;
	matatom_t<element_type> result;

	matlexinit<element_type>(lex_ctx, argc, argv, zero, one);
	matlexan<element_type>(lex_ctx);

	while (lex_ctx.token != L_EOL) {
		Q<element_type>(lex_ctx, stack);
		if (!stack.pop(result)) {
			std::cerr << "Stack underflow.\n";
			exit(1);
		}

		switch (result.atom_type) {
		case MAT_ATOM:
			std::cout << result.mat_val;
			break;
		case SCALAR_ATOM:
			std::cout << result.scalar_val << "\n";
			break;
		case INT_ATOM:
			std::cout << result.int_val << "\n";
			break;
		default:
			std::cerr << "Coding error file " << __FILE__
				<< " line " << __LINE__ << "\n";
			exit(1);
			break;
		}

		// Check for extraneous text.
		match<element_type>(lex_ctx, L_EOL);
	}
}

#endif // CMDLINEMATOPS_H
