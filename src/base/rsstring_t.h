// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef RSSTRING_T_H
#define RSSTRING_T_H

// This is just a simple class for a resizable string.
namespace spffl::base {

class rsstring_t {
public:
  rsstring_t(void);
  rsstring_t(const rsstring_t &that);
  ~rsstring_t();
  rsstring_t operator=(rsstring_t that);

  void append_string(char *s);
  void append_char(char c);

  int get_length(void) { return this->eosidx; }
  char *get_buffer(void) { return this->buffer; }

private:
  char *buffer;
  int alloc_size;
  int eosidx;

  void make_room(int len);
};

}

#endif // RSSTRING_T_H
