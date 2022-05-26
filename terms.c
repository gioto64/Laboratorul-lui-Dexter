#include "terms.h"
#include "macros.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int push(term_vector *var, char *name, char type, void *data) {
  if (data == NULL)
    return 0;

  if (var->sz == var->cap) {
    var->cap *= 2;
    term *aux = realloc(var->vec, var->cap * sizeof(term));
    if (aux == NULL)
      return 0;
    var->vec = aux;
  }

  var->vec[var->sz].type = type; 
  var->vec[var->sz].data = data; 
  var->vec[var->sz].name = (char *)malloc((strlen(name) + 1) * sizeof(char)); 
  if (var->vec[var->sz].name == NULL)
    return 0;;

  strcpy(var->vec[var->sz].name, name);
  var->sz++;
  return 1;
}

void free_terms(term_vector var) {
  for (int i = 0; i < var.sz ; ++i) {
    free(var.vec[i].name);
    if (var.vec[i].type == 'M')
      free_matrix(var.vec[i].data);
    else
      free_poly(var.vec[i].data);
  }
}

term find_name(char *name, term_vector *var) {
  for (int i = 0; i < var->sz ; ++i)
    if (strcmp(name, var->vec[i].name) == 0)
      return var->vec[i];

  term aux;
  aux.type = 'N';
  return aux; 
}
