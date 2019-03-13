#include "gsl/gsl_matrix.h"
#include "gsl/gsl_linalg.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "/home/hubert/Numerical_recipes/gaussj.cpp"
#include "/home/hubert/Numerical_recipes/nrutil.h"
#include "/home/hubert/Numerical_recipes/nrutil.cpp"
#define N 1000
#define m 5

void intialize_matrix(gsl_matrix *A);
void print_matrix(gsl_matrix *A);
void intialize_vector_b(gsl_vector **vector);
void pomnoz(gsl_matrix *A, gsl_vector *vector, gsl_vector **result, int x, int middle, int y);
void highest_drop(gsl_matrix *A, gsl_vector *vector_b);
float mnoz_wektory(gsl_vector *vec_1, gsl_vector *vec_2);
float norma_wektora(gsl_vector *vec_1);
void mnoz_macierz_i_wektor(gsl_matrix *A, gsl_vector *vector, gsl_vector **result);
void intialize_matrix_Gauss(float ***A);
int main(void)
{
    time_t time_HD_start, time_HD_stop;
    time_t time_Gauss_start, time_Gauss_stop;
    double HD_time, Gauss_time;
    gsl_matrix *A = gsl_matrix_calloc(N, N);
    intialize_matrix(A);
    gsl_vector *vector_b = gsl_vector_calloc(N);
    intialize_vector_b(&vector_b);
    time(&time_HD_start);
    highest_drop(A, vector_b);
    time(&time_HD_stop);
    HD_time = difftime(time_HD_stop, time_HD_start);
    ////// freeing memory //////
    gsl_matrix_free(A);
    gsl_vector_free(vector_b);
    ////////////////////////////

    ///// Gauss method ////////

    float **A_Gauss = matrix(1, N, 1, N);
    intialize_matrix_Gauss(&A_Gauss);
    float **vect = matrix(1, N, 1, 1);
    time(&time_Gauss_start);
    gaussj(A_Gauss, N, vect, 1);
    time(&time_Gauss_stop);
    Gauss_time = difftime(time_Gauss_stop, time_Gauss_start);
    std::cout << "Duration of Gauss method: " << Gauss_time << " \nDuration of method of steepest decent: " << HD_time << "\n";
    free_matrix(vect, 1, N, 1, 1);
    free_matrix(A_Gauss, 1, N, 1, N);
}
void intialize_matrix(gsl_matrix *A)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (abs(i - j) <= m)
                gsl_matrix_set(A, i, j, 1.0 / (1.0 + (float)(abs(i - j))));

            else
                gsl_matrix_set(A, i, j, 0);
        }
    }
}
void intialize_matrix_Gauss(float ***A)
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (abs(i - j) <= m)
                (*A)[i][j] = 1.0 / (1.0 + (float)(abs(i - j)));

            else
                (*A)[i][j] = 0;
        }
    }
}
void print_matrix(gsl_matrix *A)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf("%g ", gsl_matrix_get(A, i, j));
        printf("\n");
    }
}
void intialize_vector_b(gsl_vector **vector)
{
    for (int i = 0; i < N; i++)
    {
        gsl_vector_set(*vector, i, i);
    }
}
void highest_drop(gsl_matrix *A, gsl_vector *vector_b)
{
    double alpha;
    int iteration = 0;
    int start_value_of_x_vector = 0;
    gsl_vector *vector_A_x = gsl_vector_calloc(N);
    gsl_vector *vector_r = gsl_vector_calloc(N);
    gsl_vector *vector_A_r = gsl_vector_calloc(N);
    gsl_vector *vector_x = gsl_vector_calloc(N);
    gsl_vector_set(vector_x, 0, start_value_of_x_vector);
    FILE *file_ptr;
    file_ptr = fopen("out.dat", "w");
    if (!file_ptr)
    {
        std::cout << "ERR while opening file! Leaving...\n";
        return;
    }
    fprintf(file_ptr, "nr iteracji --- wartosc normy euklidesowej wektora reszt --- wartosc alpha --- wartosc normy euklidesowej wektora rozwiazan\n\n");

    do
    {
        mnoz_macierz_i_wektor(A, vector_x, &vector_A_x);
        for (int i = 0; i < N; i++)
        {
            gsl_vector_set(vector_r, i, gsl_vector_get(vector_b, i) - gsl_vector_get(vector_A_x, i));
        }
        mnoz_macierz_i_wektor(A, vector_r, &vector_A_r);
        alpha = mnoz_wektory(vector_r, vector_r) / mnoz_wektory(vector_r, vector_A_r);
        iteration++;
        for (int i = 0; i < N; i++)
        {
            gsl_vector_set(vector_x, i, gsl_vector_get(vector_x, i) + alpha * gsl_vector_get(vector_r, i));
        }
        if (iteration == N - 2)
        {
            std::cout << "does not converge!\n";
            break;
        }

        std::cout << "iteracja: " << iteration << "\n";
        fprintf(file_ptr, "%d --- %g --- %f --- %g\n\n", iteration, norma_wektora(vector_r), alpha, norma_wektora(vector_x));
    } while (norma_wektora(vector_r) > pow(10, -6));
    gsl_vector_free(vector_A_x);
    gsl_vector_free(vector_A_r);
    gsl_vector_free(vector_r);
    gsl_vector_free(vector_x);
    fclose(file_ptr);
}
void pomnoz(gsl_matrix *A, gsl_vector *vector, gsl_vector **result, int x, int middle, int y)
{
    float suma;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            suma = 0;
            for (int k = 0; k < middle; k++)
            {
                suma += gsl_matrix_get(A, i, k) * gsl_vector_get(vector, k);
            }
            gsl_vector_set(*result, j, suma);
        }
    }
}
float mnoz_wektory(gsl_vector *vec_1, gsl_vector *vec_2)
{
    float suma = 0;
    for (int i = 0; i < N; i++)
    {
        suma += gsl_vector_get(vec_1, i) * gsl_vector_get(vec_2, i);
    }
    return suma;
}
float norma_wektora(gsl_vector *vec_1)
{
    float suma = 0;
    for (int i = 0; i < N; i++)
    {
        suma += gsl_vector_get(vec_1, i) * gsl_vector_get(vec_1, i);
    }
    return sqrt(suma);
}
void mnoz_macierz_i_wektor(gsl_matrix *A, gsl_vector *vector, gsl_vector **result)
{
    float suma;
    for (int i = 0; i < N; i++)
    {
        suma = 0;
        for (int j = 0; j < N; j++)
        {
            suma += gsl_matrix_get(A, i, j) * gsl_vector_get(vector, j);
        }
        gsl_vector_set(*result, i, suma);
    }
}