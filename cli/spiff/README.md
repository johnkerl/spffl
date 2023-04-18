```
================================================================
Data type      Prefix  Description
---------      ------  -----------------------------------
int            z       Z                        Ring
bit_t          f2      Z/<2> = F_2              Residue field, p=2
intmod_t       fp      Z/<p> = F_p              Residue field
intrat_t       q       Q                        Quotient field
//
f2poly_t       f2p     F2[x]                    Ring
f2polymod_t    f2pm    F2[x]/<f(x)> = F_{2^n}   Residue field
f2polyrat_t    f2pr    F2(x)                    Quotient field
//
fppoly_t       fpp     F_p[x]                   Ring
fppolymod_t    fppm    F_p[x]/<f(x)>            Residue field
fppolyrat_t    fppr    F_p(x)                   Quotient field
//
f2npoly_t      f2np    F_{2^n}[y]               Ring
f2npolymod_t   f2npm   F_{2^n}[y]/<g(y)>        Residue field
f2npolyrat_t   f2npr   F_{2^n}(y)               Quotient field
//
fpnpoly_t      fpnp    F_{p^n}[y]               Ring
fpnpolymod_t   fpnpm   F_{p^n}[y]/<g(y)>        Residue field
fpnpolyrat_t   fpnpr   F_{p^n}(y)               Quotient field

----------------------------------------------------------------
Rings:

*          z    f2p  f2np fpp  fpnp
---------- ---- ---- ---- ---- ----
op         o    o    o    o    o
eval       -    o    o    o    -
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

----------------------------------------------------------------
Fields:

*        q    fp   f2   f2pm f2pr f2npm f2npr fppm fppr fpnpm fpnpr
-        ---- ---- ---- ---- ---- ----- ----- ---- ---- ----- -----
op       o    o    .    o    o    o     o     o    o    o     .
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

----------------------------------------------------------------
f2p_to_f2np fpp_to_fpnp
orbit frobit eval
matminpoly, matcharpoly
f*chart f*polylist
row-reduce over an ED, non-field.
```
