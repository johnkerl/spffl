// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef TVECTOR_H
#define TVECTOR_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
template <class element_type> class tvector;
template <class element_type> class tmatrix;
#include "int_gcd.h"
#include "tmatrix.h"

template <class element_type>
static int tvqcmp(const void *pv1, const void *pv2);

template <class element_type>
static std::ostream &operator<<(std::ostream &os,
                                const tvector<element_type> &v);

template <class element_type>
static std::istream &operator>>(std::istream &is, tvector<element_type> &v);

template <class element_type>
static std::istringstream &operator>>(std::istringstream &iss,
                                      tvector<element_type> &v);

// ================================================================
template <class element_type> class tvector {
public:
  // ================================================================
  // Constructors

  // ----------------------------------------------------------------
  tvector(void) {
    this->num_elements = 0;
    this->elements = 0;
  }

  // ----------------------------------------------------------------
  tvector(int init_num_elements) {
    if (init_num_elements <= 0) {
      std::cerr << "tvector::tvector():  Vector size must be > 0; got "
                << init_num_elements << ".  Exiting." << std::endl;
      exit(1);
    }

    this->num_elements = init_num_elements;
    this->elements = new element_type[init_num_elements];
  }

  // ----------------------------------------------------------------
  tvector(element_type e, int init_num_elements) {
    if (init_num_elements <= 0) {
      std::cerr << "tvector::tvector():  Vector size must be > 0; got "
                << init_num_elements << ".  Exiting." << std::endl;
      exit(1);
    }

    this->num_elements = init_num_elements;
    this->elements = new element_type[init_num_elements];
    for (int i = 0; i < this->num_elements; i++)
      this->elements[i] = e;
  }

  // ----------------------------------------------------------------
  tvector(const tvector<element_type> &that) {
    this->num_elements = that.num_elements;
    this->elements = new element_type[that.num_elements];
    for (int i = 0; i < that.num_elements; i++)
      this->elements[i] = that.elements[i];
  }

  // ----------------------------------------------------------------
  ~tvector(void) {
    if (this->elements != 0) {
      delete[] this->elements;
      this->elements = 0;
    }
    this->num_elements = 0;
  }

  // ================================================================
  // Operators

  // ----------------------------------------------------------------
  tvector<element_type> &operator=(tvector<element_type> that) {
    this->num_elements = that.num_elements;
    if (this->elements == 0) {
      this->elements = new element_type[that.num_elements];
    } else if (this->num_elements < that.num_elements) {
      delete[] this->elements;
      this->elements = new element_type[that.num_elements];
    }
    for (int i = 0; i < that.num_elements; i++)
      this->elements[i] = that.elements[i];
    return *this;
  }

  // ----------------------------------------------------------------
  tvector<element_type> &operator=(const element_type scalar) {
    if (this->elements) {
      for (int i = 0; i < this->num_elements; i++)
        this->elements[i] = scalar;
    } else {
      this->num_elements = 1;
      this->elements = new element_type[1];
      this->elements[0] = scalar;
    }
    return *this;
  }

  // ----------------------------------------------------------------
  // I/O format:  all elements on one line, delimited by whitespace.
  friend std::ostream &operator<< <>(std::ostream &os,
                                     const tvector<element_type> &v);

  friend std::istream &operator>><>(std::istream &is, tvector<element_type> &v);

  friend std::istringstream &operator>>
      <>(std::istringstream &iss, tvector<element_type> &v);

  // ----------------------------------------------------------------
  // See comment for istringstream >>:  the vector must already have one
  // element. The istream input operator expects only whitespace-delimited
  // elements, e.g. "1 2 3".  The bracket_in() method, by contrast, expects
  // whitespace-delimited elements, surrounded by brackets:  e.g. "[1 2 3]".
  int bracket_in(char *string) {
    char *copy = strdup(string);

    char *pleft = strchr(copy, '[');
    if (pleft == 0) {
      free(copy);
      return 0;
    }
    pleft++;

    char *pright = strrchr(pleft, ']');
    if (pright == 0) {
      free(copy);
      return 0;
    }
    *pright = 0;

    std::istringstream iss(pleft, std::ios_base::in);
    iss >> *this;
    if (iss.fail()) {
      free(copy);
      return 0;
    }

    free(copy);
    return 1;
  }

  // ----------------------------------------------------------------
  // The vector must already contain at least one element.  See the comment
  // above the istream operator.
  int load_from_file(char *file_name) {
    if ((strcmp(file_name, "-") == 0) || (strcmp(file_name, "@") == 0)) {
      std::cin >> *this;
      if (std::cin.fail())
        return 0;
      else
        return 1;
    }

    std::ifstream ifs;
    ifs.open(file_name, std::ifstream::in);

    if (ifs.fail()) {
      std::cerr << "tvector::load_from_file:  couldn't open \"" << file_name
                << "\"\n";
      return 0;
    }

    ifs >> *this;

    if (ifs.fail()) {
      std::cerr << "tvector::load_from_file:  scan failure reading \""
                << file_name << "\"\n";
      ifs.close();
      return 0;
    }
    ifs.close();
    return 1;
  }

  // ----------------------------------------------------------------
  // For this method, the vector may have the default constructor.
  // The "zero" argument is used to set the modulus for parameterized types.
  int load_from_file(char *file_name, element_type zero) {
    if (this->elements)
      delete[] this->elements;
    this->num_elements = 1;
    this->elements = new element_type[1];
    this->elements[0] = zero;
    return this->load_from_file(file_name);
  }

  // ----------------------------------------------------------------
  // No spaces between elements.  (Instead, perhaps I could implement a
  // derived iomanip, and then just use ostream <<.)
  void sqzout(std::ostream &os) {
    for (int i = 0; i < this->num_elements; i++)
      os << this->elements[i];
  }

  // ----------------------------------------------------------------
  // Carriage return between elements.
  void crout(std::ostream &os) {
    for (int i = 0; i < this->num_elements; i++) {
      os << this->elements[i];
      os << "\n";
    }
  }

  // ----------------------------------------------------------------
  element_type &operator[](int index) {
    if ((index < 0) || (index >= this->num_elements)) {
      std::cerr << "tvector array operator: index " << index
                << " out of bounds " << 0 << ":" << (this->num_elements - 1)
                << std::endl;
      exit(1);
    }
    return this->elements[index];
  }

  // ----------------------------------------------------------------
  tvector<element_type> operator+(tvector<element_type> that) {
    this->check_equal_lengths(that);
    tvector<element_type> rv(this->num_elements);
    for (int i = 0; i < this->num_elements; i++)
      rv.elements[i] = this->elements[i] + that.elements[i];
    return rv;
  }

  // ----------------------------------------------------------------
  tvector<element_type> operator-(tvector<element_type> that) {
    this->check_equal_lengths(that);
    tvector<element_type> rv(this->num_elements);
    for (int i = 0; i < this->num_elements; i++)
      rv.elements[i] = this->elements[i] - that.elements[i];
    return rv;
  }

  // ----------------------------------------------------------------
  tvector<element_type> operator-(void) {
    tvector<element_type> rv(this->num_elements);
    for (int i = 0; i < this->num_elements; i++)
      rv.elements[i] = -this->elements[i];
    return rv;
  }

  // ----------------------------------------------------------------
  tvector<element_type> operator*(element_type s) {
    tvector<element_type> rv(this->num_elements);
    for (int i = 0; i < this->num_elements; i++)
      rv.elements[i] = this->elements[i] * s;
    return rv;
  }

  // ----------------------------------------------------------------
  // This is componentwise multiplication (u * v), useful for implementing
  // direct products of rings.
  //
  // Use dot() (e.g. u.dot(v)) for inner product, or tmatrix's outer() (e.g.
  // tmatrix::outer(u, v)) for outer product.

  tvector<element_type> operator*(tvector<element_type> that) {
    this->check_equal_lengths(that);
    tvector<element_type> rv(this->num_elements);
    for (int i = 0; i < this->num_elements; i++)
      rv.elements[i] = this->elements[i] * that.elements[i];
    return rv;
  }

  // ----------------------------------------------------------------
  // (Row) vector times matrix.

  tvector<element_type> operator*(tmatrix<element_type> A) {
    int i, j;
    int Anr = A.get_num_rows();
    int Anc = A.get_num_cols();

    if (this->num_elements != Anr) {
      std::cerr << "tvector operator*(): Incompatibly dimensioned "
                << "operands (" << this->num_elements << "," << Anr << "x"
                << Anc << ")." << std::endl;
      exit(1);
    }

    tvector<element_type> rv(Anc);
    element_type t0 = this->elements[0];
    element_type zero = t0 - t0;
    for (j = 0; j < Anc; j++)
      rv.elements[j] = zero;

    for (j = 0; j < Anc; j++)
      for (i = 0; i < Anr; i++)
        rv.elements[j] += this->elements[i] * A[i][j];

    // [ 0 1 2 3 ] = [ 0 1 2 ]   [ 00 01 02 03 ]j
    //   rv            t       *i[ 10 11 12 13 ]
    //   j             i         [ 20 21 22 23 ]

    return rv;
  }

  // ----------------------------------------------------------------
  element_type dot(tvector<element_type> that) {
    this->check_equal_lengths(that);
    element_type rv = this->elements[0] - this->elements[0];
    for (int i = 0; i < this->num_elements; i++)
      rv += this->elements[i] * that.elements[i];
    return rv;
  }

  // ----------------------------------------------------------------
  // Elementwise exponentiation.
  tvector<element_type> exp(int power) {
    tvector<element_type> rv(this->num_elements);
    for (int i = 0; i < this->num_elements; i++)
      rv.elements[i] = this->elements[i].exp(power);
    return rv;
  }

  // ----------------------------------------------------------------
  // Componentwise division.
  tvector<element_type> operator/(tvector<element_type> that) {
    this->check_equal_lengths(that);
    tvector<element_type> rv(this->num_elements);
    for (int i = 0; i < this->num_elements; i++)
      rv.elements[i] = this->elements[i] / that.elements[i];
    return rv;
  }

  // ----------------------------------------------------------------
  tvector<element_type> operator+=(tvector<element_type> that) {
    *this = *this + that;
    return *this;
  }
  tvector<element_type> operator-=(tvector<element_type> that) {
    *this = *this - that;
    return *this;
  }
  tvector<element_type> operator*=(element_type e) {
    for (int i = 0; i < this->num_elements; i++)
      this->elements[i] *= e;
    return *this;
  }
  void mult_by(element_type e) {
    for (int i = 0; i < this->num_elements; i++)
      this->elements[i] *= e;
  }
  tvector<element_type> operator*=(tvector<element_type> that) {
    this->check_equal_lengths(that);
    for (int i = 0; i < this->num_elements; i++)
      this->elements[i] *= that.elements[i];
    return *this;
  }
  tvector<element_type> operator/=(element_type e) {
    for (int i = 0; i < this->num_elements; i++)
      this->elements[i] /= e;
    return *this;
  }

  // ----------------------------------------------------------------
  // Instantiate this template only for data types for which a gcd() function
  // has been implemented.
  element_type vgcd(void) {
    element_type rv = this->elements[0];
    for (int i = 1; i < this->num_elements; i++) {
      rv = gcd(rv, this->elements[i]);
    }
    return rv;
  }

  // ----------------------------------------------------------------
  // This is a step in the row-reduction algorithm which benefits from
  // hand-tuning.  The naive way to code it is:
  //   *this = *this * a - that * b;
  // which results in allocating, copying, freeing, etc.

  void accum_row_mul(element_type a, element_type b,
                     tvector<element_type> &that) {
    if (this->num_elements != that.num_elements)
      (void)check_equal_lengths(that);
    for (int i = 0; i < this->num_elements; i++)
      this->elements[i] = this->elements[i] * a - that.elements[i] * b;
  }

  // ----------------------------------------------------------------
  bool operator==(tvector<element_type> &that) {
    if (this->num_elements != that.num_elements)
      return false;
    for (int i = 0; i < this->num_elements; i++)
      if (this->elements[i] != that.elements[i])
        return false;
    return true;
  }

  // ----------------------------------------------------------------
  bool operator!=(tvector<element_type> &that) { return !(*this == that); }

  // ----------------------------------------------------------------
  bool operator==(element_type e) {
    for (int i = 0; i < this->num_elements; i++)
      if (this->elements[i] != e)
        return false;
    return true;
  }

  // ----------------------------------------------------------------
  bool operator!=(element_type e) { return !(*this == e); }

  // ----------------------------------------------------------------
  // Return value:  True/false.  rpos:  index, if found.
  int find_leader_pos(element_type &rzero, int &rpos) {
    for (int j = 0; j < this->num_elements; j++) {
      if (this->elements[j] != rzero) {
        rpos = j;
        return 1;
      }
    }
    return 0;
  }

  // ----------------------------------------------------------------
  void sort(void) {
    qsort(this->elements, this->num_elements, sizeof(element_type),
          tvqcmp<element_type>);
  }

  // ----------------------------------------------------------------
  void ptrswap(tvector<element_type> &that) {
    if (this->num_elements != that.num_elements)
      (void)check_equal_lengths(that);
    element_type *temp = this->elements;
    this->elements = that.elements;
    that.elements = temp;
  }

  // ----------------------------------------------------------------
  void check_equal_lengths(tvector<element_type> &that) {
    if (this->num_elements != that.num_elements) {
      std::cerr << "tvector operator+():  Incompatibly sized arguments ("
                << this->num_elements << ", " << that.num_elements << ")."
                << std::endl;
      exit(1);
    }
  }

  // ----------------------------------------------------------------
  void trim_num_elements(int new_num_elements) {
    if ((new_num_elements < 1) || (new_num_elements > this->num_elements)) {
      std::cerr << "tvector trim_num_elements: new count " << new_num_elements
                << " out of bounds " << 1 << ":" << this->num_elements
                << std::endl;
      exit(1);
    }
    this->num_elements = new_num_elements;
  }

  // ----------------------------------------------------------------
  element_type *expose(void) { return this->elements; }

  // ----------------------------------------------------------------
  int get_num_elements(void) { return this->num_elements; }

private:
  // ================================================================
  element_type *elements;
  int num_elements;
};

