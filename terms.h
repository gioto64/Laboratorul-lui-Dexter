#ifndef DEXTER_TERMS_H
#define DEXTER_TERMS_H

typedef struct matrix {
  int n, m;
  int **a;
} matrix;

typedef struct poly {
  int n;
  int *a;
} poly;

typedef struct term {
  char type; // M for matrix and P for polynom
  char *name;
  void *data;
} term;

#endif // DEXTER_EXPR_H

