#include "tmatrix.h"
#include "mod_t.h"

// ----------------------------------------------------------------
void test_tvector()
{
	int n = 10;
	int m = 11;
	int i;
	tvector<mod_t> u(n);
	tvector<mod_t> v(n);
	tvector<mod_t> w(n);

	std::cout << "vector test:\n";

	for (i = 0; i < n; i++) {
		u[i] = mod_t(i, m);
		v[i] = mod_t(i*i, m);
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
	int m = 11;
	int i, j;
	int nr = 3, nc = 4;
	tmatrix<mod_t> A(nr, nc);
	std::cout << "matrix test:\n";

	// Should generate an out-of-bounds error:
	// std::cout << A[4][3] << std::endl;
	// std::cout << A[2][4] << std::endl;

	for (i = 0; i < nr; i++)
		for (j = 0; j < nc; j++)
			A[i][j] = mod_t(i+j, m);

	std::cout << A << std::endl;
	A = mod_t(3, 11);
	std::cout << A << std::endl;

	tmatrix<mod_t> B(A);
	B = mod_t(4, 11);

	std::cout << B << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_vector_times_scalar()
{
	std::cout << "vr * sc test:\n";
	int i;
	int m = 11;
	int n = 4;

	tvector<mod_t> u(n);

	for (i = 0; i < n; i++)
		u[i] = mod_t(i, m);
	std::cout << u << std::endl;
	u = u * mod_t(8, 11);
	std::cout << u << std::endl;

	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_matrix_times_matrix()
{
	std::cout << "mx * mx test:\n";
	int p = 11;
	int l = 4;
	int m = 3;
	int n = 5;
	int i;

	tmatrix<mod_t> A(l, m);
	tmatrix<mod_t> B(m, n);
	tmatrix<mod_t> C(l, n);

	A = mod_t(0, p);
	B = mod_t(0, p);
	C = mod_t(0, p);

	for (i = 0; i < m; i++) {
		A[i  ][i] = mod_t(i+1, p);
		A[i+1][i] = mod_t(i+2, p);
	}
	std::cout << A << std::endl;

	for (i = 0; i < m; i++) {
		B[i][i  ] = mod_t(i+2, p);
		B[i][i+1] = mod_t(i+3, p);
	}
	std::cout << B << std::endl;

	C = A * B;
	std::cout << C << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_matrix_times_vector()
{
	std::cout << "mx * vr test:\n";
	int p = 11;
	int m = 3;
	int n = 5;
	int i;

	tmatrix<mod_t> A(m, n);
	tvector<mod_t> v(n);
	tvector<mod_t> w(m);

	A = mod_t(0, p);
	v = mod_t(0, p);

	for (i = 0; i < m; i++) {
		A[i][i  ] = mod_t(i + 1, p);
		A[i][i+1] = mod_t(i + 2, p);
	}
	std::cout << A << std::endl;

	for (i = 0; i < n; i++) {
		v[i] = mod_t(i + 3, p);
	}
	std::cout << v << std::endl << std::endl;

	w = A * v;
	std::cout << w << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_vector_plus_vector()
{
	std::cout << "vr + vr test:\n";
	int p = 11;
	int n = 5;
	int i;

	tvector<mod_t> u(n);
	tvector<mod_t> v(n);
	tvector<mod_t> w(n);

	for (i = 0; i < n; i++) {
		u[i] = mod_t(i + 2, p);
		v[i] = mod_t(i + 3, p);
	}
	std::cout << u << std::endl;
	std::cout << v << std::endl;
	w = u + v;
	std::cout << w << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
void test_matrix_plus_matrix()
{
	std::cout << "mx + mx test:\n";
	int p = 11;
	int m = 4;
	int n = 5;
	int i, j;

	tmatrix<mod_t> A(m, n);
	tmatrix<mod_t> B(m, n);
	tmatrix<mod_t> C(m, n);

	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			A[i][j] = mod_t(i + j, p);
			B[i][j] = mod_t(i * j, p);
		}
	}
	std::cout << A << std::endl;
	std::cout << B << std::endl;
	C = A + B;
	std::cout << C << std::endl;
	std::cout << "\n";
}

// ----------------------------------------------------------------
int main()
{
	test_tvector();
	test_tmatrix();
	test_vector_times_scalar();
	test_matrix_times_matrix();
	test_matrix_times_vector();
	test_vector_plus_vector();
	test_matrix_plus_matrix();

	return 0;
}