// ================================================================
template <class element_type>
static std::ostream &operator<<(std::ostream &os,
                                const tvector<element_type> &v) {
  for (int i = 0; i < v.num_elements; i++) {
    os << v.elements[i];
    if (i < (v.num_elements - 1))
      os << " ";
  }
  return os;
}

// ----------------------------------------------------------------
// See comment for istringstream >>:  the vector must already have one element.

template <class element_type>
static std::istream &operator>>(std::istream &is, tvector<element_type> &v) {
  // Read a line and use istringstream >>.
  char line[2048];
  is.getline(line, sizeof(line));
  std::istringstream iss(line, std::ios_base::in);
  iss >> v;
  if (iss.fail()) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

// ----------------------------------------------------------------
// The vector must already contain at least one element, even though it
// will be discarded.  I know no other way to set the modulus for mod types,
// other than requiring all input data to have moduli for each and every
// element (yuk).

template <class element_type>
static std::istringstream &operator>>(std::istringstream &iss,
                                      tvector<element_type> &v) {
  const int init_size = 10;
  const int more_size = 10;
  int alloc_size = init_size;

  if (!v.elements || (v.num_elements < 1)) {
    iss.setstate(std::ios::badbit);
    std::cerr << "tvector string >>:  must already have one element.\n";
    return iss;
  }

  element_type zero = v.elements[0] - v.elements[0];
  if (v.elements)
    delete[] v.elements;
  v.elements = 0;
  v.num_elements = 0;

  v.elements = new element_type[alloc_size];
  while (1) {
    if (iss.eof()) {
      break;
    }

    // xxx append method w/ optional #growth arg
    if (v.num_elements >= alloc_size) {
      alloc_size += more_size;
      element_type *ptemp = new element_type[alloc_size];
      for (int i = 0; i < v.num_elements; i++)
        ptemp[i] = v.elements[i];
      delete[] v.elements;
      v.elements = ptemp;
    }
    v.elements[v.num_elements] = zero; // E.g. set modulus.
    iss >> v.elements[v.num_elements];
    if (iss.fail()) {
      std::cerr << "tvector istringstream >>: scan failure"
                << " at vector element " << v.num_elements << ".\n";
      std::cerr << "String: <<" << iss.str() << ">>\n";
      std::cerr << "Position: " << iss.tellg() << "\n";
      return iss;
    }
    v.num_elements++;
  }

  return iss;
}

// ----------------------------------------------------------------
template <class element_type>
static int tvqcmp(const void *pv1, const void *pv2) {
  const element_type *p1 = (const element_type *)pv1;
  const element_type *p2 = (const element_type *)pv2;
  if (*p1 < *p2)
    return -1;
  if (*p1 > *p2)
    return 1;
  return 0;
}

#endif // TVECTOR_H
