#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <gsl/gsl_linalg.h>

double pochodna(const int k) {
	if(k % 2 == 0)
		return pow(-1, k/2);
	return 0;
}

double silnia(const int x) {
	if(x <= 1)
		return 1;
	else
		return x * silnia(x - 1);
}

void wypelnij_wektor_c(double * c, const int n) {
	for(int i = 0; i < n; ++i)
		c[i] = pochodna(i) / silnia(i);
}

void wypelnij_macierz(double * Matrix, const double * c, const int N, const int M) {
	int index = 0;

	for(int i  = 0; i < M; ++i) 
		for(int j = 0; j < N; ++j) 
			Matrix[index++] = c[N - M + i + j + 1];
}

void wypelnij_wektor_y(double * y, const double * c, const int N, const int M) {
	for(int i = 0; i < M; ++i)
		y[i] = -c[N + 1 + i];
}

void wypelnij_wektor_b(double * b, const double * w, const int M) {
	b[0] = 1;

	for(int i = 0; i < M; ++i)
		b[M - i] = w[i];
}

void wypelnij_wektor_a(double * a, const double * b, const double * c, const int N) {
	for(int i = 0; i <= N; ++i) {
		a[i] = 0;

		for(int j = 0; j <= i; ++j)
			a[i] += c[i - j] * b[j];
	}
}

double wartosc_p(const double x, const double * a, const int N) {
	double value = 0;

	for(int i = 0; i <= N; ++i)
		value += a[i] * pow(x, i);

	return value;
}

double wartosc_q(const double x, const double * b, const int M) {
	double value = 0;

	for(int i = 0; i <= M; ++i)
		value += b[i] * pow(x, i);

	return value;
}

void rozwiaz(double * Matrix, double * y, double * output, const int M) {
	gsl_matrix_view m = gsl_matrix_view_array (Matrix, M, M);
	gsl_vector_view b = gsl_vector_view_array (y, M);
	gsl_vector * w = gsl_vector_alloc (M);
	int s;
	gsl_permutation * p = gsl_permutation_alloc (M);
	

	gsl_linalg_LU_decomp (&m.matrix, p, &s); 

	gsl_linalg_LU_solve (&m.matrix, p, &b.vector, w);


	for(int i=0;i<M; ++i)
		output[i] = gsl_vector_get(w, i);


	gsl_permutation_free (p);
	gsl_vector_free (w);
}

void aproksymacjaPadego(std::string fileName, double (*fun)(double), const int N, const int M) {
	const int n = N + M + 1;

	double * c = new double [n];
	double * A = new double [M * M];
	double * y = new double [M];
	double * b = new double [M + 1];
	double * a = new double [N + 1];
	double * w = new double [M];


	wypelnij_wektor_c(c, n);
	wypelnij_macierz(A, c, N, M);
	wypelnij_wektor_y(y, c, N, M);

	rozwiaz(A, y, w, M);

	wypelnij_wektor_b(b, w, M);
	wypelnij_wektor_a(a, b, c, N);

  std::fstream file;
  file.open(fileName);

	for(double x = -5.0; x <= 5.0; x += 0.01) {
		double approx = wartosc_p(x, a, N) / wartosc_q(x, b, M);
    file << x << "\t" << fun(x) << "\t" << approx << std::endl;
	}

	file.close();

	delete [] c;
	delete [] A;
	delete [] y;
	delete [] b;
	delete [] a;
	delete [] w;
}

int main()
{
	aproksymacjaPadego("Zad1.txt", cos, 2, 2);
	aproksymacjaPadego("Zad2.txt", cos, 4, 4);
	aproksymacjaPadego("Zad3.txt", cos, 6, 6);

	return 0;
}