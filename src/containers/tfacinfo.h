// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef TFACINFO_H
#define TFACINFO_H

#include "tvector.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#define TFACINFO_INIT_LENGTH 20
#define TFACINFO_INCR_LENGTH 20

template <class element_type> class tfacinfo;

template <class element_type>
static std::ostream &operator<<(std::ostream &os,
                                const tfacinfo<element_type> &v);

// ================================================================
template <class element_type> class tfacinfo {
private:
  // ================================================================
  struct factor_and_count_t {
    element_type factor;
    int count;
  } *pfactors_and_counts;
  int num_distinct;
  int num_allocated;

  int have_unit;
  element_type unit;

public:
  // ================================================================
  // Constructors

  // ----------------------------------------------------------------
  tfacinfo(void) {
    this->num_distinct        = 0;
    this->num_allocated       = TFACINFO_INIT_LENGTH;
    this->pfactors_and_counts = new factor_and_count_t[this->num_allocated];
    this->have_unit           = 0;
    // Let this->unit take its default constructor.
  }

  // ----------------------------------------------------------------
  tfacinfo(const tfacinfo<element_type> &that) {
    this->num_distinct        = that.num_distinct;
    this->num_allocated       = that.num_distinct;
    this->pfactors_and_counts = new factor_and_count_t[that.num_distinct];
    for (int i = 0; i < that.num_distinct; i++) {
      this->pfactors_and_counts[i] = that.pfactors_and_counts[i];
    }
    this->have_unit = that.have_unit;
    this->unit      = that.unit;
  }

  // ----------------------------------------------------------------
  tfacinfo<element_type> &operator=(tfacinfo<element_type> that) {
    if (this->pfactors_and_counts) {
      delete[] this->pfactors_and_counts;
    }

    this->num_distinct        = that.num_distinct;
    this->num_allocated       = that.num_distinct;
    this->pfactors_and_counts = new factor_and_count_t[that.num_distinct];
    for (int i = 0; i < that.num_distinct; i++) {
      this->pfactors_and_counts[i] = that.pfactors_and_counts[i];
    }
    this->have_unit = that.have_unit;
    this->unit      = that.unit;
  }

  // ----------------------------------------------------------------
  ~tfacinfo(void) {
    if (this->pfactors_and_counts) {
      delete[] this->pfactors_and_counts;
    }
    this->num_distinct        = 0;
    this->num_allocated       = 0;
    this->pfactors_and_counts = 0;
    this->have_unit           = 0;
  }

  // ----------------------------------------------------------------
  // I/O format:  all elements on one line, delimited by whitespace.
  friend std::ostream &operator<< <>(std::ostream &os,
                                     const tfacinfo<element_type> &v);

  // ----------------------------------------------------------------
  int get_num_distinct(void) { return this->num_distinct; }

  // ----------------------------------------------------------------
  // Units don't count.
  int get_num_factors(void) {
    int rv = 0;
    for (int i = 0; i < this->num_distinct; i++) {
      rv += this->pfactors_and_counts[i].count;
    }
    return rv;
  }

  // ----------------------------------------------------------------
  element_type get_ith_factor(int which) {
    this->bounds_check(which);
    return this->pfactors_and_counts[which].factor;
  }

  // ----------------------------------------------------------------
  int get_ith_count(int which) {
    this->bounds_check(which);
    return this->pfactors_and_counts[which].count;
  }

  // ----------------------------------------------------------------
  bool get_unit(element_type &runit) {
    if (this->have_unit) {
      runit = this->unit;
      return true;
    } else {
      return false;
    }
  }

  // ----------------------------------------------------------------
  void bounds_check(int which) {
    if ((which < 0) || (which >= this->num_distinct)) {
      std::cerr << "tfacinfo:  index " << which
                << " out of bounds 0:" << this->num_distinct - 1 << ".\n";
      exit(1);
    }
  }

  // ----------------------------------------------------------------
  void insert_factor(element_type e) { this->insert_factor(e, 1); }

  // ----------------------------------------------------------------
  // If the element is found, returns its index.  Else, returns the index
  // at which it should be located in order to preserve sorted factors.

private:
  bool find(element_type &re, int &ridx) {
#if 0
	// Need to find the bug.

		// Binary search.
		if (this->num_distinct == 0) {
			ridx = 0;
			return false;
		}

		int left = 0;
		int right = this->num_distinct - 1;
		int mid  = (right + left) / 2;

		if (re < this->pfactors_and_counts[left].factor) {
			ridx = left;
			return false;
		}
		if (re > this->pfactors_and_counts[right].factor) {
			ridx = right + 1;
			return false;
		}

		ridx = mid;
		while (1) {
			if ((left == mid) || (mid == right)) {
				ridx = mid;
				if (re == this->pfactors_and_counts[mid].factor)
					return true;
				if (re > this->pfactors_and_counts[mid].factor)
					ridx++;
				return false;
			}
			if (re == this->pfactors_and_counts[mid].factor) {
				ridx = mid;
				return true;
			}
			else if (re < this->pfactors_and_counts[mid].factor) {
				right = mid;
			}
			else {
				left = mid;
			}
			mid  = (right + left) / 2;
		}
		ridx = mid;
		if (re > this->pfactors_and_counts[mid].factor)
			ridx++;
		return false;
#else
    // Linear search.
    for (int i = 0; i < this->num_distinct; i++) {
      if (re == this->pfactors_and_counts[i].factor) {
        ridx = i;
        return true;
      }
      if (re < this->pfactors_and_counts[i].factor) {
        ridx = i;
        return false;
      }
    }
    ridx = this->num_distinct;
    return false;
#endif
  }

public:
  // ----------------------------------------------------------------
  void insert_factor(element_type e, int count) {
    int idx = 0;

    // Insert a repeated factor.
    if (this->find(e, idx)) {
      this->pfactors_and_counts[idx].count += count;
      return;
    }

    // Need to resize the array?
    if (this->num_distinct >= this->num_allocated) {
      factor_and_count_t *temp = this->pfactors_and_counts;
      this->num_allocated += TFACINFO_INCR_LENGTH;
      this->pfactors_and_counts = new factor_and_count_t[this->num_allocated];
      for (int i = 0; i < this->num_distinct; i++) {
        this->pfactors_and_counts[i] = temp[i];
      }
    }

    // Insert a new factor.  The find() method has returned the correct
    // insertion point.
    for (int i = this->num_distinct; i > idx; i--) {
      this->pfactors_and_counts[i] = this->pfactors_and_counts[i - 1];
    }

    this->pfactors_and_counts[idx].factor = e;
    this->pfactors_and_counts[idx].count  = count;
    this->num_distinct++;
  }

  // ----------------------------------------------------------------
  void insert_unit(element_type e) {
    if (this->have_unit) {
      this->unit *= e;
    } else {
      this->unit      = e;
      this->have_unit = 1;
    }
  }

  // ----------------------------------------------------------------
  // The class being instantiated may or may not have an exp() method.
  element_type tf_exp(element_type x, int e) {
    element_type zero = x - x;
    element_type xp   = x;

    if (x == zero) {
      if (e < 0) {
        std::cerr << "Division by zero.\n";
        exit(1);
      }
      if (e == 0) {
        std::cerr << "0 ^ 0 undefined.\n";
        exit(1);
      }
      return zero;
    }
    element_type one = x / x;
    element_type rv  = one;

    if (e == 0) {
      return rv;
    }

    if (e < 0) {
      if (e == -e) {
        std::cerr << "Can't handle MIN_INT.\n";
        exit(1);
      }
      xp = one / x;
      e  = -e;
    }

    while (e != 0) {
      if (e & 1) {
        rv *= xp;
      }
      e = (unsigned)e >> 1;
      xp *= xp;
    }

    return rv;
  }

  // ----------------------------------------------------------------
  void exp_all(int power) {
    if (this->have_unit) {
      // The element_type class (or native C++ type, for integers)
      // may not have an exp() method.
      this->unit = this->tf_exp(this->unit, power);
    }
    for (int i = 0; i < this->num_distinct; i++) {
      this->pfactors_and_counts[i].count *= power;
    }
  }

  // ----------------------------------------------------------------
  void merge(tfacinfo<element_type> &that) {
    for (int i = 0; i < that.num_distinct; i++) {
      this->insert_factor(that.pfactors_and_counts[i].factor,
                          that.pfactors_and_counts[i].count);
    }
    if (that.have_unit) {
      if (this->have_unit) {
        this->unit *= that.unit;
      } else {
        this->unit = that.unit;
      }
      this->have_unit = 1;
    }
  }

  // ----------------------------------------------------------------
  // In a template class, we don't know what 1 looks like.  It's simplest
  // to have it passed in.

  element_type unfactor(element_type one) {
    element_type rv = one;

    if (this->have_unit) {
      rv *= this->unit;
    }
    for (int i = 0; i < this->num_distinct; i++) {
      element_type f      = this->pfactors_and_counts[i].factor;
      element_type fpower = one;
      int power           = this->pfactors_and_counts[i].count;
      for (int j = 1; j <= power; j++) {
        fpower *= f;
      }
      rv *= fpower;
    }
    return rv;
  }

  // ----------------------------------------------------------------
  // Given the prime factorization p1^m1 ... pk^mk of n, how to enumerate all
  // factors of n?
  //
  // Example 72 = 2^3 * 3^2.  Exponent on 2 is one of 0, 1, 2, 3.  Exponent on
  // 3 is one of 0, 1, 2.  Number of possibilities:  product over i of (mi + 1).
  // Factors are:
  //
  //	2^0 3^0    1
  //	2^0 3^1    3
  //	2^0 3^2    9
  //	2^1 3^0    2
  //	2^1 3^1    6
  //	2^1 3^2   18
  //	2^2 3^0    4
  //	2^2 3^1   12
  //	2^2 3^2   36
  //	2^3 3^0    8
  //	2^3 3^1   24
  //	2^3 3^2   72

  int get_num_divisors(void) {
    if (this->num_distinct <= 0) {
      if (!this->have_unit) {
        std::cerr << "tfacinfo::get_num_divisors():  "
                     "No factors have been inserted.\n";
        exit(1);
      }
    }
    int rv = 1;
    for (int i = 0; i < this->num_distinct; i++) {
      rv *= this->pfactors_and_counts[i].count + 1;
    }
    return rv;
  }

  // ----------------------------------------------------------------
  // See comments to get_num_divisors.  k is treated as a multibase
  // representation over the bases mi+1.  (This may overflow a 32-bit
  // integer when factoring something large -- but if something really
  // has more than a billion factors, it is impractical to loop over all
  // its factors anyway.)

  element_type get_kth_divisor(int k, element_type one) {
    if (this->num_distinct <= 0) {
      if (this->have_unit) {
        // if (k == 0)
        return one;
      } else {
        std::cerr << "tfacinfo::get_kth_divisor():  "
                     "No factors have been inserted.\n";
        exit(1);
      }
    }

    element_type rv = one;
    int base, power;

    for (int i = 0; i < this->num_distinct; i++) {
      base  = this->pfactors_and_counts[i].count + 1;
      power = k % base;
      k     = k / base;
      rv *= this->tf_exp(this->pfactors_and_counts[i].factor, power);
    }
    return rv;
  }

  // ----------------------------------------------------------------
  // The output will be sorted from smallest to largest.
  tvector<element_type> get_all_divisors(element_type one) {
    if (this->num_distinct <= 0) {
      if (!this->have_unit) {
        std::cerr << "tfacinfo::get_all_divisors():  "
                  << "No factors have been inserted.\n";
        exit(1);
      }
    }
    int nd = this->get_num_divisors();
    tvector<element_type> rv(nd);
    for (int k = 0; k < nd; k++) {
      rv[k] = this->get_kth_divisor(k, one);
    }
    rv.sort();
    return rv;
  }

  // ----------------------------------------------------------------
  // The output will be sorted from smallest to largest.
  bool get_maximal_proper_divisors(tvector<element_type> &rv,
                                   element_type one) {
    if (this->num_distinct <= 0) {
      if (!this->have_unit) {
        std::cerr << "tfacinfo::get_maximal_proper_divisors():  "
                  << "No factors have been inserted.\n";
        exit(1);
      } else {
        return false;
      }
    }
    int nmpd = this->num_distinct;
    rv       = tvector<element_type>(nmpd);
    for (int k = 0; k < nmpd; k++) {
      tfacinfo<element_type> other(*this);
      other.pfactors_and_counts[k].count--;
      rv[k] = other.unfactor(one);
    }
    rv.sort();
    return true;
  }
};

// ================================================================
template <class element_type>
static std::ostream &operator<<(std::ostream &os,
                                const tfacinfo<element_type> &finfo) {
  if (finfo.have_unit) {
    os << finfo.unit;
  }
  for (int i = 0; i < finfo.num_distinct; i++) {
    if ((i > 0) || finfo.have_unit) {
      os << " ";
    }
    os << finfo.pfactors_and_counts[i].factor;
    if (finfo.pfactors_and_counts[i].count != 1) {
      os << "^" << finfo.pfactors_and_counts[i].count;
    }
  }
  return os;
}

#endif // TFACINFO_H
