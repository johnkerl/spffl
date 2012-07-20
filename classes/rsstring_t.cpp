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

#include <cstring>
#include "rsstring_t.h"

#define INIT_SIZE 128
#define INCR_SIZE 128

// ----------------------------------------------------------------
rsstring_t::rsstring_t(void)
{
	this->alloc_size = INIT_SIZE;
	this->buffer = new char[this->alloc_size];
	this->buffer[0] = 0;
	this->eosidx = 0;
}

// ----------------------------------------------------------------
rsstring_t::rsstring_t(const rsstring_t & that)
{
	this->alloc_size = that.alloc_size;
	this->buffer = new char[this->alloc_size];
	strcpy(this->buffer, that.buffer);
	this->eosidx = that.eosidx;
}

// ----------------------------------------------------------------
rsstring_t::~rsstring_t(void)
{
	if (this->buffer) {
		delete [] this->buffer;
		this->buffer =0;
	}
	this->alloc_size = 0;
	this->eosidx = 0;
}

// ----------------------------------------------------------------
rsstring_t rsstring_t::operator=(rsstring_t that)
{
	if (this->buffer)
		delete [] this->buffer;
	this->alloc_size = that.alloc_size;
	this->buffer = new char[this->alloc_size];
	strcpy(this->buffer, that.buffer);
	this->eosidx = that.eosidx;
	return *this;
}

// ----------------------------------------------------------------
void rsstring_t::append_string(char * s)
{
	int len = strlen(s);
	this->make_room(len);
	strcpy(&this->buffer[this->eosidx], s);
	this->eosidx += len;
}

// ----------------------------------------------------------------
void rsstring_t::append_char(char c)
{
	this->make_room(1);
	this->buffer[this->eosidx++] = c;
	this->buffer[this->eosidx] = 0;
}

// ----------------------------------------------------------------
void rsstring_t::make_room(int len)
{
	int bytes_left = this->alloc_size - this->eosidx - 1;
	if (len <= bytes_left)
		return;

	int incr = len - bytes_left;
	if (incr < INCR_SIZE)
		incr = INCR_SIZE;
	this->alloc_size += incr;
	char * temp = this->buffer;
	this->buffer = new char[this->alloc_size];
	strcpy(this->buffer, temp);
	delete [] temp;
}
