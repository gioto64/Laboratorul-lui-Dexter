#include "expr.h"
#include "macros.h"
#include "terms.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void parse_aritm(char *s, term_vector *var) {
  static char delim[] = "*+-/ ";
  char *name1 = strtok(s, delim);
  char *name2 = strtok(NULL, delim); 

  if (name2 == NULL && name1 == NULL)
    return;

  if (name2 == NULL) {
    term aux = find_name(name1, var);
    if (aux.type == 'M') {
      print_matrix(aux.data);
    }
    else if (aux.type == 'P') {
      print_poly(aux.data);
    } else {
      printf("No term found with the given name\n");
    }

    return;
  }
}

int parse_expr(char *s, term_vector *var) {
  // parses an expression
  // should report only if memory errors occur
  // the convention is: return 1 - ok, return 0 - bad
  
  static const char *ip = "init_poly";
  static const char *im = "init_matrix";
  static char name[BUFF_SIZE];
  
  if (strcmp(s, ip) == 0) {
    printf("Insert the name of the polynom: ");
    scanf("%s", name);
    printf("Insert the grade of the polynom: ");
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
    parse_aritm(s, var);
    return 1;
  }

  return 1; 

}
