// S => E ;
// E => T | T + T | T - T
// T => F | F * F | F / F | F % F
// F => B | - B | + B
// B => P | P ** P
// P => E | ( E ) | num
// ================================================================

#include <iostream>
#include <sstream>
#include "tstack.h"

#define element_type int

typedef struct _lex_ctx_t {
	int            argi;
	int            argc;
	char        ** argv;
	// tv substruct, for save's & for stack too.  w/ union flag.
	element_type   value;
	int            token;
	int            in_pow_rhs;
} lex_ctx_t;

#define L_NUM    100
#define L_NULL   101
#define L_UNDEF  102

#define L_PLUS   110
#define L_MINUS  111
#define L_MUL    112
#define L_DIV    113
#define L_MOD    114
#define L_EXP    115
#define L_UPLUS  120
#define L_UMINUS 121

#define L_ORD    131

#define L_LPAREN 200
#define L_RPAREN 201

static void E(
	lex_ctx_t & rlex_ctx,
	tstack<element_type> & rstack);

// ----------------------------------------------------------------
static char * token_desc(int t)
{
	switch (t) {
	case L_NUM:     return "num";   break;
	case L_NULL:    return "NULL";  break;
	case L_UNDEF:   return "undef"; break;

	case L_PLUS:    return "+";     break;
	case L_MINUS:   return "-";     break;
	case L_MUL:     return "*";     break;
	case L_DIV:     return "/";     break;
	case L_MOD:     return "%";     break;
	case L_EXP:     return "^";     break;
	case L_UPLUS:   return "u+";    break;
	case L_UMINUS:  return "u-";    break;

	case L_ORD:     return "ord";   break;

	case L_LPAREN:  return "(";     break;
	case L_RPAREN:  return ")";     break;
	default:        return "{???}"; break;
	}
}

// ----------------------------------------------------------------
static void lexinit(
	lex_ctx_t & rlex_ctx,
	int     argc,
	char ** argv)
{
	rlex_ctx.argi  = 0;
	rlex_ctx.argc  = argc;
	rlex_ctx.argv  = argv;
	rlex_ctx.token = L_UNDEF;
	rlex_ctx.in_pow_rhs = 0;
}

// ----------------------------------------------------------------
static void lexan(
	lex_ctx_t & rlex_ctx)
{
	if (rlex_ctx.argi >= (rlex_ctx.argc - 1)) {
		rlex_ctx.token = L_NULL;
		return;
	}
	rlex_ctx.argi++;
	char * s = rlex_ctx.argv[rlex_ctx.argi];

	if      (strcmp(s, "+") == 0)
		rlex_ctx.token = L_PLUS;
	else if (strcmp(s, "-") == 0)
		rlex_ctx.token = L_MINUS;
	else if (strcmp(s, "*") == 0)
		rlex_ctx.token = L_MUL;
	else if (strcmp(s, ".") == 0)
		rlex_ctx.token = L_MUL;
	else if (strcmp(s, "/") == 0)
		rlex_ctx.token = L_DIV;
	else if (strcmp(s, "%") == 0)
		rlex_ctx.token = L_MOD;
	else if (strcmp(s, "^") == 0)
		rlex_ctx.token = L_EXP;
	else {
		rlex_ctx.token = L_NUM;
		std::istringstream iss(s, std::ios_base::in);
		if (rlex_ctx.in_pow_rhs) {
			std::cerr << "exponent scan stub.\n";
			exit(1);
		}
		else {
			iss >> rlex_ctx.value;
		}
		if (iss.fail()) {
			std::cerr << "Scan failure at \"" << s << "\".\n";
			exit(1);
		}
	}
}

// ----------------------------------------------------------------
static void emit(
	lex_ctx_t & rlex_ctx,
	tstack<element_type> & rstack)
{
	element_type a, b, c;
#if 0
	if (rlex_ctx.token == L_NUM)
		std::cout << "emit # " << rlex_ctx.value << "\n";
	else
		std::cout << "emit t " << token_desc(rlex_ctx.token) << "\n";
#endif

	switch (rlex_ctx.token) {
	case L_NUM:
		rstack.push(rlex_ctx.value);
		break;

	case L_UPLUS:
		// pop & push back -- amounts to leaving as-is.
		break;
	case L_UMINUS:
		rstack.pop(a);
		a = -a;
		rstack.push(a);
		break;

	case L_PLUS:
		rstack.pop(b); rstack.pop(a); c = a + b; rstack.push(c);
		break;
	case L_MINUS:
		rstack.pop(b); rstack.pop(a); c = a - b; rstack.push(c);
		break;
	case L_MUL:
		rstack.pop(b); rstack.pop(a); c = a * b; rstack.push(c);
		break;
	case L_DIV:
		rstack.pop(b); rstack.pop(a); c = a / b; rstack.push(c);
		break;
	case L_MOD:
		rstack.pop(b); rstack.pop(a); c = a % b; rstack.push(c);
		break;
	// exp
	// ord
	}
}

