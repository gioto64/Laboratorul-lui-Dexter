#ifndef DEXTER_TERMS_H
#define DEXTER_TERMS_H

typedef struct matrix {
  int n, m;
  double **a;
} matrix;

typedef struct poly {
  int n;
  double *a;
} poly;

typedef struct term {
  char type; // M for matrix and P for polynomial
  char *name;
  void *data;
} term;

typedef struct term_vector {
  int sz, cap;
  term *vec;
} term_vector;

// matrix functions
void* init_matrix(int n, int m, double *v);
void free_matrix(matrix *M);
void print_matrix(matrix *M);
int add_matrix(matrix *A, matrix *B, matrix *C, int sgn);
int mul_matrix(matrix *A, matrix *B, matrix *C);

// polynomial functions
void* init_poly(int n, double *v); 
void free_poly(poly *P);
void print_poly(poly *P);
int add_poly(poly *A, poly *B, poly *C, int sgn);
int mul_poly(poly *A, poly *B, poly *C);

// vector functions
void free_terms(term_vector var);
int push(term_vector *var, char *name, char type, void *data);
term find_name(char *name, term_vector *var);

#endif // DEXTER_EXPR_H

