/*
** close.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Thu Oct 20 02:15:44 2005 thomas moulard
** Last update Sun Oct 23 05:28:34 2005 thomas moulard
*/

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

void		close_lib(char *s, struct s_context *context)
{
  struct s_llib	*elt = NULL;
  struct s_llib	*prev = NULL;
  char		*alias = NULL;

  alias = get_arg(s, 1);
  elt = context->f_lib;
  while (elt && my_strcmp(elt->alias, alias) != 0)
    {
      prev = elt;
      elt = elt->next;
    }
  if (elt && my_strcmp(elt->alias, alias) == 0)
    {
      dlclose(elt->handle);
      if (prev)
	prev->next = elt->next;
      else
	context->f_lib = elt->next;
      free(elt);
    }
  else
    set_error(3, alias, NULL, context);
}
