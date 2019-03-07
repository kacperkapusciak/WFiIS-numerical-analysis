//# include "/opt/NR/numerical_recipes.c/nrutil.h"
//# include "/opt/NR/numerical_recipes.c/nrutil.c"
//# include "/opt/NR/numerical_recipes.c/ludcmp.c"
#include "deps.h"
#define N 5

void wyzeruj_macierz(float ***A){
  for(int i=1; i<=N; i++)
    for (int j=1; j<=N; j++)
      (*A)[i][j] = 0;
}

void wyzeruj_wektor(int **v){
  for (int i = 1; i <= N; i++) 
    (*v)[i] = 0;
}

void wypisz_macierz(float **A){
  for (int i = 1; i <= N; i++) {
    for (int j = 1; j <= N; j++)
      printf("\t%3.4g\t", A[i][j]);
    cout << endl;
  }
  cout << endl;
}

void inicjalizuj_macierz_A(float ***A) {
  wyzeruj_macierz(A);
  float b = 2.0;
  float h = 2 * b / (N - 1);

  for (int i = 2; i < N; i++){
      (*A)[i][i] = -2.0 / (h * h);
      (*A)[i+1][i] = (*A)[i][i+1] = 1.0 / (h * h);
  }
  //warunki brzegowe
  (*A)[1][1] = (*A)[N][N] = 1;
  (*A)[2][1] = (*A)[1][2] = (*A)[N-1][N] = (*A)[N][N-1] = 0;  
}

void stworz_LU(float ***L, float ***U, float **A) {
  wyzeruj_macierz(L); wyzeruj_macierz(U);
  (*U)[1][1] = A[1][1];
  for (int i = 2; i < N; i++) {
    (*L)[i][i] = 1; //diagonala L
    (*U)[i][i+1] = A[i][i+1]; // c
    (*L)[i+1][i] = A[i+1][i] / (*U)[i-1][i];//l
    (*U)[i][i] = A[i][i] - (*L)[i+1][i] * A[i-1][i]; //diagonala U
  }
  (*U)[N][N] = A[N][N];
  (*L)[N][N] = 1;
  (*U)[N][N-1] = A[N][N-1];
}

int main() {
  float **A = matrix(1, N, 1, N);
  inicjalizuj_macierz_A(&A);
  cout << "Macierz A:" << endl;
  wypisz_macierz(A);

  int *vec = ivector(1, N);
  float d;
  ludcmp(A, N, vec, &d);

  float **L = matrix(1, N, 1, N);
  float **U = matrix(1, N, 1, N);
  stworz_LU(&L, &U, A);
  cout << "L:" << endl;
  wypisz_macierz(L);

  cout << "U:" << endl;
  wypisz_macierz(U);
  return 0;
}

// #include "Main.h"

// int main()
// {
//     A = matrix(1, N, 1, N);
//     inicjalizuj_0(&A);
//     d_inicjalizuj_wektor(&invector);
//     inicjalizuj_spec(&A);
//     ludcmp(A, N, invector, &d);
//     inicjalizuj_L_U(&L, &U, A);
//     b_vector = vector(1, N);
//     y_vector = vector(1, N);
//     inicjalizuj_wektor_wyrazow_wolnych(&b_vector);
//     inicjalizuj_y_wektor(&y_vector, b_vector, L);
//     v_vector = vector(1, N);
//     inicjalizuj_v_vector(&v_vector, y_vector, U);
//     tr_vector = vector(1, N);
//     inicjalizuj_wektor_wartosci_rzeczywistych(&tr_vector);
//     file_ptr_NR = fopen("out_NR.dat", "w");
//     file_ptr_TR = fopen("out_TR.dat", "w");
//     if (!file_ptr_NR || !(file_ptr_TR))
//     {
//         printf("ERR while opening file! LEAVING!!!\n");
//         return -1;
//     }
//     for (int i = 1; i <= N; i++)
//     {
//         fprintf(file_ptr_NR, "%3f\n", v_vector[i]);
//         fprintf(file_ptr_TR, "%3f\n", tr_vector[i]);
//     }
//     free_matrix(A, 1, N, 1, N);
//     free_matrix(L, 1, N, 1, N);
//     free_matrix(U, 1, N, 1, N);
//     free_ivector(invector, 1, N);
//     free_vector(b_vector, 1, N);
//     free_vector(y_vector, 1, N);
//     free_vector(v_vector, 1, N);
//     free_vector(tr_vector, 1, N);
//     fclose(file_ptr_NR);
//     fclose(file_ptr_TR);
//     return 0;
// }
// void inicjalizuj_macierz(float ***A)
// {
//     for (int i = 1; i <= N; i++)
//     {
//         for (int j = 1; j <= N; j++)
//         {
//             (*A)[i][j] = (float)(1.0) / (i + j);
//         }
//     }
// }
// void inicjalizuj_wektor_wyrazow_wolnych(float **b_vector)
// {
//     (*b_vector)[1] = 0;
//     (*b_vector)[N] = 0;
//     float x;
//     for (int i = 2; i <= N - 1; i++)
//     {
//         x = -(float)b + (h * (float)(i - 1));
//         if ((x > -b && x < -a) || x == 0 || (x > a && x < b))
//             (*b_vector)[i] = 0;
//         else if (x > -a && x < 0)
//             (*b_vector)[i] = 1;
//         else if (x > 0 && x < a)
//             (*b_vector)[i] = -1;
//     }
// }
// void inicjalizuj_y_wektor(float **y_vector, float *b_vector, float **L)
// {
//     (*y_vector)[1] = b_vector[1];
//     for (int i = 2; i <= N; i++)
//         (*y_vector)[i] = (b_vector[i] - (L[i][i - 1] * (*y_vector)[i - 1]));
// }

