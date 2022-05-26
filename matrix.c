#include "macros.h"
#include "terms.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void* init_matrix(int n, int m, double *x) {
  matrix *M = (matrix*)malloc(sizeof(matrix));
  if (M == NULL)
    return NULL;

  M->a = (double **)malloc(n * sizeof(double *));
  if (!M->a) {
    free(M);
    return NULL;
  }

  M->n = n;
  M->m = m;
  for (int i = 0, ind = 0; i < n ; ++i) {
    M->a[i] = (double *)malloc(m * sizeof(double));
    if (!M->a[i]) {
      free(M->a);
      free(M);
      return NULL;
    }

    if (x == NULL) {
      for (int j = 0; j < m ; ++j)
        M->a[i][j] = 0;
    } else {
      for (int j = 0; j < m ; ++j)
        M->a[i][j] = x[ind++];
    }
  }

  return M;
}

void free_matrix(matrix *M) {
  for (int i = 0; i < M->n ; ++i)
    free(M->a[i]);
  free(M->a);
  free(M);
}

void print_matrix(matrix *M) {
  if (M == NULL) {
    printf("No matrix found with the given name\n");
    return;
  }

  for (int i = 0; i < M->n ; ++i) {
    for (int j = 0; j < M->m ; ++j)
      printf("%lf ", M->a[i][j]);
    printf("\n");
  }
}

int add_matrix(matrix *A, matrix *B, matrix *C, int sgn) {
  if (A->n != B->n || A->m != B->m) {
    printf("Incompatible sizes\n");
    return 0;
  }

  for (int i = 0; i < A->n ; ++i) {
     for (int j = 0; j < B->m ; ++j)
       C->a[i][j] = A->a[i][j] + sgn * B->a[i][j]; 
  }

  return 1;
}

int mul_matrix(matrix *A, matrix *B, matrix *C) {
  if (A->m != B->n) {
    printf("Incompatible sizes\n");
    return 0;
  }

  for (int i = 0; i < A->n ; ++i) {
    for (int k = 0; k < B->m ; ++k) { 
       double aux = 0;
       for (int j = 0; j < A->m ; ++j)
         aux += A->a[i][j] * B->a[j][k];
       C->a[i][k] = aux;
    }
  }

  return 1;
}
