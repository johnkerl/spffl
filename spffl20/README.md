This is a putative --- perhaps never-to-be-completed --- port of `../spffl` to use C++ 20, with significant positive impacts on code deduplication.

To do:

* Use concepts (ring element) for polynomial coefficients
* Polynomial-of class
* Euclidean domain to take `std::is_integral` or is-polynomial
* How to work in the ad-hoc `f2poly` class which uses bit-packing (can't be polynomial-of-byte)
* Templates for residue rings and quotient rings (both requiring Euclidean GCD)
* Templates for matrix and vector; probably use STL
* Still want a specialized class for matrix-of-bit with bit-packing (not matrix-of-byte)
