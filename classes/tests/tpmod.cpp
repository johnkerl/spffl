#include "tmatrix.h"
#include "zppolymod_t.h"

//// ----------------------------------------------------------------
//void test_poly_math(void)
//{
//	zppoly_t r(1,0,0,1,1,2);
//	zppoly_t a(0,0,1,1,1,2);
//	zppoly_t b;
//	b = a / r; std::cout << b << std::endl;
//	b = a % r; std::cout << b << std::endl;
//	b = r / a; std::cout << b << std::endl;
//	b = r % a; std::cout << b << std::endl;
//}

// ----------------------------------------------------------------
void test_tvector()
{
	int n = 10;
	int i;
	tvector<zppolymod_t> u(n);
	tvector<zppolymod_t> v(n);
	tvector<zppolymod_t> w(n);

	std::cout << "vector test:\n";
	zppoly_t r(1,0,0,1,1,2);

	for (i = 0; i < n; i++) {
		u[i] = zppolymod_t(zppoly_t::from_base_rep(i, 2), r);
		v[i] = zppolymod_t(zppoly_t::from_base_rep(i*i, 2), r);
	}
	w = u + v;

	std::cout << "u: " << u << std::endl;
	std::cout << "v: " << v << std::endl;
	std::cout << "w: " << w << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_tmatrix()
{
	zppoly_t r(1,0,0,1,1,2);
	int i, j;
	int nr = 3, nc = 4;
	tmatrix<zppolymod_t> A(nr, nc);
	std::cout << "matrix test:\n";

	for (i = 0; i < nr; i++)
		for (j = 0; j < nc; j++)
			A[i][j] = zppolymod_t(
				zppoly_t::from_base_rep(i+j, 2), r);

	std::cout << A << std::endl;

	tmatrix<zppolymod_t> B(A);
	std::cout << B << std::endl;
	B = A[0][0];
	std::cout << B << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_vector_times_scalar()
{
	std::cout << "vr * sc test:\n";
	zppoly_t r(1,0,0,1,1,2);
	int i;
	int n = 10;
	tvector<zppolymod_t> v(n);

	for (i = 0; i < n; i++)
		v[i] = zppolymod_t(zppoly_t::from_base_rep(i, 2), r);

	std::cout << v << std::endl;
	v = v * zppolymod_t(zppoly_t::from_base_rep(7, 2), r);
	std::cout << v << std::endl;

	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_matrix_times_matrix()
{
	std::cout << "mx * mx test:\n";
	zppoly_t r(1,0,0,1,1,2);
	zppoly_t zero(0,2);
	int i;
	int l = 4, m = 3, n = 5;

	tmatrix<zppolymod_t> A(l, m);
	tmatrix<zppolymod_t> B(m, n);
	tmatrix<zppolymod_t> C(l, n);

	A = zppolymod_t(zero, r);
	B = zppolymod_t(zero, r);
	C = zppolymod_t(zero, r);

	for (i = 0; i < m; i++) {
		A[i  ][i] = zppolymod_t(zppoly_t::from_base_rep(i+1, 2), r);
		A[i+1][i] = zppolymod_t(zppoly_t::from_base_rep(i+2, 2), r);
	}
	std::cout << A << std::endl;

	for (i = 0; i < m; i++) {
		B[i][i  ] = zppolymod_t(zppoly_t::from_base_rep(i+1, 2), r);
		B[i][i+1] = zppolymod_t(zppoly_t::from_base_rep(i+2, 2), r);
	}
	std::cout << B << std::endl;

	C = A * B;
	std::cout << C << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_row_replacement()
{
	std::cout << "mx row-replacement test:\n";
	zppoly_t r(1,0,0,1,1,2);
	int i, j;
	int n = 6;
	tmatrix<zppolymod_t> A(n, n);
	tvector<zppolymod_t> v(n);

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			A[i][j] = zppolymod_t(
				zppoly_t::from_base_rep(j+i+3, 2), r);
	for (i = 0; i < n; i++)
		v[i] = zppolymod_t(zppoly_t::from_base_rep(i, 2), r);

	std::cout << A << std::endl;
	std::cout << v << std::endl << std::endl;
	A[3] = v;
	std::cout << A << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_matrix_times_vector()
{
	std::cout << "mx * vr test:\n";
//	int p = 11;
//	int m = 3;
//	int n = 5;
//	int i;

//	tmatrix<zppolymod_t> A(m, n);
//	tvector<zppolymod_t> v(n);
//	tvector<zppolymod_t> w(m);

//	A = zppolymod_t(0, p);
//	v = zppolymod_t(0, p);

//	for (i = 0; i < m; i++) {
//		A[i][i  ] = zppolymod_t(i + 1, p);
//		A[i][i+1] = zppolymod_t(i + 2, p);
//	}
//	std::cout << A << std::endl;

//	for (i = 0; i < n; i++) {
//		v[i] = zppolymod_t(i + 3, p);
//	}
//	std::cout << v << std::endl << std::endl;

//	w = A * v;
//	std::cout << w << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_vector_plus_vector()
{
	std::cout << "vr + vr test:\n";
//	int p = 11;
//	int n = 5;
//	int i;

//	tvector<zppolymod_t> u(n);
//	tvector<zppolymod_t> v(n);
//	tvector<zppolymod_t> w(n);

//	for (i = 0; i < n; i++) {
//		u[i] = zppolymod_t(i + 2, p);
//		v[i] = zppolymod_t(i + 3, p);
//	}
//	std::cout << u << std::endl;
//	std::cout << v << std::endl;
//	w = u + v;
//	std::cout << w << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_matrix_plus_matrix()
{
	std::cout << "mx + mx test:\n";
//	int p = 11;
//	int m = 4;
//	int n = 5;
//	int i, j;

//	tmatrix<zppolymod_t> A(m, n);
//	tmatrix<zppolymod_t> B(m, n);
//	tmatrix<zppolymod_t> C(m, n);

//	for (i = 0; i < m; i++) {
//		for (j = 0; j < n; j++) {
//			A[i][j] = zppolymod_t(i + j, p);
//			B[i][j] = zppolymod_t(i * j, p);
//		}
//	}
//	std::cout << A << std::endl;
//	std::cout << B << std::endl;
//	C = A + B;
//	std::cout << C << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
int main()
{
	test_tvector();
	test_tmatrix();
	test_vector_times_scalar();
	test_matrix_times_matrix();
	test_row_replacement();
	//test_matrix_times_vector();
	//test_vector_plus_vector();
	//test_matrix_plus_matrix();

	return 0;
}
