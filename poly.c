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

  for (int i = 0; i <= n ; ++i)
    P->a[i] = x[i];

  return P;
}

void free_poly(poly *P) {
  free(P->a);
  free(P);
}

void print_poly(poly *P) {
  if (P == NULL) {
    printf("No polygon found with the given name\n");
    return;
  }

  for (int i = 0; i <= P->n ; ++i)
    printf("%lf ", P->a[i]);
  printf("\n");
}

