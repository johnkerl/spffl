// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef CMDLINEVECOPS_H
#define CMDLINEVECOPS_H

// Grammar:
//
//   S := E {terminator}
//   Q := E | E == E | E != E
//   E := T | T + T | T - T
//   T := F | F * F | F / F | F % F
//   F := + U | - U | U
//   U := P ^ P | P
//   P := ( E ) | NUM

#include "tstack.h"
#include "tvector.h"
#include <iostream>
#include <sstream>
#include <string.h>
#include <string>

namespace spffl::cliparser {

template <class element_type> struct vecatom_t {
  tvector<element_type> vec_val;
  element_type scalar_val;
  int int_val;
  int atom_type;
};

template <class element_type> struct vec_lex_ctx_t {
  int argi;
  int argc;
  char **argv;
  vecatom_t<element_type> atom;
  int token;
  int in_pow_rhs;
  element_type zero;
  element_type one;
};

#define L_VEC 100
#define L_EOL 101
#define L_UNDEF 102

#define L_PLUS 110
#define L_MINUS 111
#define L_MUL 112
#define L_EXP 115
#define L_UPLUS 120
#define L_UMINUS 121

#define L_EQ 140
#define L_NE 141
#define L_RANK 142

#define L_LPAREN 200
#define L_RPAREN 201

#define S_V_OP 3  // scalar = op vec, i.e. -- none here?
#define V_V_OP 4  // vec = op vec, i.e. left-unary operators
#define V_VV_OP 5 // vec = vec op vec, e.g. almost all.
#define V_VI_OP 6 // vec = vec op int,  e.g. exponentiation
#define I_VV_OP 7 // int = vec op vec, e.g. equality and ordering.
#define I_V_OP 8  // int = vec, e.g. -- none here?

#define VEC_ATOM 17
#define SCALAR_ATOM 18
#define INT_ATOM 19

template <class element_type>
static void E(vec_lex_ctx_t<element_type> &rlex_ctx,
              tstack<vecatom_t<element_type>> &rstack);

// ----------------------------------------------------------------
template <class element_type> static const char *vec_token_desc(int t) {
  switch (t) {
  case L_VEC:
    return "vector";
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
static void veclexinit(vec_lex_ctx_t<element_type> &rlex_ctx, int argc,
                       char **argv, element_type zero, element_type one) {
  rlex_ctx.argi = 0;
  rlex_ctx.argc = argc;
  rlex_ctx.argv = argv;
  rlex_ctx.token = L_UNDEF;
  rlex_ctx.in_pow_rhs = 0;
  rlex_ctx.zero = zero;
  rlex_ctx.one = one;
}

// ----------------------------------------------------------------
template <class element_type>
static void veclexan(vec_lex_ctx_t<element_type> &rlex_ctx) {
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
  } else if (strcmp(s, "^") == 0) {
    rlex_ctx.token = L_EXP;
  }

  else if (strcmp(s, "==") == 0) {
    rlex_ctx.token = L_EQ;
  } else if (strcmp(s, "!=") == 0) {
    rlex_ctx.token = L_NE;
  } else if (strcmp(s, "/=") == 0) {
    rlex_ctx.token = L_NE;
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
    rlex_ctx.token = L_VEC;
    std::istringstream iss(s, std::ios_base::in);
    if (rlex_ctx.in_pow_rhs) {
      rlex_ctx.atom.atom_type = INT_ATOM;
      iss >> rlex_ctx.atom.int_val;
    } else {
      rlex_ctx.atom.vec_val = rlex_ctx.zero; // Set modulus
      rlex_ctx.atom.atom_type = VEC_ATOM;

      if (strchr(rlex_ctx.argv[rlex_ctx.argi], '[')) {
        if (!rlex_ctx.atom.vec_val.bracket_in(rlex_ctx.argv[rlex_ctx.argi])) {
          std::cerr << "Couldn't scan \"" << rlex_ctx.argv[rlex_ctx.argi]
                    << "\"\n";
          exit(1);
        }
      } else {
#if 0
				if (!rlex_ctx.atom.vec_val.load_from_file(
					rlex_ctx.argv[rlex_ctx.argi]))
				{
					std::cerr << "Couldn't read \""
						<< rlex_ctx.argv[rlex_ctx.argi]
						<< "\"\n";
					exit(1);
				}
#else
        std::cerr << "cmd_line_vector_ops: file I/O not yet implemented.\n";
        exit(1);
#endif
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
static void emit(vec_lex_ctx_t<element_type> &rlex_ctx,
                 tstack<vecatom_t<element_type>> &rstack) {
  vecatom_t<element_type> A, B, C;
  int msiform;

  if (rlex_ctx.token == L_VEC) {
    rstack.push(rlex_ctx.atom);
    return;
  }

  if (rlex_ctx.token == L_UPLUS) {
    // pop & push back -- amounts to leaving as-is.
    return;
  }

  switch (rlex_ctx.token) {
  case L_UMINUS:
    msiform = V_V_OP;
    break;

  case L_DET: // TODO: defined in cmdlintmatops.h -- needs some common define
              // location ...
    msiform = S_V_OP;
    break;

  case L_PLUS:
  case L_MINUS:
  case L_MUL:
    msiform = V_VV_OP;
    break;

  case L_EXP:
    msiform = V_VI_OP;
    break;

  case L_EQ:
  case L_NE:
    msiform = I_VV_OP;
    break;

  case L_RANK:
    msiform = I_V_OP;
    break;

  default:
    std::cerr << "Unhandled operator "
              << vec_token_desc<element_type>(rlex_ctx.token) << ".\n";
    exit(1);
    break;
  }

  if ((msiform == V_V_OP) || (msiform == S_V_OP) || (msiform == I_V_OP)) {
    rstack.pop(A);
  } else {
    rstack.pop(B);
    rstack.pop(A);
  }

  switch (msiform) {
  case V_V_OP:
  case S_V_OP:
    if (A.atom_type != VEC_ATOM) {
      std::cerr << "Operator " << vec_token_desc<element_type>(rlex_ctx.token)
                << " requires vector argument.\n";
      exit(1);
    }
    break;
  case V_VV_OP:
  case I_VV_OP:
    if ((A.atom_type != VEC_ATOM) || (B.atom_type != VEC_ATOM)) {
      std::cerr << "Operator " << vec_token_desc<element_type>(rlex_ctx.token)
                << " requires two vector arguments.\n";
      exit(1);
    }
    break;
  case I_V_OP:
    if (A.atom_type != VEC_ATOM) {
      std::cerr << "Operator " << vec_token_desc<element_type>(rlex_ctx.token)
                << " requires one vector argument.\n";
      exit(1);
    }
    break;
  case V_VI_OP:
    if ((A.atom_type != VEC_ATOM) || (B.atom_type != INT_ATOM)) {
      std::cerr << "Operator " << vec_token_desc<element_type>(rlex_ctx.token)
                << " requires one vector argument "
                << " and one integer argument.\n";
      exit(1);
    }
    break;
  }

  switch (rlex_ctx.token) {
  case L_UMINUS:
    C.vec_val = -A.vec_val;
    break;
  case L_PLUS:
    C.vec_val = A.vec_val + B.vec_val;
    break;
  case L_MINUS:
    C.vec_val = A.vec_val - B.vec_val;
    break;
  case L_MUL:
    C.vec_val = A.vec_val * B.vec_val;
    break;

  case L_EQ:
    C.int_val = A.vec_val == B.vec_val;
    break;
  case L_NE:
    C.int_val = A.vec_val != B.vec_val;
    break;

  case L_EXP:
    C.vec_val = A.vec_val.exp(B.int_val);
    break;

  default:
    std::cerr << "Unhandled operator "
              << vec_token_desc<element_type>(rlex_ctx.token) << ".\n";
    exit(1);
    break;
  }

  switch (msiform) {
  case V_V_OP:
  case V_VV_OP:
  case V_VI_OP:
    C.atom_type = VEC_ATOM;
    break;
  case S_V_OP:
    C.atom_type = SCALAR_ATOM;
    break;
  case I_VV_OP:
    C.atom_type = INT_ATOM;
    break;
  case I_V_OP:
    C.atom_type = INT_ATOM;
    break;
  }

  rstack.push(C);
}

// ----------------------------------------------------------------
template <class element_type>
static void match(vec_lex_ctx_t<element_type> &rlex_ctx, int expected_token) {
  if (rlex_ctx.token == expected_token) {
    veclexan<element_type>(rlex_ctx);
  } else {
    std::cerr << "Syntax error.\n";
    std::cerr << "Expected " << vec_token_desc<element_type>(expected_token)
              << "; got " << vec_token_desc<element_type>(rlex_ctx.token)
              << ".\n";
    exit(1);
  }
}

// ----------------------------------------------------------------
template <class element_type>
static void P(vec_lex_ctx_t<element_type> &rlex_ctx,
              tstack<vecatom_t<element_type>> &rstack) {
  switch (rlex_ctx.token) {
  case L_LPAREN:
    match<element_type>(rlex_ctx, L_LPAREN);
    E<element_type>(rlex_ctx, rstack);
    match<element_type>(rlex_ctx, L_RPAREN);
    break;
  case L_VEC:
    emit<element_type>(rlex_ctx, rstack);
    match<element_type>(rlex_ctx, L_VEC);
    break;
  default:
    std::cerr << "syntax error at token "
              << vec_token_desc<element_type>(rlex_ctx.token) << "\n";
    exit(1);
  }
}

// ----------------------------------------------------------------
template <class element_type>
static void U(vec_lex_ctx_t<element_type> &rlex_ctx,
              tstack<vecatom_t<element_type>> &rstack) {
  vec_lex_ctx_t<element_type> save;
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
static void F(vec_lex_ctx_t<element_type> &rlex_ctx,
              tstack<vecatom_t<element_type>> &rstack) {
  vec_lex_ctx_t<element_type> save;
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

  default:
    U<element_type>(rlex_ctx, rstack);
    return;
  }
}

// ----------------------------------------------------------------
template <class element_type>
static void T(vec_lex_ctx_t<element_type> &rlex_ctx,
              tstack<vecatom_t<element_type>> &rstack) {
  vec_lex_ctx_t<element_type> save;
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
static void E(vec_lex_ctx_t<element_type> &rlex_ctx,
              tstack<vecatom_t<element_type>> &rstack) {
  vec_lex_ctx_t<element_type> save;
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
static void Q(vec_lex_ctx_t<element_type> &rlex_ctx,
              tstack<vecatom_t<element_type>> &rstack) {
  vec_lex_ctx_t<element_type> save;
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
void cmd_line_vec_parse(int argc, char **argv, element_type zero,
                        element_type one) {
  vec_lex_ctx_t<element_type> lex_ctx;
  tstack<vecatom_t<element_type>> stack;
  vecatom_t<element_type> result;

  veclexinit<element_type>(lex_ctx, argc, argv, zero, one);
  veclexan<element_type>(lex_ctx);

  while (lex_ctx.token != L_EOL) {
    Q<element_type>(lex_ctx, stack);
    if (!stack.pop(result)) {
      std::cerr << "Stack underflow.\n";
      exit(1);
    }

    switch (result.atom_type) {
    case VEC_ATOM:
      std::cout << result.vec_val << "\n";
      break;
    case SCALAR_ATOM:
      std::cout << result.scalar_val << "\n";
      break;
    case INT_ATOM:
      std::cout << result.int_val << "\n";
      break;
    default:
      std::cerr << "Coding error file " << __FILE__ << " line " << __LINE__
                << "\n";
      exit(1);
      break;
    }

    // Check for extraneous text.
    match<element_type>(lex_ctx, L_EOL);
  }
}

} // namespace spffl::cliparser

#endif // CMDLINEVECOPS_H
