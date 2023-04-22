// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "rsstring_t.h"
#include <cstring>

#define INIT_SIZE 128
#define INCR_SIZE 128
namespace spffl::base {

// ----------------------------------------------------------------
rsstring_t::rsstring_t(void) {
  this->alloc_size = INIT_SIZE;
  this->buffer = new char[this->alloc_size];
  this->buffer[0] = 0;
  this->eosidx = 0;
}

// ----------------------------------------------------------------
rsstring_t::rsstring_t(const rsstring_t &that) {
  this->alloc_size = that.alloc_size;
  this->buffer = new char[this->alloc_size];
  strcpy(this->buffer, that.buffer);
  this->eosidx = that.eosidx;
}

// ----------------------------------------------------------------
rsstring_t::~rsstring_t(void) {
  if (this->buffer) {
    delete[] this->buffer;
    this->buffer = 0;
  }
  this->alloc_size = 0;
  this->eosidx = 0;
}

// ----------------------------------------------------------------
rsstring_t rsstring_t::operator=(rsstring_t that) {
  if (this->buffer)
    delete[] this->buffer;
  this->alloc_size = that.alloc_size;
  this->buffer = new char[this->alloc_size];
  strcpy(this->buffer, that.buffer);
  this->eosidx = that.eosidx;
  return *this;
}

// ----------------------------------------------------------------
void rsstring_t::append_string(char *s) {
  int len = strlen(s);
  this->make_room(len);
  strcpy(&this->buffer[this->eosidx], s);
  this->eosidx += len;
}

// ----------------------------------------------------------------
void rsstring_t::append_char(char c) {
  this->make_room(1);
  this->buffer[this->eosidx++] = c;
  this->buffer[this->eosidx] = 0;
}

// ----------------------------------------------------------------
void rsstring_t::make_room(int len) {
  int bytes_left = this->alloc_size - this->eosidx - 1;
  if (len <= bytes_left)
    return;

  int incr = len - bytes_left;
  if (incr < INCR_SIZE)
    incr = INCR_SIZE;
  this->alloc_size += incr;
  char *temp = this->buffer;
  this->buffer = new char[this->alloc_size];
  strcpy(this->buffer, temp);
  delete[] temp;
}

} // namespace
