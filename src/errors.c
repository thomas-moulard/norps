/*
** errors.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Wed Oct 19 19:16:37 2005 thomas moulard
** Last update Sun Oct 23 08:09:14 2005 thomas moulard
*/

#include <unistd.h>
#include "common.h"

static void	print_error_shared(struct s_context *context)
{
  int		i = 0;

  write(STDERR_FILENO, "Shared object ``", 17);
  while (context->errparam[i])
	write(STDERR_FILENO, context->errparam + (i++), 1);
  write(STDERR_FILENO, "'' not found\n", 13);
}

static void	print_error_alias_def(struct s_context *context)
{
  int		i = 0;

  while (context->errparam[i])
    write(STDERR_FILENO, context->errparam + (i++), 1);
  write(STDERR_FILENO, " is already used for ", 21);
  i = 0;
  while (context->errparam2[i])
    write(STDERR_FILENO, context->errparam2 + (i++), 1);
  write(STDERR_FILENO, "\n", 1);
}

static void	print_error_alias_undef(struct s_context *context)
{
  int		i = 0;

  write(STDERR_FILENO, "Unknown alias ", 14);
  while (context->errparam[i])
    write(STDERR_FILENO, context->errparam + (i++), 1);
  write(STDERR_FILENO, " !\n", 3);
}

static void	print_error_al_open(struct s_context *context)
{
  int		i = 0;

  while (context->errparam[i])
    write(STDERR_FILENO, context->errparam + (i++), 1);
  write(STDERR_FILENO, " is already opened as ", 22);
  i = 0;
  while (context->errparam2[i])
    write(STDERR_FILENO, context->errparam2 + (i++), 1);
  write(STDERR_FILENO, "\n", 1);
}

void	print_error(struct s_context *context)
{
  int	i = 0;

  if (context->errno == SYNTAX_ERROR)
    write(STDERR_FILENO, "Syntax error !\n", 15);
  else if (context->errno == OBJ_NF_ERROR)
    print_error_shared(context);
  else if (context->errno == UNDEF_ALIAS_ERROR)
    print_error_alias_undef(context);
  else if (context->errno == UNDEF_SYMBOL_ERROR)
    {
      while (context->errparam[i])
	write(STDERR_FILENO, context->errparam + (i++), 1);
      write(STDERR_FILENO, "\n", 1);
    }
  else if (context->errno == LIB_AL_OPEN_ERROR)
    print_error_al_open(context);
  else if (context->errno == ALIAS_DEFINED_ERROR)
    print_error_alias_def(context);
  else if (context->errno == OTHER_ERROR)
    write(STDERR_FILENO, "Other error !\n", 14);
}

void	set_error(int n, char *p1, char *p2, struct s_context *context)
{
  context->errno = n;
  context->errparam = p1;
  context->errparam2 = p2;
}
