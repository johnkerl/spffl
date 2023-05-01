// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef CMDLINEOPS_H
#define CMDLINEOPS_H

// Grammar:
//
//   S := E {terminator}
//   Q := C | C == C | C != C
//   C := E | E < E | E <= E | E > E | E >= E
//   E := T | T + T | T - T
//   T := F | F * F | F / F | F % F
//   F := + U | - U | U
//   U := P ^ P | P
//   P := ( E ) | NUM

#include "spffl/base/spffl_exception.h"
#include "spffl/containers/tstack.h"
#include <iostream>
#include <sstream>
#include <string.h>

namespace spffl::cli_parser {

template <class element_type> struct atom_t {
  element_type type_val;
  int int_val;
  bool is_int;
};

template <class element_type> struct lex_ctx_t {
  int argi;
  int argc;
  char **argv;
  atom_t<element_type> atom;
  int token;
  int in_pow_rhs;
  element_type zero;
  element_type one;
};

#define L_NUM 100
#define L_EOL 101
#define L_UNDEF 102

#define L_PLUS 110
#define L_MINUS 111
#define L_MUL 112
#define L_DIV 113
#define L_MOD 114
#define L_EXP 115
#define L_UPLUS 120
#define L_UMINUS 121

#define L_ORD 130

#define L_EQ 140
#define L_NE 141
#define L_LT 142
#define L_LE 143
#define L_GT 144
#define L_GE 145

#define L_LPAREN 200
#define L_RPAREN 201

#define T_T_OP 3  // type = op type, i.e. left-unary operators
#define T_TT_OP 4 // type = type op type, e.g. almost all.
#define T_TI_OP 5 // type = type op int,  e.g. exponentiation
#define I_TT_OP 6 // int  = type op type, e.g. equality and ordering.

template <class element_type>
static void E(
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack);

// ----------------------------------------------------------------
template <class element_type> static const char *token_desc(int t) {
  switch (t) {
  case L_NUM:
    return "num";
    break;
  case L_EOL:
    return "EOL";
    break;
  case L_UNDEF:
    return "undef";
    break;

  case L_PLUS:
    return "+";
    break;
  case L_MINUS:
    return "-";
    break;
  case L_MUL:
    return "*";
    break;
  case L_DIV:
    return "/";
    break;
  case L_MOD:
    return "%";
    break;
  case L_EXP:
    return "^";
    break;
  case L_UPLUS:
    return "u+";
    break;
  case L_UMINUS:
    return "u-";
    break;

  case L_EQ:
    return "==";
    break;
  case L_NE:
    return "!=";
    break;
  case L_LT:
    return "<";
    break;
  case L_LE:
    return "<=";
    break;
  case L_GT:
    return ">";
    break;
  case L_GE:
    return ">=";
    break;

  case L_ORD:
    return "ord";
    break;

  case L_LPAREN:
    return "(";
    break;
  case L_RPAREN:
    return ")";
    break;
  default:
    return "{???}";
    break;
  }
}

// ----------------------------------------------------------------
template <class element_type>
static void lexinit(lex_ctx_t<element_type> &rlex_ctx, int argc, char **argv,
    element_type zero, element_type one) {
  rlex_ctx.argi       = 0;
  rlex_ctx.argc       = argc;
  rlex_ctx.argv       = argv;
  rlex_ctx.token      = L_UNDEF;
  rlex_ctx.in_pow_rhs = 0;
  rlex_ctx.zero       = zero;
  rlex_ctx.one        = one;

#if 0
	std::cout << "zero = " << zero << "\n";
	std::cout << "one  = " << one  << "\n";
#endif
}

// ----------------------------------------------------------------
template <class element_type>
static void lexan(lex_ctx_t<element_type> &rlex_ctx) {
  if (rlex_ctx.argi >= rlex_ctx.argc) {
    rlex_ctx.token = L_EOL;
    return;
  }
  char *s = rlex_ctx.argv[rlex_ctx.argi];

  if (strcmp(s, "+") == 0) {
    rlex_ctx.token = L_PLUS;
  } else if (strcmp(s, "-") == 0) {
    rlex_ctx.token = L_MINUS;
  } else if (strcmp(s, "*") == 0) {
    rlex_ctx.token = L_MUL;
  } else if (strcmp(s, ".") == 0) {
    rlex_ctx.token = L_MUL;
  } else if (strcmp(s, "/") == 0) {
    rlex_ctx.token = L_DIV;
  } else if (strcmp(s, "%") == 0) {
    rlex_ctx.token = L_MOD;
  } else if (strcmp(s, "^") == 0) {
    rlex_ctx.token = L_EXP;
  }

  else if (strcmp(s, "==") == 0) {
    rlex_ctx.token = L_EQ;
  } else if (strcmp(s, "!=") == 0) {
    rlex_ctx.token = L_NE;
  } else if (strcmp(s, "/=") == 0) {
    rlex_ctx.token = L_NE;
  } else if (strcmp(s, "<") == 0) {
    rlex_ctx.token = L_LT;
  } else if (strcmp(s, "<=") == 0) {
    rlex_ctx.token = L_LE;
  } else if (strcmp(s, ">") == 0) {
    rlex_ctx.token = L_GT;
  } else if (strcmp(s, ">=") == 0) {
    rlex_ctx.token = L_GE;
  }

  else if (strcmp(s, "(") == 0) {
    rlex_ctx.token = L_LPAREN;
  } else if (strcmp(s, ")") == 0) {
    rlex_ctx.token = L_RPAREN;
  }

  else if (strcmp(s, "[") == 0) {
    rlex_ctx.token = L_LPAREN;
  } else if (strcmp(s, "]") == 0) {
    rlex_ctx.token = L_RPAREN;
  }

  else {
    rlex_ctx.token = L_NUM;
    std::istringstream iss(s, std::ios_base::in);
    if (rlex_ctx.in_pow_rhs) {
      rlex_ctx.atom.is_int = true;
      iss >> rlex_ctx.atom.int_val;
    } else {
      rlex_ctx.atom.type_val = rlex_ctx.zero; // Set modulus
      rlex_ctx.atom.is_int   = false;
      iss >> rlex_ctx.atom.type_val;
    }
    if (iss.fail()) {
      std::stringstream ss;
      ss << "Scan failure at \"" << s << "\".\n";
      throw spffl::exception_t(ss.str());
    }
  }
  rlex_ctx.argi++;
}

// ----------------------------------------------------------------
template <class element_type>
element_type clo_exp(
    element_type x, int e, element_type zero, element_type one) {
  element_type xp = x;

  if (x == zero) {
    if (e < 0) {
      std::stringstream ss;
      ss << "Division by zero.\n";
      throw spffl::exception_t(ss.str());
    }
    if (e == 0) {
      std::stringstream ss;
      ss << "0 ^ 0 undefined.\n";
      throw spffl::exception_t(ss.str());
    }
    return zero;
  }
  element_type rv = one;

  if (e == 0) {
    return rv;
  }

  if (e < 0) {
    if (e == -e) {
      std::stringstream ss;
      ss << "Can't handle MIN_INT.\n";
      throw spffl::exception_t(ss.str());
    }
    xp = one / x;
    e  = -e;
  }

  while (e != 0) {
    if (e & 1) {
      rv *= xp;
    }
    e = (unsigned)e >> 1;
    xp *= xp;
  }

  return rv;
}

// ----------------------------------------------------------------
template <class element_type>
static void emit(
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack) {
  atom_t<element_type> a, b, c;
  int tiform;

  if (rlex_ctx.token == L_NUM) {
    rstack.push(rlex_ctx.atom);
    return;
  }

  if (rlex_ctx.token == L_UPLUS) {
    // pop & push back -- amounts to leaving as-is.
    return;
  }

  switch (rlex_ctx.token) {
  case L_UMINUS:
    tiform = T_T_OP;
    break;

  case L_PLUS:
  case L_MINUS:
  case L_MUL:
  case L_DIV:
  case L_MOD:
    tiform = T_TT_OP;
    break;

  case L_EXP:
    tiform = T_TI_OP;
    break;

  case L_EQ:
  case L_NE:
  case L_LT:
  case L_LE:
  case L_GT:
  case L_GE:
    tiform = I_TT_OP;
    break;

  default:
    std::stringstream ss;
    ss << "Unhandled operator " << token_desc<element_type>(rlex_ctx.token)
       << ".\n";
    throw spffl::exception_t(ss.str());
    break;
  }

  if (tiform == T_T_OP) {
    rstack.pop(a);
  } else {
    rstack.pop(b);
    rstack.pop(a);
  }

  switch (tiform) {
  case T_T_OP:
    if (a.is_int) {
      std::stringstream ss;
      ss << "Operator " << token_desc<element_type>(rlex_ctx.token)
         << " requires type-specific argument.\n";
      throw spffl::exception_t(ss.str());
    }
    break;
  case T_TT_OP:
  case I_TT_OP:
    if (a.is_int || b.is_int) {
      std::stringstream ss;
      ss << "Operator " << token_desc<element_type>(rlex_ctx.token)
         << " requires two type-specific arguments.\n";
      throw spffl::exception_t(ss.str());
    }
    break;
  case T_TI_OP:
    if (a.is_int || !b.is_int) {
      std::stringstream ss;
      ss << "Operator " << token_desc<element_type>(rlex_ctx.token)
         << " requires one type-specific argument "
         << " and one integer argument.\n";
      throw spffl::exception_t(ss.str());
    }
    break;
  }

  switch (rlex_ctx.token) {
  case L_UMINUS:
    c.type_val = -a.type_val;
    break;
  case L_PLUS:
    c.type_val = a.type_val + b.type_val;
    break;
  case L_MINUS:
    c.type_val = a.type_val - b.type_val;
    break;
  case L_MUL:
    c.type_val = a.type_val * b.type_val;
    break;
  case L_DIV:
    c.type_val = a.type_val / b.type_val;
    break;
  case L_MOD:
    c.type_val = a.type_val % b.type_val;
    break;

  case L_EXP:
    c.type_val = clo_exp(a.type_val, b.int_val, rlex_ctx.zero, rlex_ctx.one);
    break;

  case L_EQ:
    c.int_val = a.type_val == b.type_val;
    break;
  case L_NE:
    c.int_val = a.type_val != b.type_val;
    break;
  case L_LT:
    c.int_val = a.type_val < b.type_val;
    break;
  case L_LE:
    c.int_val = a.type_val <= b.type_val;
    break;
  case L_GT:
    c.int_val = a.type_val > b.type_val;
    break;
  case L_GE:
    c.int_val = a.type_val >= b.type_val;
    break;

  default:
    std::stringstream ss;
    ss << "Unhandled operator " << token_desc<element_type>(rlex_ctx.token)
       << ".\n";
    throw spffl::exception_t(ss.str());
    break;
  }

  switch (tiform) {
  case T_T_OP:
  case T_TT_OP:
  case T_TI_OP:
    c.is_int = false;
    break;
  case I_TT_OP:
    c.is_int = true;
    break;
  }
  rstack.push(c);
}

// ----------------------------------------------------------------
template <class element_type>
static void match(lex_ctx_t<element_type> &rlex_ctx, int expected_token) {
  if (rlex_ctx.token == expected_token) {
    lexan<element_type>(rlex_ctx);
  } else {
    std::stringstream ss;
    ss << "Syntax error.\n";
    ss << "Expected " << token_desc<element_type>(expected_token) << "; got "
       << token_desc<element_type>(rlex_ctx.token) << ".\n";
    throw spffl::exception_t(ss.str());
  }
}

// ----------------------------------------------------------------
template <class element_type>
static void P(
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack) {
  switch (rlex_ctx.token) {
  case L_LPAREN:
    match<element_type>(rlex_ctx, L_LPAREN);
    E<element_type>(rlex_ctx, rstack);
    match<element_type>(rlex_ctx, L_RPAREN);
    break;
  case L_NUM:
    emit<element_type>(rlex_ctx, rstack);
    match<element_type>(rlex_ctx, L_NUM);
    break;
  default:
    std::stringstream ss;
    ss << "syntax error at token " << token_desc<element_type>(rlex_ctx.token)
       << "\n";
    throw spffl::exception_t(ss.str());
  }
}

// ----------------------------------------------------------------
template <class element_type>
static void U(
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack) {
  lex_ctx_t<element_type> save;
  P<element_type>(rlex_ctx, rstack);
  while (1) {
    switch (rlex_ctx.token) {
      //		case L_GCD: // xxx temp; need to find appropriate
      // precedence. 		case L_CHOOSE: // xxx temp; need to find
      // appropriate precedence.
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
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack) {
  lex_ctx_t<element_type> save;
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

    //	case L_EXP:
    //	case L_LOG:
    //	case L_ORD:
    //		t = pc->lookahead1;
    //		match<element_type>(t, lookahead_token);
    //		U<element_type>(rlex_ctx, rstack);
    //		emit<element_type>(rlex_ctx, rstack);
    //		break;
    //
  default:
    U<element_type>(rlex_ctx, rstack);
    return;
  }
}

// ----------------------------------------------------------------
template <class element_type>
static void T(
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack) {
  lex_ctx_t<element_type> save;
  F<element_type>(rlex_ctx, rstack);
  while (1) {
    switch (rlex_ctx.token) {
    case L_MUL:
    case L_DIV:
    case L_MOD:
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
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack) {
  lex_ctx_t<element_type> save;
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
static void C(
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack) {
  lex_ctx_t<element_type> save;
  E<element_type>(rlex_ctx, rstack);
  while (1) {
    switch (rlex_ctx.token) {
    case L_LT:
    case L_LE:
    case L_GT:
    case L_GE:
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
template <class element_type>
static void Q(
    lex_ctx_t<element_type> &rlex_ctx, tstack<atom_t<element_type>> &rstack) {
  lex_ctx_t<element_type> save;
  C<element_type>(rlex_ctx, rstack);
  while (1) {
    switch (rlex_ctx.token) {
    case L_EQ:
    case L_NE:
      save = rlex_ctx;
      match<element_type>(rlex_ctx, rlex_ctx.token);
      C<element_type>(rlex_ctx, rstack);
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
void cmd_line_parse(
    int argc, char **argv, element_type zero, element_type one) {
  lex_ctx_t<element_type> lex_ctx;
  tstack<atom_t<element_type>> stack;
  atom_t<element_type> result;

  lexinit<element_type>(lex_ctx, argc, argv, zero, one);
  lexan<element_type>(lex_ctx);

  while (lex_ctx.token != L_EOL) {
    Q<element_type>(lex_ctx, stack);
    if (!stack.pop(result)) {
      std::stringstream ss;
      ss << "Stack underflow.\n";
      throw spffl::exception_t(ss.str());
    }
    if (result.is_int) {
      std::cout << result.int_val << "\n";
    } else {
      std::cout << result.type_val << "\n";
    }
    // Check for extraneous text.
    match<element_type>(lex_ctx, L_EOL);
  }
}

} // namespace spffl::cli_parser

#endif // CMDLINEOPS_H
