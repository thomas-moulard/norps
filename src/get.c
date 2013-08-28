/*
** get.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
** 
** Made by thomas moulard
** Login   <moular_t@epita.fr>
** 
** Started on  Sun Oct 23 09:13:11 2005 thomas moulard
** Last update Sun Oct 23 09:17:31 2005 thomas moulard
*/

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "common.h"

char	*get_alias(char *l)
{
  int	i = 0;
  int	pos = 0;
  char	*res = NULL;
  int	s = 32;

  i = recognize_type(l);
  while (l[i] && is_space(l[i]))
    ++i;
  if (!(res = malloc(s * sizeof (char))))
    return NULL;
  while (l[i] && !is_space(l[i]) && l[i] != ':')
    {
      if (pos >= s)
	{
	  s += 32;
	  l = realloc(l, s);
	}
      res[pos++] = l[i++];
    }
  res[pos] = 0;
  return res;
}

char	*get_fct(char *l)
{
  int	i = 0;
  int	pos = 0;
  char	*res = NULL;
  int	s = 32;

  while (l[i] && l[i] != ':')
    ++i;
  i += 2;
  if (!(res = malloc(s * sizeof (char))))
    return NULL;
  while (l[i] && !is_space(l[i]) && l[i] != '(')
    {
      if (pos >= s)
	{
	  s += 32;
	  l = realloc(l, s);
	}
      res[pos++] = l[i++];
    }
  res[pos] = 0;
  return res;
}


static void	search_param(char *l, int *i, int n)
{
  *i = recognize_type(l);
  while (l[*i] && l[*i] != '(')
    ++(*i);
  ++(*i);
  while (n > 0)
    {
      while (l[*i] && l[*i] != ',')
	++(*i);
      ++(*i);
      n--;
    }
  while (l[*i] && is_space(l[*i]))
    ++(*i);
}

char	*get_params(char *l, int n)
{
  int	i = 0;
  int	s = 32;
  int	pos = 0;
  int	isstring = 0;
  char	*res = NULL;

  res = malloc(s * sizeof (char));
  search_param(l, &i, n);
  while (l[i] && (isstring || (l[i] != ',' && l[i] != ')')))
    {
      if (i >= s)
	l = realloc(l, s =+ 32);
      res[pos++] = l[i++];
    }
  res[pos] = 0;
  res = realloc(res, (pos + 1) * sizeof (char));
  return res;
}
