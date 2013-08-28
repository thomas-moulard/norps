/*
** libs.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Thu Oct 20 16:51:48 2005 thomas moulard
** Last update Sun Oct 23 08:10:38 2005 thomas moulard
*/

#include <unistd.h>
#include <stdlib.h>
#include "common.h"

void		libs(struct s_context *context)
{
  struct s_llib	*elt = NULL;
  int		i = 0;

  elt = context->f_lib;
  while (elt)
    {
      i = 0;
      write(STDOUT_FILENO, "~ ", 2);
      while (elt->lib[i] && elt->lib[i] != '.' && elt->lib[i + 1] != 's'
	     && elt->lib[i] != 'o')
	write(STDOUT_FILENO, elt->lib + (i++), 1);
      write(STDOUT_FILENO, " is opened as ", 14);
      i = 0;
      while (elt->alias[i])
	write(STDOUT_FILENO, elt->alias + (i++), 1);
      write(STDOUT_FILENO, "\n", 1);
      elt = elt->next;
    }
}
