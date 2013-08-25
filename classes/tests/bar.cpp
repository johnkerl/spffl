// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

	tvector<float> g(f);
	g = 4;

	std::cout << f << std::endl;
	std::cout << g << std::endl;
}

// ----------------------------------------------------------------
void test_tmatrix()
{
	tmatrix<double> f(3, 4);

	// std::cout << f[4][3] << std::endl;
	// std::cout << f[2][4] << std::endl;

	std::cout << f << std::endl;
	f = 3.0;
	std::cout << f << std::endl;

	tmatrix<double> g(f);
	g = 4;

	std::cout << f << std::endl;
	std::cout << g << std::endl;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 4; j++)
			g[i][j] = i * 10 + j;
	std::cout << f << std::endl;
	std::cout << g << std::endl;
}

// ----------------------------------------------------------------
void test_vector_times_scalar()
{
	int i;
	int N = 4;

	tvector<double> f(N);

	for (i = 0; i < N; i++)
		f[i] = i;
	std::cout << f << std::endl;
	f = f * 4.0;
	std::cout << f << std::endl;

}

// ----------------------------------------------------------------
void test_matrix_times_matrix()
{
	int L = 4;
	int M = 3;
	int N = 5;
	int i;

	tmatrix<double> a(L, M);
	tmatrix<double> b(M, N);
	tmatrix<double> c(L, N);

	a = 0.0;
	b = 0.0;
	c = 0.0;

	for (i = 0; i < M; i++) {
		a[i  ][i] = i + 1.0;
		a[i+1][i] = i + 2.0;
	}
	std::cout << a << std::endl;

	for (i = 0; i < M; i++) {
		b[i][i  ] = i + 1.0;
		b[i][i+1] = i + 2.0;
	}
	std::cout << b << std::endl;

	c = a * b;

	// std::cout << setw(4);
	// std::cout.width(4);
	std::cout << c << std::endl;

}

// ----------------------------------------------------------------
void test_matrix_times_vector()
{
	int M = 3;
	int N = 5;
	int i;

	tmatrix<double> a(M, N);
	tvector<double> v(N);
	tvector<double> w(M);

	a = 0.0;
	v = 0.0;

	for (i = 0; i < M; i++) {
		a[i][i  ] = i + 1.0;
		a[i][i+1] = i + 2.0;
	}
	std::cout << a << std::endl;

	for (i = 0; i < N; i++) {
		v[i] = i + 3.0;
	}
	std::cout << v << std::endl;

	w = a * v;

	std::cout << w << std::endl;

}

// ----------------------------------------------------------------
void test_vector_plus_vector()
{
	int N = 5;
	int i;

	tvector<double> u(N);
	tvector<double> v(N);
	tvector<double> w(N);

	for (i = 0; i < N; i++) {
		u[i] = i + 1.0;
		v[i] = i * 2.0;
	}
	std::cout << u << std::endl;
	std::cout << v << std::endl;
	w = u + v;
	std::cout << w << std::endl;

}

// ----------------------------------------------------------------
void test_matrix_plus_matrix()
{
	int M = 4;
	int N = 5;
	int i, j;

	tmatrix<double> a(M, N);
	tmatrix<double> b(M, N);
	tmatrix<double> c(M, N);

	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			a[i][j] = i + j;
			b[i][j] = i * j;
		}
	}
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	c = a + b;
	std::cout << c << std::endl;
}


// ----------------------------------------------------------------
int main()
{
	// test_tvector();
	// test_tmatrix();
	// test_vector_times_scalar();
	// test_matrix_times_matrix();
	// test_matrix_times_vector();
	// test_vector_plus_vector();
	test_matrix_plus_matrix();

	return 0;
}
