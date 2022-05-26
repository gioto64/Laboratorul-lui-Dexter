#include "macros.h"
#include "terms.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void* init_poly(int n, double *x) {
  poly *P = (poly*)malloc(sizeof(poly));
  if (P == NULL)
    return NULL;

  P->a = malloc((n + 1) * sizeof(double));
  if (P->a == NULL) {
    free(P);
    return NULL;
  }

  P->n = n;
  for (int i = 0; i <= n ; ++i) {
    if (!x)
      P->a[i] = 0;
    else
      P->a[i] = x[i];
  }

  return P;
}

void free_poly(poly *P) {
  free(P->a);
  free(P);
}

void print_poly(poly *P) {
  if (P == NULL) {
    printf("No polynomial found with the given name\n");
    return;
  }

  for (int i = 0; i <= P->n ; ++i) {
    printf("%lf", P->a[i]);
    if (i > 0)
      printf("*x^%d", i);
    if (i < P->n)
      printf(" + ");
  }
  printf("\n");
}

int add_poly(poly *A, poly *B, poly *C, int sgn) {
  for (int i = 0; i <= C->n ; ++i)
    C->a[i] = 0;
  for (int i = 0; i <= A->n ; ++i)
    C->a[i] += A->a[i];
  for (int i = 0; i <= B->n ; ++i)
    C->a[i] += sgn * B->a[i];

  return 1;
}

int mul_poly(poly *A, poly *B, poly *C) {
  for (int i = 0; i < C->n ; ++i)
    C->a[i] = 0;
  for (int i = 0; i <= A->n ; ++i)
    for (int j = 0; j <= B->n ; ++j)
      C->a[i + j] += A->a[i] * B->a[j];

  return 1;
}
