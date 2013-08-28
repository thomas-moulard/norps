/*
** open.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Wed Oct 19 19:43:43 2005 thomas moulard
** Last update Sat Oct 22 13:08:02 2005 thomas moulard
*/

#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

void		open_lib(char *str, struct s_context *context)
{
  struct s_llib	*elt = NULL;
  struct s_llib	*prev = NULL;
  struct s_llib	*nelt = NULL;
  char		*lib = NULL;
  char		*alias = NULL;

  lib = get_arg(str, 1);
  alias = get_arg(str, 3);
  elt = context->f_lib;

  while (elt && my_strcmp(elt->lib, lib) != 0)
    elt = elt->next;

  if (elt && my_strcmp(elt->lib, lib) == 0)
    {
      context->errno = LIB_AL_OPEN_ERROR;
      context->errparam = elt->lib;
      context->errparam2 = elt->alias;
      return;
    }
  elt = context->f_lib;
  while (elt && my_strcmp(elt->alias, alias) != 0)
    {
      prev = elt;
      elt = elt->next;
    }
  if (elt && my_strcmp(elt->alias, alias) == 0)
    {
      context->errno = ALIAS_DEFINED_ERROR;
      context->errparam = alias;
      context->errparam2 = elt->lib;
      return;
    }
  if (!(nelt = malloc(sizeof (struct s_llib))))
    return;
  nelt->lib = lib;
  nelt->alias = alias;
  nelt->handle = dlopen(lib, RTLD_LAZY);
  if (!nelt->handle)
    {
      free(nelt);
      context->errno = OBJ_NF_ERROR;
      context->errparam = lib;
      return;
    }
  nelt->next = NULL;
  if (prev)
    prev->next = nelt;
  else
    context->f_lib = nelt;
}
