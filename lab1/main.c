#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gaussj.c"

#define N 400 // rozmiar macierzy A: NxN

int main(void) {
	float **A,**b;
//	Alokacja macierzy
	A = matrix(1, N, 1, N);
	b = matrix(1, N, 1, 1);
	
// 	Wypelnienie macierzy A i wektora b
	for(int i=1; i<=N; ++i){
		b[i][1] = 0.0;
		for(int j=1; j<=N; ++j)
			A[i][j] = 0.0;
	}

    for (int i=1; i <=N; ++i) {
        for (int j=1; j<=N; ++j) {
            if (i == j && i + 2 <= N) {
                A[i][j] = 1;
                A[i+1][j] = 0.1*0.1 - 2;
                A[i+2][j] = 1;
            }
        }
    }

    A[2][1] = -1;
    A[N][N] = 1;
    A[N-1][N-1] = 1;
    A[N][N-1] = 0.1*0.1 - 2;

    b[1][1] = 1;


//	Rozwiazanie ukladu rownan Ax=b - wywolanie procedury:
	gaussj(A,N,b,1);

//	Wypisanie rozwiazania, ktore procedura gaussj(A,N,b,1); zapisala w wektorze b.
	for(int i=1; i<=N; ++i)
		printf("%f %g\n", i*0.1, b[i][1]); 
    
//	Zwolnienie pamieci
	free_matrix(A,1,N,1,N);
	free_matrix(b,1,N,1,1);    
	
	return 0;
}
