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

// ----------------------------------------------------------------
// aggregate-magic pop count:
//static unsigned ones32(unsigned n)
//{
//	n -= ((n >> 1) & 0x55555555);
//	n = (((n >> 2) & 0x33333333) + (n & 0x33333333));
//	n = (((n >> 4) + n) & 0x0f0f0f0f);
//	n += (n >> 8);
//	n += (n >> 16);
//	return n & 0x0000003f;
//}

// MIT HAKMEM pop count:
static unsigned find_ones_32(unsigned n)
{
	unsigned r = n - ((n >> 1) & 033333333333) - ((n >> 2) & 011111111111);
	return ((r + (r >> 3)) & 030707070707) % 63;
}

static unsigned find_floor_log2_32(unsigned n)
{
     n |= (n >> 1);
     n |= (n >> 2);
     n |= (n >> 4);
     n |= (n >> 8);
     n |= (n >> 16);
     return find_ones_32(n) - 1; // If log(0) is to be -1
}

// ----------------------------------------------------------------
unsigned short find_msb_16(
	unsigned short n)
{
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	return n & ~(n >> 1) ;
}

unsigned find_msb_32(
	unsigned n)
{
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	return n & ~(n >> 1) ;
}

unsigned long long find_msb_64(
	unsigned long long n)
{
	n |= (n >> 1);
	n |= (n >> 2);
	n |= (n >> 4);
	n |= (n >> 8);
	n |= (n >> 16);
	n |= (n >> 32);
	return n & ~(n >> 1) ;
}

unsigned short find_lsb_16(
	unsigned short n)
{
	return n & -n;
}

unsigned find_lsb_32(
	unsigned n)
{
	return n & -n;
}

unsigned long long find_lsb_64(
	unsigned long long n)
{
	return (n & -n);
}

// ----------------------------------------------------------------
unsigned find_msb_pos_16(
	unsigned short n)
{
	return find_floor_log2_32(find_msb_16(n));
}

unsigned find_msb_pos_32(unsigned n)
{
	return find_floor_log2_32(find_msb_32(n));
}

unsigned find_lsb_pos_32(unsigned n)
{
	return find_floor_log2_32(find_lsb_32(n));
}

// ----------------------------------------------------------------
unsigned find_msb_pos_64(
	unsigned long long n)
{
	return find_floor_log2_32(find_msb_64(n));
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
