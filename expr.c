#include "expr.h"
#include "macros.h"
#include "terms.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(int a, int b) {
  if (a > b)
    return a;
  return b;
}

int parse_aritm(char *s, term_vector *var) {
  static char delim[] = "*+- ";
  char ch = -1;
  int len = strlen(s);
  for (int i = 0; i < len ; ++i) {
    if (strchr(delim, s[i])) {
      if (ch == -1) {
        ch = *strchr(delim, s[i]);
        continue;
      }

      printf("Invalid expression\n");
      return 1;
    }
  }

  char *name1 = strtok(s, delim);
  char *name2 = strtok(NULL, delim); 

  if (name2 == NULL && name1 == NULL)
    return 1;

  if (name2 == NULL) {
    // if there's only one term, output it
    term aux = find_name(name1, var);
    if (aux.type == 'M') {
      print_matrix(aux.data);
    }
    else if (aux.type == 'P') {
      print_poly(aux.data);
    } else {
      printf("No term found with the given name\n");
    }

    return 1;
  } else {
    term lft = find_name(name1, var); 
    if (lft.type == 'N') {
      printf("No term found with the given name\n");
      return 1;
    }

    term rgt = find_name(name2, var); 
    if (rgt.type == 'N') {
      printf("No term found with the given name\n");
      return 1;
    }

    if (lft.type != rgt.type) {
      printf("The terms have incompatible types\n");
      return 1;
    }

    if (lft.type == 'M') {
      if (ch == '+') {
        matrix *aux = init_matrix(((matrix *)lft.data)->n, ((matrix *)lft.data)->m, NULL);
        if (aux == NULL)
          return 0;

        int ok = add_matrix(lft.data, rgt.data, aux, 1);
        if (ok)
          print_matrix(aux);

        free_matrix(aux);
      } else if (ch == '*'){
        matrix *aux = init_matrix(((matrix *)lft.data)->n, ((matrix *)rgt.data)->m, NULL);
        if (aux == NULL)
          return 0;

        int ok = mul_matrix(lft.data, rgt.data, aux);
        if (ok)
          print_matrix(aux);

        free_matrix(aux);
      } else if (ch == '-'){
        matrix *aux = init_matrix(((matrix *)lft.data)->n, ((matrix *)lft.data)->m, NULL);
        if (aux == NULL)
          return 0;

        int ok = add_matrix(lft.data, rgt.data, aux, -1);
        if (ok)
          print_matrix(aux);

        free_matrix(aux);
      }
      else {
        printf("Invalid expression\n");
      }
    } else {
      if (ch == '+') {
        poly *aux = init_poly(max(((poly *)lft.data)->n, ((poly *)rgt.data)->n), NULL);
        if (aux == NULL)
          return 0;

        int ok = add_poly(lft.data, rgt.data, aux, 1);
        if (ok)
          print_poly(aux);

        free_poly(aux);
      } else if (ch == '*'){
        poly *aux = init_poly(((poly *)lft.data)->n + ((poly *)rgt.data)->n, NULL);
        if (aux == NULL)
          return 0;

        int ok = mul_poly(lft.data, rgt.data, aux);
        if (ok)
          print_poly(aux);

        free_poly(aux);
      } else if (ch == '-'){
        poly *aux = init_poly(max(((poly *)lft.data)->n, ((poly *)rgt.data)->n), NULL);
        if (aux == NULL)
          return 0;

        int ok = add_poly(lft.data, rgt.data, aux, -1);
        if (ok)
          print_poly(aux);

        free_poly(aux);
      } else {
        printf("Invalid expression\n");
      }
    }
  }

  return 1;
}

int parse_expr(char *s, term_vector *var) {
  // parses an expression
  // should report only if memory errors occur
  // the convention is: return 1 -> ok, return 0 -> bad
  
  static const char *ip = "init_poly";
  static const char *im = "init_matrix";
  static char name[BUFF_SIZE];
  
  if (strcmp(s, ip) == 0) {
    // insert a polynomial
    printf("Insert the name of the polynomial: ");
    scanf("%s", name);
    printf("Insert the grade of the polynomial: ");
    int n;
    scanf("%d", &n);
    
    printf("Insert %d coefficients: ", n + 1);
    double *x = (double *)malloc((n + 1) * sizeof(double)); 
    if (x == NULL)
      return 0;

    for (int i = 0; i <= n ; ++i)
      scanf("%lf", &x[i]);

    int ok = push(var, name, 'P', init_poly(n, x));
    free(x);
    return ok;
  } else if (strcmp(s, im) == 0) {
    // insert a matrix
    printf("Insert the name of the matrix: ");
    scanf("%s", name);
    printf("Insert the number of lines of the matrix: ");
    int n, m;
    scanf("%d", &n);
    printf("Insert the number of columns of the matrix: ");
    scanf("%d", &m);
    
    printf("Insert the %d entries of the matrix: ", n * m);
    double *x = (double *)malloc(n * m * sizeof(double)); 
    if (x == NULL)
      return 0;

    for (int i = 0; i < n * m ; ++i)
      scanf("%lf", &x[i]);

    int ok = push(var, name, 'M', init_matrix(n, m, x));
    free(x);
    return ok;
  } else {
    return parse_aritm(s, var);
  }

  return 1; 
}