// void inicjalizuj_0(float ***A)
// {
//     for (int i = 1; i <= N; i++)
//     {
//         for (int j = 1; j <= N; j++)
//             (*A)[i][j] = 0;
//     }
// }

// void d_inicjalizuj_wektor(int **A)
// {
//     *A = ivector(1, N);
//     for (int i = 1; i <= N; i++)
//         (*A)[i] = 0;
// }
// void inicjalizuj_spec(float ***A)
// {
//     (*A)[1][1] = 1;
//     (*A)[1][2] = 0;
//     (*A)[2][1] = 0;
//     for (int i = 2; i <= N - 1; i++)
//     {
//         (*A)[i][i] = (float)(-2.0) / (h * h);
//         (*A)[i][i - 1] = (1.0) / (h * h);
//         (*A)[i][i + 1] = (1.0) / (h * h);
//     }

//     (*A)[N][N] = 1;
//     (*A)[N][N - 1] = 0;
//     (*A)[1][1] = 1;
// }
// void wypisz(float **arr)
// {
//     printf("\n");
//     printf("\n");
//     for (int i = 1; i <= N; i++)
//     {
//         for (int j = 1; j <= N; j++)
//             printf("%   3f   ", arr[i][j]);
//         printf("\n");
//     }
//     printf("\n");
//     printf("\n");
// }
// void inicjalizuj_L_U(float ***L, float ***U, float **A)
// {
//     *L = matrix(1, N, 1, N);
//     *U = matrix(1, N, 1, N);
//     inicjalizuj_0(L);
//     inicjalizuj_0(U);
//     for (int i = 1; i <= N; i++)
//         (*L)[i][i] = 1;
//     for (int i = 2; i <= N - 1; i++)
//         (*U)[i][i + 1] = (1.0) / (h * h); // inicjalizacja wspolczynnikow Cn macierzy U
//     (*U)[1][2] = 0;
//     (*U)[1][1] = 1;
//     for (int i = 2; i <= N - 1; i++)
//     {
//         (*L)[i][i - 1] = ((1.0) / (h * h)) / (*U)[i - 1][i - 1];
//         (*U)[i][i] = ((-2.0) / (h * h)) - (((*L)[i][i - 1]) * (*U)[i][i + 1]);
//     }
//     (*L)[N][N - 1] = ((1.0) / (h * h)) / (*U)[N - 1][N - 1];
//     (*U)[N][N] = ((-2.0) / (h * h)) - (((*L)[N][N - 1]) * (*U)[N - 1][N]);
// }
// void inicjalizuj_v_vector(float **v_vector, float *y_vector, float **U)
// {
//     (*v_vector)[N] = y_vector[N] / U[N][N];
//     for (int i = N - 1; i >= 1; i--)
//     {
//         (*v_vector)[i] = (y_vector[i] - (U[i][i + 1] * (*v_vector)[i + 1])) / U[i][i];
//     }
// }
// void inicjalizuj_wektor_wartosci_rzeczywistych(float **tr_vector)
// {
//     float x;
//     for (int i = 1; i <= N; i++)
//     {
//         x = -(float)b + (h * (float)(i - 1));
//         if (x > -b && x < -a)
//             (*tr_vector)[i] = (float)(-(x / 16.0) - 1.0 / 8.0); // + + // zaznaczone obok znaki, tak bylo w pdf,
//                                                                 //jednak wowczas wykresy nie pokrywaly sie, byly semtryczne,
//                                                                 //odwrocenie jednego sprawilo ze pasuja do siebie
//         else if (x > -a && x < 0)
//             (*tr_vector)[i] = (float)(+((x * x) / 2.0) + ((7.0 / 16.0) * x)); // - -
//         else if (x > 0 && x < a)
//             (*tr_vector)[i] = (float)(-((x * x) / 2.0) + ((7.0 / 16.0) * x)); //+ -
//         else if (x > a && x < b)
//             (*tr_vector)[i] = (float)(-(x / 16.0) + 1.0 / 8.0); //+ -
//         else
//         {
//             (*tr_vector)[i] = 0;
//         }
//     }
// }
