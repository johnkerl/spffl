# SPFFL

SPFFL (pronounced _spiffle_) is a small-prime finite-field library, where small means 32 bits or less. Polynomials may have arbitrary degree, as limited by machine resources. Residue field and quotient fields are supported. In addition to the C++ library, there is a command-line tool, named `spiff`, for convenient interactive use.

See also my expository paper [_Computation in Finite Fields_](doc/ffcomp.pdf) for background
and narrative on the data structures and algorithms implemented by SPFFL.

Please also see [RUFFL](https://github.com/johnkerl/ruffl), my Ruby port of SPFFL.

SPFFL is released under the terms of the 2-Clause BSD license.

## Summary of data types

* Integers, residue class rings (finite fields when the modulus is a prime number), quotient fields (small rationals).
* Polynomials with coefficients in `F_p`.
* Residue class rings for polynomials with coefficients in `F_p` (finite fields when the modulus is an irreducible polynomial), quotient fields (rational functions).
* Polynomials with coefficients in `F_q`.
Residue class rings for polynomials with coefficients in `F_q` (finite fields when the modulus is an irreducible polynomial), quotient fields (rational functions).
* Thus, double extensions are supported, with tools for embedding double extensions into single extensions.

## Data types in detail
```
C++ data type	spiff prefix	Notation	      Description
 
int             z               Z                     Ring
bit_t           f2              Z/<2>=F_2             Residue  field, p=2
intmod_t        fp              Z/<p>=F_p             Residue  field
intrat_t        q               Q                     Quotient field

f2_poly_t       f2p             F_2[x]                Ring
f2_poly_mod_t   f2pm            F_2[x]/<f(x)>=F_2^n   Residue  field
f2_poly_rat_t   f2pr            F_2(x)                Quotient field

fp_poly_t       fpp             F_p[x]                Ring
fp_poly_mod_t   fppm            F_p[x]/<f(x)>=F_p^n   Residue  field
fp_poly_rat_t   fppr            F_p(x)                Quotient field

f2n_poly_t      f2np            F_2^n[y]              Ring
f2n_poly_mod_t  f2npm           F_2^n[y]/<g(y)>       Residue field
f2n_poly_rat_t  f2npr           F_2^n(y)              Quotient field

fpn_poly_t      fpnp            F_p^n[y]              Ring
fpn_poly_mod_t  fpnpm           F_p^n[y]/<g(y)>       Residue field
fpn_poly_rat_t  fpnpr           F_p^n(y)              Quotient field
```

## Summary of features

* Arithmetic for integers and polynomial rings, residue class rings/fields, and quotient fields.
* Generation of random elements.
* GCD, LCM, totient.
* Irreducibility testing, factorization (Berlekamp).
* Periods of polynomials.
* Printing of tables.
* Discrete log (Shanks).
* Matrix arithmetic for all data types.
* Computation of row echelon form, determinant, matrix inverse.
* Diagonalizability testing for matrices over finite fields (under construction).
* Jordan normal form and rational canonical form for matrices over finite fields (to be implemented).
* Computation of eigenspaces and generalized eigenspaces for matrices over finite fields (under construction).

## Features in detail
Key:
* "o" means coded
* "." means not coded yet
* "-" means not applicable or not interesting.

Rings:
```
cmd/type   z    f2p  f2np fpp  fpnp
---------- ---- ---- ---- ---- ----
op         o    o    o    o    .
eval       -    o    o    o    .
rand       -    o    o    o    .
deg        -    o    o    o    .
gcd        o    o    o    o    .
lcm        o    o    o    o    .
totient    o    o    o    o    .
test       o    o    o    o    .
find       -    o    o    o    .
period     -    o    .    .    .
factor     o    o    o    o    .
divisors   o    o    o    o    .
list       -    o    o    o    .
compmx     -    o    o    o    .
```

Fields:
```
cmd/type q    fp   f2   f2pm f2pr f2npm f2npr fppm fppr fpnpm fpnpr
-------- ---- ---- ---- ---- ---- ----- ----- ---- ---- ----- -----
op       o    o    .    o    o    o     o     o    o    .     .
tbl      -    o    -    o    -    o     -     o    -    .     -
ord      -    o    -    o    -    o     -     r    -    .     -
findgen  -    o    -    o    -    o     -     .    -    .     -
log      -    o    -    o    -    o     -     .    -    .     -
rand     -    o    o    o    o    o     .     o    .    .     .
chpol    -    -    -    o    -    -     -     .    -    -     -
minpol   -    -    -    o    -    -     -     .    -    -     -
list     -    o    -    o    -    o     -     o    -    .     -
matop    o    o    o    o    o    o     o     o    o    .     .
matord   -    o    o    o    -    .     -     o    -    .     .
matrand  -    o    o    o    o    .     .     o    .    .     .
matchpol -    o    o    o    -    -     -     .    -    -     -
dable    .    .    .    .    .    .     .     .    .    .     .
eisys    .    .    .    .    .    .     .     .    .    .     .
jordan   .    .    .    .    .    .     .     .    .    .     .
ratcanon .    .    .    .    .    .     .     .    .    .     .
```

## Examples

```bash
$ f=`spiff f2_p_op 2 ^ 64 - 2`

$ echo $f
10000000000000002

$ spiff f2_p_factor $f
2 3 7 b d 43 49 57 5b 61 67 6d 73 75
```

```bash
$ spiff f2_pm_tbl 13 .
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 1 2 3 4 5 6 7 8 9 a b c d e f
0 2 4 6 8 a c e 3 1 7 5 b 9 f d
0 3 6 5 c f a 9 b 8 d e 7 4 1 2
0 4 8 c 3 7 b f 6 2 e a 5 1 d 9
0 5 a f 7 2 d 8 e b 4 1 9 c 3 6
0 6 c a b d 7 1 5 3 9 f e 8 2 4
0 7 e 9 f 8 1 6 d a 3 4 2 5 c b
0 8 3 b 6 e 5 d c 4 f 7 a 2 9 1
0 9 1 8 2 b 3 a 4 d 5 c 6 f 7 e
0 a 7 d e 4 9 3 f 5 8 2 1 b 6 c
0 b 5 e a 1 f 4 7 c 2 9 d 6 8 3
0 c b 7 5 9 e 2 a 6 1 d f 3 4 8
0 d 9 4 1 c 8 5 2 f b 6 3 e a 7
0 e f 1 d 3 2 c 9 7 6 8 4 a b 5
0 f d 2 9 6 4 b 1 e c 3 8 7 5 a
```

```bash
m=13
for r in `spiff f2_pm_list -a $m`; do
	spiff f2_pm_ch_pol $m $r
done

1:0:0:0:0
1:0:0:0:1
1:0:0:1:1
1:0:0:1:1
1:0:0:1:1
1:0:0:1:1
1:0:1:0:1
1:0:1:0:1
1:1:1:1:1
1:1:0:0:1
1:1:1:1:1
1:1:0:0:1
1:1:1:1:1
1:1:0:0:1
1:1:0:0:1
1:1:1:1:1
```

```bash
spiff f2_p_period { f2_p_list 4 }
10: 0
11: 4
12: 0
13: 15
14: 0
15: 6
16: 0
17: 7
18: 0
19: 15
1a: 0
1b: 6
1c: 0
1d: 7
1e: 0
1f: 5
```

```bash
spiff fp_ord  35 { fp_list -u 35 }
1: 1
2: 12
3: 12
4: 6
6: 2
8: 4
9: 6
11: 3
12: 12
13: 4
16: 3
17: 12
18: 12
19: 6
22: 4
23: 12
24: 6
26: 6
27: 4
29: 2
31: 6
32: 12
33: 12
34: 2
```

```bash
p=7
elements="`spiff fp_list -a $p`"
for a in $elements; do
        for b in $elements; do
                c=`spiff fp_op $p $a . $b`
                echo -n " $c"
        done
        echo ""
done

0  0  0  0  0  0  0
0  1  2  3  4  5  6
0  2  4  6  1  3  5
0  3  6  2  5  1  4
0  4  1  5  2  6  3
0  5  3  1  6  4  2
0  6  5  4  3  2  1
```

# Setup

## Disclaimer

This project, from 2004-2005, was for self-education, as well as software support for my master's
thesis (https://johnkerl.org/doc/kerl-ma-thesis-gc.pdf).  My efforts at portability were minimal.
Nonetheless Linux/x86 (which was my environment) has become a broad standard.

As of 2023 I'm using this repo as a little experiment, to port the build system
from [yamm](https://github.com/johnkerl/scripts/blob/main/fundam/yamm) to [cmake](https://cmake.org).

## Build/install steps

Still a WIP. Generate/build/test/install steps:

```
alias cmz='cmake --build build --target clean && rm -rf build'

alias  cmg='cmake -B build'
alias cmgd='cmake -B build -DCMAKE_BUILD_TYPE=Debug'

alias  cmb='cmake --build build'
alias  cmt='cmake --build build --target test'
alias  cmi='cmake --build build --target install' # <-- WIP as of 2023-03-13

export PATH=$(pwd)/build/cli/spiff:$PATH
cd regression
sh regress.sh
```

To get more details about failed unit tests including line numbers:

* Run `cmg` and `cmb`
* In place of `cmt`, `./build/test/bits/test_bits` (or whichever test executable)

TODO: more here about tests, libraries, and executables.

## Compiler selection

```
cmz
cmg -D CMAKE_C_COMPILER=gcc -D CMAKE_CXX_COMPILER=g++
cmb -v
```

TODO:
```
-DCMAKE_INSTALL_PREFIX=$prefix
```

## Installation (WIP)

```
$ cmz
$ cmg
$ cmb
$ cmt
$ cmi
```

This creates:

* `/usr/local/include/spffl/`
* `/usr/local/lib/libspffl.dylib` (or `.so`)
* `/usr/local/bin/spff`

Then you can run `spiff`. You can also built using the library like this:

```
$ g++ -std=c++20 -I /usr/local/include -L /usr/local/lib -lspffl examples/example1.cpp -o example1
$ install_name_tool -add_rpath $(pwd)/dist/lib example1
```

If you use an install location other than `/usr/local`:

* Replace `cmg` above with `cmg -DCMAKE_INSTALL_PREFIX=./dist`
* On MacOS, use `install_name_tool` tell the executable where to find the library

```
$ g++ -std=c++20 -I dist/spffl/include -L dist/lib -lspffl examples/example1.cpp -o example1
$ install_name_tool -add_rpath $(pwd)/dist/lib example1
```

```
$ ./example1 abc def
736a54
```

# Why SPFFL?
There are numerous other software packages for doing arithmetic over finite fields, e.g. Pari/GP, Shoup's NTL, Mathematica, etc. Pluses and minuses of SPFFL are as follows:

* My single most important reason for writing SPFFL was to learn by doing. I encourage you to do the same. Nonetheless, SPFFL is available on an as-is basis for anyone who would like to learn from it.
* SPFFL has I/O in a very compact format (examples are below).
* Special cases are made for _p_=2. This increases computation speed, and also permits an even more compact, hexadecimal I/O format.
* SPFFL aims for reasonable performance, but clarity of implementation is just as important. You will not find cutting-edge algorithms implemented here. SPFFL grew out of my desire for a simple desk calculator (cf. the Unix `bc` command) which would support finite-field arithmetic. Its main purpose remains that of automating simple computations.
* Unlike Shoup's NTL, there is no global modulus: each intmod or polymod has its own modulus, leading to a more elegant user experience.
* I limit _p_ to 32 bits. This reduces required storage space, and also removes the need for third-party (or my own) arbitrary-precision integer arithmetic, along with the concomitant hard problem of factoring large integers. Any prime of 32 bits or less will have a prime factor of 16 bits or less. There are 6542 primes of 16 bits or less, which may be stored in a table. Thus, 32-bit integer factorization is trivial. The down side of this is that SPFFL is unsuitable for finite fields F_p for large p, e.g. in cryptographic applications.
* SPFFL does use dynamic memory allocation, which permits arbitrary-degree polynomials (as limited by machine resources). However, it cleans up after itself as it runs, via properly coded constructors and destructors, so it has no need for garbage collection, user tweaking via `allocatemem()` calls, etc.
* Unlike computer-algebra tools such as Mathematica, Maple, or GAP, SPFFL is not monolithic, and does not have startup time measured in multiple seconds. Thus, it permits shell scripting in which executables are repeatedly invoked.
* Since the source code is my own, I can make it run on any platform I port it to, and I do not need to pay license fees.
* SPFFL's data types are not recursive. If you want to make a matrix of matrices, or use triple field extensions, you must create new C++ classes.
* SPFFL has no scripting language of its own. While SPFFL is a subroutine library, there is also a `spiff` executable which provides a command-line interface to most routines. `spiff` includes a simple expression parser, while variables, looping, and file I/O are provided by the shell. This offloads the script processing onto the shell, which already exists, freeing me from needing to re-invent the wheel, and allowing me to focus on SPFFL's core mathematical competency.
