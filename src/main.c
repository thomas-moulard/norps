/*
** main.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Tue Oct 18 16:46:12 2005 thomas moulard
** Last update Sun Oct 23 02:28:11 2005 thomas moulard
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "common.h"

void	interactive_mode(struct s_context *context)
{
  char	*s;

  while (1)
    {
      write(STDOUT_FILENO, "> ", 2);
      s = getline(STDIN_FILENO);
      if (!s)
	continue;
      parse_line(s, context);
      print_error(context);
      context->errno = NO_ERROR;
      context->errparam = NULL;
      context->errparam2 = NULL;
    }
}

void	noninteractive_mode(struct s_context *context, char *f)
{
  char	*s;
  int	fd = 0;

  if (!(fd = open(f, O_RDONLY)))
    {
      set_error(OTHER_ERROR, NULL, NULL, context);
      print_error(context);
      return;
    }
  while ((s = getline(fd)) != NULL)
    {
      parse_line(s, context);
      print_error(context);
      set_error(NO_ERROR, NULL, NULL, context);
    }
  close(fd);
}

int			main(int argc, char *argv[])
{
  struct s_context	context;

  context.f_lib = NULL;
  context.f_var = NULL;
  context.errno = NO_ERROR;
  if (argc == 2)
    {
      print_error(&context);
      set_error(NO_ERROR, NULL, NULL, &context);
      return 0;
    }
  if (argc >= 3 && (!my_strcmp(argv[1], "-f") ||
		    !my_strcmp(argv[1], "--file")))
    {
      noninteractive_mode(&context, argv[2]);
      return 0;
    }
  interactive_mode(&context);
  return 0;
}
