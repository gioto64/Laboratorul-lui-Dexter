#include "expr.h"
#include "macros.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_expr(char *s) {
  // parses an expression
  // should report only if memory errors occur
  // the convention is: return 1 - ok, return 0 - bad
  static const char *ip = "init_poly";
  static const char *im = "init_matrix";
  static char name[BUFF_SIZE];
  
  if (strcmp(s, ip) == 0) {
    printf("Insert the name of the polynom: ");
    printf("Insert the grade of the polynom: ");
    int n;
    scanf("%d", &n);
    
    printf("Insert %d coefficients: ", n);
    double *x = (double *)malloc(n * sizeof(double)); 
    if (x == NULL)
      return 0;

    for (int i = 0; i <= n ; ++i)
      scanf("%lf", &x[i]);

    init_poly(n, x);
  } else if (strcmp(s, im) == 0) {
    printf("Insert the name of the polynom: ");
    printf("Insert the grade of the polynom: ");
    int n;
    scanf("%d", &n);
    
    printf("Insert %d coefficients: ", n);
    double *x = (double *)malloc(n * sizeof(double)); 
    if (x == NULL)
      return 0;

    for (int i = 0; i <= n ; ++i)
      scanf("%lf", &x[i]);

    init_poly(n, x);

  
  }


  return 1; 
}
