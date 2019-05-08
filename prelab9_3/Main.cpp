#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
#include <fstream>

#include "../dependencies/deps.h"

float fun1(const float x, const float x0, const float sigma) {
	return expf(-(pow(x - x0, 2)) / (2 * pow(sigma, 2)));
}

float fun2(const float x, const float x0, const float sigma) {
	const float alpha = 0.1;

	float Gx = expf(-(pow(x - x0, 2)) / (2 * pow(sigma, 2)));
	float delta = alpha * (rand()/(RAND_MAX + 1.0) - 0.5);

	return Gx * (1 + delta);
}

void inicjalizuj_wezly(float * wezly, const float N, const float xMin, const float xMax){
	float dx = (fabs(xMin) + fabs(xMax)) / (N - 1);

	for(int i = 1; i <= N; i++)
		wezly[i] = xMin + dx * (i - 1);
}

void inicjalizuj_wartosci(float * wartosci, const float * wezly, float (*fun)(float, float, float),
				const int N, const float x0, const float sigma) {
	for(int i = 1; i <= N; i++)
		wartosci[i] = fun(wezly[i], x0, sigma);
}

void inic_r(float ** r, const float * wezly, const float * wartosci, const int N, const int m)
{
	for(int k = 1; k <= m; ++k) {
		float sum = 0;

		for(int j = 1; j <= N; j++)
			sum += log(wartosci[j]) * pow(wezly[j], k - 1);
	
		r[k][1] = sum;
	}
}
void inic_G(float ** G, const float * wezly, const int N, const int m)
{
	for(int i = 1; i <= m; i++) {
		for(int k = 1; k <= m; k++) {
			float sum = 0;

			for(int j = 1; j <= N; j++)
				sum += pow(wezly[j], i + k - 2);

			G[i][k] = sum;
		}
  }
}

void inic_a(float * a, const float x0, const float sigma, const float m)
{
	a[1] = -pow(x0, 2) / 2 / pow(sigma, 2);
	a[2] = x0 / pow(sigma, 2);
	a[3] = -1.0 / 2.0 / pow(sigma, 2);

	for(int i = 4; i <= m; i++)
		a[i] = 0.0;
}

void aproksymacja(float (*fun)(float, float, float), const char * fileName, const float x0,
			const float sigma, const int N, const int m) {
	float xMin = -3.0 * sigma + x0;
	float xMax = 3.0 * sigma + x0;

	float * wezly = vector(1, N);
	float * wartosci = vector(1, N);

	float ** r = matrix(1, m, 1, 1);
	float ** G = matrix(1, m, 1, m);

	float * a = vector(1, m);

	inicjalizuj_wezly(wezly, N, xMin, xMax);
	inicjalizuj_wartosci(wartosci, wezly, fun, N, x0, sigma);
	inic_r(r, wezly, wartosci, N, m);
	inic_G(G, wezly, N, m);
	inic_a(a, x0, sigma, m);


	gaussj(G, m, r, 1);


  std::fstream file;
  file.open(fileName);

	for(float x = xMin; x <= xMax; x += 0.01)
    file << x << "\t" << fun(x, x0, sigma) << "\t" << expf(r[1][1] + x * r[2][1] + pow(x, 2) * r[3][1] + pow(x, 3) * r[4][1]) << std::endl;
	

	std::string plikZWezlami = "Nodes";
	plikZWezlami += fileName;
	std::fstream fileWezly;
  fileWezly.open(plikZWezlami);

	for(int i = 1; i <= N; i++)
    fileWezly << wezly[i] << "\t" << wartosci[i] << std::endl;
	

	file.close();
	fileWezly.close();

	free_vector(wezly, 1, N);
	free_vector(wartosci, 1, N);
	free_matrix(r, 1, m, 1, 1);
	free_matrix(G, 1, m, 1, m);
	free_vector(a, 1, m);
}

int main() {
  aproksymacja(fun1, "Zad1_N11.txt", 2.0, 4.0, 11, 4);
	aproksymacja(fun1, "Zad1_N21.txt", 2.0, 4.0, 21, 4);
	aproksymacja(fun1, "Zad1_N101.txt", 2.0, 4.0, 101, 4);

	aproksymacja(fun2, "Zad2_N11.txt", 2.0, 4.0, 11, 4);
	aproksymacja(fun2, "Zad2_N21.txt", 2.0, 4.0, 21, 4);
	aproksymacja(fun2, "Zad2_N51.txt", 2.0, 4.0, 51, 4);
	aproksymacja(fun2, "Zad2_N101.txt", 2.0, 4.0, 101, 4);
  return 0;
}