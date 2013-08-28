/*
** utils.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Wed Oct 19 15:08:05 2005 thomas moulard
** Last update Sun Oct 23 02:10:18 2005 thomas moulard
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "common.h"

int	is_space(char c)
{
  return c == ' ' || c == '\t';
}

char	*get_arg(char *str, int n)
{
  char	*res = NULL;
  int	i = 0;
  int	pos = 0;
  int	l = 32;

  if (!(res = malloc(l * sizeof (char))))
    return NULL;
  while (str[pos] && is_space(str[pos]))
    ++pos;
  for (i = 0; i < n; i++)
    {
      while (str[pos] && is_space(str[pos]))
	++pos;
      while (str[pos] && !is_space(str[pos]))
	++pos;
    }
  while (str[pos] && is_space(str[pos]))
    ++pos;
  i = 0;
  while (str[pos] && !is_space(str[pos]))
    {
      res[i++] = str[pos++];
      if (i >= l)
	res = realloc(res, l += 32);
    }
  res[i] = 0;
  return res;
}

int		my_strcmp(char *s1, char *s2)
{
  unsigned char	a = 0;
  unsigned char	b = 0;

  while (*s1 && *s2 && *s1 == *s2)
    {
      s1++;
      s2++;
    }
  a = *s1;
  b = *s2;
  return a - b;
}

static void	my_printnbr_positif(long n, int fd)
{
  long		i;
  char		c;
  long		div;

  div = 1;
  while (n / div >= 10)
      div *= 10;
  while (div > 0)
    {
      i = (n / div) % 10;
      c = '0' + i;
      write(fd, &c, 1);
      div /= 10;
    }
}

void	my_printnbr(int n, int fd)
{
  char	c;
  int	i;
  char	intmax[] = "2147483648";

  if (n == -0x7fffffff - 1)
    {
      c = '-';
      write(fd, &c, 1);
      for (i = 0; i < 10; i++ )
	write(fd, &intmax[i], 1);
      return;
    }
  if (n < 0)
    {
      c = '-';
      write(fd, &c, 1);
      my_printnbr_positif(-n, fd);
      return;
    }
  my_printnbr_positif(n, fd);
}

static void	my_printnbr_positif_hexa(long n, int fd)
{
  long		i;
  char		c;
  long		div;

  div = 1;
  while (n / div >= 16)
      div *= 16;
  while (div > 0)
    {
      i = (n / div) % 16;
      if (i < 10)
	c = '0' + i;
      else
	c = 'a' + i - 10;
      write(fd, &c, 1);
      div /= 16;
    }
}

void	my_printnbr_hexa(int n, int fd)
{
  char	c;

  if (n < 0)
    {
      c = '-';
      write(fd, &c, 1);
      my_printnbr_positif_hexa(-n, fd);
      return;
    }
  my_printnbr_positif_hexa(n, fd);
}
