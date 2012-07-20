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

#include "log2.h"
#include "msb_table.h"

static int u4_table[] = {
	0, /* 0x0 */ 0, /* 0x1 */ 1, /* 0x2 */ 1, /* 0x3 */
	2, /* 0x4 */ 2, /* 0x5 */ 2, /* 0x6 */ 2, /* 0x7 */
	3, /* 0x8 */ 3, /* 0x9 */ 3, /* 0xa */ 3, /* 0xb */
	3, /* 0xc */ 3, /* 0xd */ 3, /* 0xe */ 3, /* 0xf */
};

static int l4_table[] = {
	0, /* 0x0 */ 0, /* 0x1 */ 1, /* 0x2 */ 0, /* 0x3 */
	2, /* 0x4 */ 0, /* 0x5 */ 1, /* 0x6 */ 0, /* 0x7 */
	3, /* 0x8 */ 0, /* 0x9 */ 1, /* 0xa */ 0, /* 0xb */
	2, /* 0xc */ 0, /* 0xd */ 1, /* 0xe */ 0, /* 0xf */
};

// ----------------------------------------------------------------
unsigned find_msb_16(
	unsigned short n)
{
	unsigned rv = 0;
	unsigned short upper;
	unsigned un = (unsigned) n;

	if (un < MSB_TABLE_SIZE)
		return msb_table[n];

	upper = n >> 8;
	if (upper) {
		rv += 8;
		n = upper;
	}
	else
		n &= 0xff;

	upper = n >> 4;
	if (upper) {
		rv += 4;
		n = upper;
	}
	else
		n &= 0x0f;

	rv += u4_table[n];
	return rv;
}

// ----------------------------------------------------------------
unsigned find_msb_32(
	unsigned n)
{

	// // aggregate.org/MAGIC
	// unsigned int
	// msb32(register unsigned int x)
	// {
	//	x |= (x >> 1);
	//	x |= (x >> 2);
	//	x |= (x >> 4);
	//	x |= (x >> 8);
	//	x |= (x >> 16);
	//	return(x & ~(x >> 1));
	// }

	unsigned rv = 0;
	unsigned upper;

	if (n < MSB_TABLE_SIZE)
		return msb_table[n];

	upper = n >> 16;
	if (upper) {
		rv += 16;
		n = upper;
	}
	else
		n &= 0xffff;

	upper = n >> 8;
	if (upper) {
		rv += 8;
		n = upper;
	}
	else
		n &= 0xff;

	upper = n >> 4;
	if (upper) {
		rv += 4;
		n = upper;
	}
	else
		n &= 0x0f;

	rv += u4_table[n];
	return rv;
}

// ----------------------------------------------------------------
unsigned find_msb_64(
	unsigned long long n)
{
	unsigned upper = n >> 32;

	if (n < MSB_TABLE_SIZE)
		return msb_table[n];

	if (upper)
		return find_msb_32(upper) + 32;
	else
		return find_msb_32((unsigned)n);
}

// ----------------------------------------------------------------
unsigned find_lsb_32(
	unsigned n)
{
	unsigned rv = 0;
	unsigned lower;

	lower = n & 0xffff;
	if (lower) {
		n = lower;
	}
	else {
		n >>= 16;
		rv += 16;
	}

	lower = n & 0xff;
	if (lower) {
		n = lower;
	}
	else {
		n >>= 8;
		rv += 8;
	}

	lower = n & 0xf;
	if (lower) {
		n = lower;
	}
	else {
		n >>= 4;
		rv += 4;
	}

	rv += l4_table[n];
	return rv;
}

// ----------------------------------------------------------------
unsigned find_lsb_64(
	unsigned long long n)
{
	unsigned lower = n;
	if (lower)
		return find_lsb_32(lower);
	else
		return find_lsb_32((unsigned)(n >> 32)) + 32;
}

// ----------------------------------------------------------------
unsigned calc_log2_unsigned(
	unsigned n,
	int want_ceil)
{
	unsigned l = find_msb_32(n);

	if (want_ceil == IFLOOR) {
		return l;
	}
	else {
		if (((unsigned)1 << l) == n)
			return l;
		else
			return l+1;
	}
}

// ----------------------------------------------------------------
unsigned long long calc_log2_unsigned_ll(
	unsigned long long n,
	int want_ceil)
{
	unsigned long long l = (unsigned long long)find_msb_64(n);

	if (want_ceil == IFLOOR) {
		return l;
	}
	else {
		if (((unsigned long long)1LL << l) == n)
			return l;
		else
			return l+1;
	}
}

// ----------------------------------------------------------------
#ifdef MAKE_MSB_TABLES
#include <stdio.h>
int main(void)
{
	unsigned n = 65536;
	printf("unsigned msb_table[] = {\n");
	for (unsigned i = 0; i < n; i++) {
		unsigned pos = find_msb_32((unsigned short)i);
		if ((i & 3) == 0)
			printf("\t");
		printf("%2u /*%4u*/,", pos, i);
		if ((i & 3) == 3)
			printf("\n");
	}
	printf("};\n");
	printf("#define MSB_TABLE_SIZE (sizeof(msb_table)/sizeof(msb_table[0]))\n");
}
#endif
