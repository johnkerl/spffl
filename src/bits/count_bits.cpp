// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "count_bits.h"

namespace spffl::bits {

static unsigned char byte_num_one_bits[] = {
    0 /*00*/,
    1 /*01*/,
    1 /*02*/,
    2 /*03*/,
    1 /*04*/,
    2 /*05*/,
    2 /*06*/,
    3 /*07*/,
    1 /*08*/,
    2 /*09*/,
    2 /*0a*/,
    3 /*0b*/,
    2 /*0c*/,
    3 /*0d*/,
    3 /*0e*/,
    4 /*0f*/,
    1 /*10*/,
    2 /*11*/,
    2 /*12*/,
    3 /*13*/,
    2 /*14*/,
    3 /*15*/,
    3 /*16*/,
    4 /*17*/,
    2 /*18*/,
    3 /*19*/,
    3 /*1a*/,
    4 /*1b*/,
    3 /*1c*/,
    4 /*1d*/,
    4 /*1e*/,
    5 /*1f*/,
    1 /*20*/,
    2 /*21*/,
    2 /*22*/,
    3 /*23*/,
    2 /*24*/,
    3 /*25*/,
    3 /*26*/,
    4 /*27*/,
    2 /*28*/,
    3 /*29*/,
    3 /*2a*/,
    4 /*2b*/,
    3 /*2c*/,
    4 /*2d*/,
    4 /*2e*/,
    5 /*2f*/,
    2 /*30*/,
    3 /*31*/,
    3 /*32*/,
    4 /*33*/,
    3 /*34*/,
    4 /*35*/,
    4 /*36*/,
    5 /*37*/,
    3 /*38*/,
    4 /*39*/,
    4 /*3a*/,
    5 /*3b*/,
    4 /*3c*/,
    5 /*3d*/,
    5 /*3e*/,
    6 /*3f*/,
    1 /*40*/,
    2 /*41*/,
    2 /*42*/,
    3 /*43*/,
    2 /*44*/,
    3 /*45*/,
    3 /*46*/,
    4 /*47*/,
    2 /*48*/,
    3 /*49*/,
    3 /*4a*/,
    4 /*4b*/,
    3 /*4c*/,
    4 /*4d*/,
    4 /*4e*/,
    5 /*4f*/,
    2 /*50*/,
    3 /*51*/,
    3 /*52*/,
    4 /*53*/,
    3 /*54*/,
    4 /*55*/,
    4 /*56*/,
    5 /*57*/,
    3 /*58*/,
    4 /*59*/,
    4 /*5a*/,
    5 /*5b*/,
    4 /*5c*/,
    5 /*5d*/,
    5 /*5e*/,
    6 /*5f*/,
    2 /*60*/,
    3 /*61*/,
    3 /*62*/,
    4 /*63*/,
    3 /*64*/,
    4 /*65*/,
    4 /*66*/,
    5 /*67*/,
    3 /*68*/,
    4 /*69*/,
    4 /*6a*/,
    5 /*6b*/,
    4 /*6c*/,
    5 /*6d*/,
    5 /*6e*/,
    6 /*6f*/,
    3 /*70*/,
    4 /*71*/,
    4 /*72*/,
    5 /*73*/,
    4 /*74*/,
    5 /*75*/,
    5 /*76*/,
    6 /*77*/,
    4 /*78*/,
    5 /*79*/,
    5 /*7a*/,
    6 /*7b*/,
    5 /*7c*/,
    6 /*7d*/,
    6 /*7e*/,
    7 /*7f*/,
    1 /*80*/,
    2 /*81*/,
    2 /*82*/,
    3 /*83*/,
    2 /*84*/,
    3 /*85*/,
    3 /*86*/,
    4 /*87*/,
    2 /*88*/,
    3 /*89*/,
    3 /*8a*/,
    4 /*8b*/,
    3 /*8c*/,
    4 /*8d*/,
    4 /*8e*/,
    5 /*8f*/,
    2 /*90*/,
    3 /*91*/,
    3 /*92*/,
    4 /*93*/,
    3 /*94*/,
    4 /*95*/,
    4 /*96*/,
    5 /*97*/,
    3 /*98*/,
    4 /*99*/,
    4 /*9a*/,
    5 /*9b*/,
    4 /*9c*/,
    5 /*9d*/,
    5 /*9e*/,
    6 /*9f*/,
    2 /*a0*/,
    3 /*a1*/,
    3 /*a2*/,
    4 /*a3*/,
    3 /*a4*/,
    4 /*a5*/,
    4 /*a6*/,
    5 /*a7*/,
    3 /*a8*/,
    4 /*a9*/,
    4 /*aa*/,
    5 /*ab*/,
    4 /*ac*/,
    5 /*ad*/,
    5 /*ae*/,
    6 /*af*/,
    3 /*b0*/,
    4 /*b1*/,
    4 /*b2*/,
    5 /*b3*/,
    4 /*b4*/,
    5 /*b5*/,
    5 /*b6*/,
    6 /*b7*/,
    4 /*b8*/,
    5 /*b9*/,
    5 /*ba*/,
    6 /*bb*/,
    5 /*bc*/,
    6 /*bd*/,
    6 /*be*/,
    7 /*bf*/,
    2 /*c0*/,
    3 /*c1*/,
    3 /*c2*/,
    4 /*c3*/,
    3 /*c4*/,
    4 /*c5*/,
    4 /*c6*/,
    5 /*c7*/,
    3 /*c8*/,
    4 /*c9*/,
    4 /*ca*/,
    5 /*cb*/,
    4 /*cc*/,
    5 /*cd*/,
    5 /*ce*/,
    6 /*cf*/,
    3 /*d0*/,
    4 /*d1*/,
    4 /*d2*/,
    5 /*d3*/,
    4 /*d4*/,
    5 /*d5*/,
    5 /*d6*/,
    6 /*d7*/,
    4 /*d8*/,
    5 /*d9*/,
    5 /*da*/,
    6 /*db*/,
    5 /*dc*/,
    6 /*dd*/,
    6 /*de*/,
    7 /*df*/,
    3 /*e0*/,
    4 /*e1*/,
    4 /*e2*/,
    5 /*e3*/,
    4 /*e4*/,
    5 /*e5*/,
    5 /*e6*/,
    6 /*e7*/,
    4 /*e8*/,
    5 /*e9*/,
    5 /*ea*/,
    6 /*eb*/,
    5 /*ec*/,
    6 /*ed*/,
    6 /*ee*/,
    7 /*ef*/,
    4 /*f0*/,
    5 /*f1*/,
    5 /*f2*/,
    6 /*f3*/,
    5 /*f4*/,
    6 /*f5*/,
    6 /*f6*/,
    7 /*f7*/,
    5 /*f8*/,
    6 /*f9*/,
    6 /*fa*/,
    7 /*fb*/,
    6 /*fc*/,
    7 /*fd*/,
    7 /*fe*/,
    8 /*ff*/,
};

// ----------------------------------------------------------------
int count_one_bits(unsigned char *p, int nbytes) {
  int rv = 0;
  int i;
  for (i = 0; i < nbytes; i++) {
    rv += byte_num_one_bits[p[i]];
  }
  return rv;
}

#ifdef MAKE_TABLE
// ----------------------------------------------------------------
// This function may be used to create a look-up table, which can then
// be used instead.
int slow_count_one_bits(unsigned char u) {
  int rv = 0;
  while (u) {
    if (u & 1) {
      rv++;
    }
    u >>= 1;
  }
  return rv;
}

// ----------------------------------------------------------------
int main(void) {
  unsigned i;
  unsigned char u;
  int nb;

  for (i = 0, u = 0; i < 256; i++, u++) {
    if ((i & 7) == 0) {
      printf("\t");
    } else {
      printf(" ");
    }

    nb = slow_count_one_bits(u);
    printf("%d /*%02x/,", nb, u);

    if ((i & 7) == 7) {
      printf("\n");
    }
  }

  return 0;
}
#endif // MAKE_TABLE

} // namespace spffl::bits
