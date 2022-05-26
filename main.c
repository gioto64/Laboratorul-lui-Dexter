#include "terms.h"
#include "macros.h"
#include "expr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int check_alloc(void *p) {
  if (p == NULL) {
    printf("Bad alloc\n");
    return 0;
  }
  return 1;
}

char* strip_blank(char *s) {
  int l = strlen(s);
  char *new = (char *)malloc((l + 1) * sizeof(char));
  if (new == NULL) {
    free(s);
    return NULL; 
  }

  int j = 0;
  for (int i = 0; i < l ; ++i) {
    if (!isspace(s[i]))
      new[j++] = s[i]; 
  }
  new[j++] = 0;

  return new;
}

int main() {
  printf(KGRN "Dexter's Laboratory, version 1.0.0\n");

  char *buff = (char *)malloc(BUFF_SIZE * sizeof(char));
  if (!check_alloc(buff))
    exit(1);

  term_vector var;
  var.sz = 0;
  var.cap = 1;
  var.vec = (term *)malloc(sizeof(term));
  if (!check_alloc(var.vec)) {
    free(buff);
    exit(1);
  }

  while (1) {
    printf("dexter:>");
    fgets(buff, BUFF_SIZE, stdin);
    if (buff[0] == '\n')
      fgets(buff, BUFF_SIZE, stdin);

    char *buff_clean = strip_blank(buff);
    if (buff_clean == NULL)
      continue;

    if (strcmp(buff_clean, "exit") == 0) {
      // exit the program
      free(buff);
      free(buff_clean);
      free_terms(var);
      return 0;
    }

    // parse an expression
    int ok = parse_expr(buff_clean, &var);
    // only memory errors should be catched by ok
    if (!ok) {
      free(buff);
      free(buff_clean);
      free_terms(var);
      exit(1);
    }

    free(buff_clean);
  }

  return 0;
}
