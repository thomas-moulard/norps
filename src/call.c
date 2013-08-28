/*
** call.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Thu Oct 20 23:52:10 2005 thomas moulard
** Last update Sun Oct 23 09:17:28 2005 thomas moulard
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "common.h"

int	count_params(char *s)
{
  int	i = 0;
  int	res = 0;
  int	instring = 0;

  i = recognize_type(s);
  while (s[i] && s[i] != '(')
      i++;
  if (!s[i])
    return 0;
  i++;
  if (s[i] == ')')
    return 0;
  while (s[i] && s[i] != ')')
    {
      if (s[i] == '"')
	instring = !instring;
      if (s[i] == ',' && !instring)
	res++;
      i++;
    }
  return res + 1;
}



static char	escape(char c)
{
  if (c == 0)
    return 0;
  else if (c == 't')
    return '\t';
  else if (c == 'n')
    return '\n';
  return 0;
}

union u_arg	convert_string(char *l)
{
  union	u_arg	u;
  int		pos = 0;
  int		pos2 = 1;
  int		s = 32;
  char		*res = NULL;

  res = malloc(s * sizeof (char));
  while (l[pos2 + 1])
    {
      if (pos >= s)
	res = realloc(res, s += 32);
      if (l[pos2] == '\\')
	{
	  res[pos] = escape(l[pos2 + 1]);
	  pos2++;
	} else
	  res[pos] = l[pos2];
      ++pos2;
      ++pos;
    }
  res[pos] = 0;
  u.s = res;
  return u;
}

int		is_int(char *s)
{
  int		i = 0;

  if (*s == '-')
    ++i;
  while (s[i] && s[i] >= '0' && s[i] <= '9')
    ++i;
  return !s[i];
}

union u_arg	convert_int(char *l)
{
  union	u_arg	u;
  int		i = 0;
  int		signe = 1;

  if (l[i] == '-')
    {
      i++;
      signe = -1;
    }
  u.i = 0;
  while (l[i])
    {
      u.i = u.i * 10 + l[i] - '0';
      ++i;
    }
  u.i *= signe;
  return u;
}

union u_arg	convert_arg(char *s)
{
  union u_arg	u;
  u.l = 0;

  if (*s == '"')
    return convert_string(s);
  if (is_int(s))
    {
      return convert_int(s);
    }
  return u;
}

static void	print_res_int(char *l, int i, long res)
{
  if (l[i + 1] == 'i' && l[i + 2] == 'n' && l[i + 3] == 't')
    my_printnbr(res, STDOUT_FILENO);
  else if (l[i + 1] == 'u' && l[i + 2] == 'i' && l[i + 3] == 'n'
	   && l[i + 4] == 't')
    my_printnbr(res, STDOUT_FILENO);
  else if (l[i + 1] == 's' && l[i + 2] == 'h' && l[i + 3] == 'o'
	   && l[i + 4] == 'r' && l[i + 5] == 't')
    my_printnbr(res, STDOUT_FILENO);
  else if (l[i + 1] == 'u' && l[i + 2] == 's' && l[i + 3] == 'h'
	   && l[i + 4] == 'o' && l[i + 5] == 'r' && l[i + 6] == 't')
    my_printnbr(res, STDOUT_FILENO);
  else if (l[i + 1] == 'c' && l[i + 2] == 'h' && l[i + 3] == 'a'
	   && l[i + 4] == 'r')
    my_printnbr(res, STDOUT_FILENO);
  else if (l[i + 1] == 'u' && l[i + 2] == 'c' && l[i + 3] == 'h'
	   && l[i + 4] == 'a' && l[i + 5] =='r')
    my_printnbr(res, STDOUT_FILENO);
  else if (l[i + 1] == 'l' && l[i + 2] == 'o' && l[i + 3] == 'n'
	   && l[i + 4] == 'g')
    my_printnbr(res, STDOUT_FILENO);
  else if (l[i + 1] == 'u' && l[i + 2] == 'l' && l[i + 3] == 'o'
	   && l[i + 4] == 'n' && l[i + 5] =='g')
    my_printnbr(res, STDOUT_FILENO);
  write(STDOUT_FILENO, "\n", 1);
}

void		print_res(char *l, long res)
{
  int		i = 0;

  if (!recognize_type(l))
    return;
  while (l[i] && l[i] != '(')
    ++i;
  print_res_int(l, i, res);
  if (l[i + 1] == 'v' && l[i + 2] == 'o' && l[i + 3] == 'i' &&
      l[i + 4] == 'd' && l[i + 5] != ')')
    {
      write(STDOUT_FILENO, "0x", 2);
      my_printnbr_hexa(res, STDOUT_FILENO);
      write(STDOUT_FILENO, "\n", 1);
    }
  else if (l[i + 1] == 'v' && l[i + 2] == 'o' && l[i + 3] == 'i' &&
	   l[i + 4] == 'd')
    write(STDOUT_FILENO, "(void)\n", 7);
}

static void	call_fct(char *s, t_func f)
{
  int		n = 0;
  long		res = 0;

  n = count_params(s);
  if (n == 0)
    res = f();
  else if (n == 1)
    res = f(convert_arg(get_params(s, 0)).s);
  else if (n == 2)
    res = f(convert_arg(get_params(s, 0)).s,
	    convert_arg(get_params(s, 1)).s);
  else if (n == 3)
    res = f(convert_arg(get_params(s, 0)).s,
	    convert_arg(get_params(s, 1)).s,
	    convert_arg(get_params(s, 2)).s);
  else if (n == 4)
    res = f(convert_arg(get_params(s, 0)).s,
	    convert_arg(get_params(s, 1)).s,
	    convert_arg(get_params(s, 2)).s,
	    convert_arg(get_params(s, 3)).s);
  print_res(s, res);
}

void		call_function(char *s, struct s_context *context)
{
  char		*alias = NULL;
  char		*fct = NULL;
  struct s_llib	*elt = NULL;
  t_func	f;

  alias = get_alias(s);
  fct = get_fct(s);
  elt = context->f_lib;
  while (elt && my_strcmp(alias, elt->alias) != 0)
    elt = elt->next;
  if (!elt)
    {
      set_error(UNDEF_ALIAS_ERROR, alias, NULL, context);
      return;
    }
  if (!(f = (t_func) dlsym(elt->handle, fct)))
    {
      set_error(UNDEF_SYMBOL_ERROR, dlerror(), NULL, context);
      return;
    }
  call_fct(s, f);
}
