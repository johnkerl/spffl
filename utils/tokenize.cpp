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

// ================================================================
// tokenize.c
//
// John Kerl
// 2001/08/22
// ================================================================

#include "tokenize.h"

// ----------------------------------------------------------------
// Breaks a single character string into an array of tokens.
//
// The logic is straightforward:  A token is a sequence of non-whitespace
// characters.  A token is delimited by the beginning of the input string, a
// whitespace character, or the end of the string.

// Returns argc
int tokenize(
	char        * line,
	const char  * seps,
	char       ** argv,
	int           max_arguments)
{
	char * readp;
	int    inside_token = 0;
	int    argc = 0;
	const char * psep;
	int    is_sep;

	for (readp = line; *readp; readp++) {

		is_sep = 0;
		for (psep = seps; *psep; psep++) {
			if (*readp == *psep) {
				is_sep = 1;
				break;
			}
		}

		if (is_sep) { // Is a separator
			if (inside_token) {
				inside_token = 0;
				*readp = 0;
			}
			//else, whitespace is not copied.
		}
		else { // Not a separator
			if (!inside_token) { // Start of token
				inside_token = 1;
				if (argc >= max_arguments)
					break;
				argv[argc] = readp;
				argc++;
			}
			// else, continuation of token
		}
	}

	if (inside_token) { // End of input line terminates a token.
		*readp = 0;
		readp++;
	}
	return argc;
}

// ----------------------------------------------------------------
int count_tokens(
	char       * line,
	const char * seps)
{
	char * readp;
	int    inside_token = 0;
	int    argc = 0;
	const char * psep;
	int    is_sep;

	for (readp = line; *readp; readp++) {

		is_sep = 0;
		for (psep = seps; *psep; psep++) {
			if (*readp == *psep) {
				is_sep = 1;
				break;
			}
		}

		if (is_sep) { // Is a separator
			if (inside_token) {
				inside_token = 0;
			}
			//else, whitespace is not copied.
		}
		else { // Not a separator
			if (!inside_token) { // Start of token
				inside_token = 1;
				argc++;
			}
			// else, continuation of token
		}
	}

	if (inside_token) { // End of input line terminates a token.
		readp++;
	}
	return argc;
}
