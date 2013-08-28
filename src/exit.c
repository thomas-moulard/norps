/*
** exit.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Wed Oct 19 19:07:41 2005 thomas moulard
** Last update Thu Oct 20 01:16:12 2005 thomas moulard
*/

#include <stdlib.h>
#include "common.h"

void	exit_program(struct s_context *context)
{
  print_error(context);

  if (context->errno > 10)
    exit(context->errno / 10);
    exit(context->errno);
}