// ----------------------------------------------------------------
static void match(
	lex_ctx_t & rlex_ctx,
	int expected_token)
{
	if (rlex_ctx.token == expected_token) {
		lexan(rlex_ctx);
	}
	else {
		std::cerr << "Syntax error.\n";
		std::cerr << "Expected " << token_desc(expected_token)
			<< "; got " << token_desc(rlex_ctx.token)
			<< ".\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
static void P(
	lex_ctx_t & rlex_ctx,
	tstack<element_type> & rstack)
{
	switch (rlex_ctx.token) {
	case L_LPAREN:
		match(rlex_ctx, L_LPAREN);
		E(rlex_ctx, rstack);
		match(rlex_ctx, L_RPAREN);
		break;
	case L_NUM:
		emit(rlex_ctx, rstack);
		match(rlex_ctx, L_NUM);
		break;
	default:
		std::cerr << "syntax error at token "
			<< token_desc(rlex_ctx.token) << "\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
static void U(
	lex_ctx_t & rlex_ctx,
	tstack<element_type> & rstack)
{
	lex_ctx_t save;
	P(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
//		case L_GCD: // xxx temp; need to find appropriate precedence.
//		case L_CHOOSE: // xxx temp; need to find appropriate precedence.
		case L_EXP:
			// This match() gets the next token after the **.
			// Which might be a number (atom), or might be
			// a more complex expression.
			save = rlex_ctx;
			rlex_ctx.in_pow_rhs++;
			match(rlex_ctx, rlex_ctx.token);
			P(rlex_ctx, rstack);
			emit(save, rstack);
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
static void F(
	lex_ctx_t & rlex_ctx,
	tstack<element_type> & rstack)
{
	lex_ctx_t save;
	switch (rlex_ctx.token) {
	case L_PLUS:
		save = rlex_ctx;
		match(rlex_ctx, rlex_ctx.token);
		U(rlex_ctx, rstack);
		emit(save, rstack);
		break;

	case L_MINUS:
		save = rlex_ctx;
		match(rlex_ctx, rlex_ctx.token);
		U(rlex_ctx, rstack);
		emit(save, rstack);
		break;

//	case L_EXP:
//	case L_LOG:
//	case L_ORD:
//		t = pc->lookahead1;
//		match(t, lookahead_token);
//		U(rlex_ctx, rstack);
//		emit(rlex_ctx, rstack);
//		break;
//
	default:
		U(rlex_ctx, rstack);
		return;
	}
}

// ----------------------------------------------------------------
static void T(
	lex_ctx_t & rlex_ctx,
	tstack<element_type> & rstack)
{
	lex_ctx_t save;
	F(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case L_MUL:
		case L_DIV:
		case L_MOD:
			save = rlex_ctx;
			match(rlex_ctx, rlex_ctx.token);
			F(rlex_ctx, rstack);
			emit(save, rstack);
			continue;
			break;
		default:
			return;
			break;
		}
	}
}

// ----------------------------------------------------------------
static void E(
	lex_ctx_t & rlex_ctx,
	tstack<element_type> & rstack)
{
	lex_ctx_t save;
	T(rlex_ctx, rstack);
	while (1) {
		switch (rlex_ctx.token) {
		case L_PLUS:
		case L_MINUS:
			save = rlex_ctx;
			match(rlex_ctx, rlex_ctx.token);
			T(rlex_ctx, rstack);
			emit(save, rstack);
			continue;
			break;
		default:
			return;
			break;
		}
	}
}

// ----------------------------------------------------------------
void parse(int argc, char ** argv)
{
	lex_ctx_t lex_ctx;
	tstack<element_type> stack;
	element_type result = -999;

	lexinit(lex_ctx, argc, argv);
	lexan(lex_ctx);

	while (lex_ctx.token != L_NULL) {
		E(lex_ctx, stack);
		if (!stack.pop(result)) {
			std::cerr << "Stack underflow.\n";
			exit(1);
		}
		std::cout << result << "\n";
		match(lex_ctx, L_NULL); // Check for extraneous text.
	}
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	parse(argc, argv);
	return 0;
}
