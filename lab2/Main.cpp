#include <iostream>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <math.h>
#include <fstream>
using std::cout;
using std::endl;
#define N 4


int main() {
    //inicjalizacja macierzy A
    gsl_matrix *A = gsl_matrix_calloc(N, N);

    for (int i = 0; i < N; i++) 
        for (int j = 0; j < N; j++) 
            gsl_matrix_set(A, i, j, 1.0 / (i + j + 2));

    cout << "Macierz A:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) 
            cout << gsl_matrix_get(A, i, j) << "\t";
        cout << endl;
    }
    cout << endl << endl;

    //wektor permutacji wierszy
    gsl_permutation *p = gsl_permutation_calloc(N);

    //rozklad LU
    int signum;
    gsl_linalg_LU_decomp(A, p, &signum);
    cout << "Macierz LU:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) 
            cout << gsl_matrix_get(A, i, j) << "\t";
        cout << endl;
    }
    cout << endl << endl;
    
    //licze wyznacznik i zapisuje elementy z przekatnej macierzy U
    double wyznacznik = 1;
    std::ofstream file;
    file.open("out.dat");

    file << "Elementy na diagonali macierzy U: ";
    for (int i = 0; i < N; i++) {
        wyznacznik *= gsl_matrix_get(A, i, i);
        file << gsl_matrix_get(A, i, i) << "\t";
    }
    file << endl << endl;
    file << "Wyznacznik macierzy A: " << wyznacznik << endl;


    //macierz odwrotna
    gsl_matrix *A_inv = gsl_matrix_calloc(N, N);
    gsl_vector *b = gsl_vector_calloc(N);
    gsl_vector *x = gsl_vector_calloc(N);

    for (int i = 0; i < N; i++){
        gsl_vector_set_zero(b);
        gsl_vector_set(b, i, 1.0);
        gsl_linalg_LU_solve(A, p, b, x);

        for (int j = 0; j < N; j++) {
            double vec = gsl_vector_get(x, j);
			gsl_matrix_set(A_inv, j, i, vec);
        }
    }

    cout << "Macierz A^-1:" << endl;
    file << endl << "Macierz A^-1:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << gsl_matrix_get(A_inv, i, j) << "\t";
            file << gsl_matrix_get(A_inv, i, j) << "\t";
        }
        cout << endl;
        file << endl;
    }
    cout << endl << endl;
    file << endl;

    //przywrocenie A do "ustawien fabrycznych" :)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            gsl_matrix_set(A, i, j, 1.0 / (i + j + 2));
        }
    }

    //iloczyn A * A^-1
    gsl_matrix *iloczyn = gsl_matrix_calloc(N, N);
    double suma = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            suma = 0;
            for (int k = 0; k < N; k++) {
                suma += gsl_matrix_get(A, i, k) * gsl_matrix_get(A_inv, k, j);
                gsl_matrix_set(iloczyn, i, j, suma);
            }
        }
    }

    cout << "Macierz A * A^-1:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << gsl_matrix_get(iloczyn, i, j) << "\t";
        }
        cout << endl;
    }
    cout << endl << endl;

    //wskaznik uwarunkowania macierzy A
    double max_A = abs(gsl_matrix_get(A, 0, 0)),
         max_A_inv = abs(gsl_matrix_get(A_inv, 0, 0));
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(max_A < abs(gsl_matrix_get(A, i, j)))
                max_A = abs(gsl_matrix_get(A, i, j));

    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(max_A_inv < abs(gsl_matrix_get(A_inv, i, j)))
                max_A_inv = abs(gsl_matrix_get(A_inv, i, j));
    
    double wskaznik_uwar_A =  max_A * max_A_inv;
    cout << "Max A: " << max_A << endl << "Max A^-1: " << max_A_inv << endl;
    cout << "Wskaznik uwarunkowania macierzy A wynosi: " << wskaznik_uwar_A << endl << endl;
    file << "Wskaznik uwarunkowania macierzy A wynosi: " << wskaznik_uwar_A << endl;

    //zwalnianie pamieci
    file.close();
    gsl_matrix_free(A);
	gsl_matrix_free(A_inv);
	gsl_matrix_free(iloczyn);
	gsl_permutation_free(p);
	gsl_vector_free(b);
	gsl_vector_free(x);
}
