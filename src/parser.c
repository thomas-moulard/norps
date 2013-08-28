/*
** parser.c for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Tue Oct 18 16:47:08 2005 thomas moulard
** Last update Sun Oct 23 09:58:49 2005 thomas moulard
*/

#include <stdio.h>
#include "common.h"

static const char *tokens[] =
  {
    "open",
    "as",
    "close",
    "exit",
    "leaks",
    "on",
    "off",
    "libs",
    ":",
    ";",
    NULL
  };

static const int grammar[N_GRAM_RULES][5] =
  {
    {TOK_LIBS, EOG, EOG, EOG, EOG},
    {TOK_OPEN, IDENT, TOK_AS, IDENT, EOG},
    {TOK_CLOSE, IDENT, EOG, EOG, EOG},
    {TOK_EXIT, EOG, EOG, EOG, EOG},
    {TYPE, FUNCTION, TOK_SEMICOLON, EOG, EOG},
    {FUNCTION, TOK_SEMICOLON, EOG, EOG, EOG},
    {EOG, EOG, EOG, EOG, EOG}
  };

static void	skip_space(char *s, int *pos)
{
  while (is_space(s[*pos]))
    (*pos)++;
}

static int	recognize(char *l, const char *tok)
{
  int		i = 0;

  while (l[i] && tok[i] && !is_space(l[i]) && l[i] == tok [i])
    ++i;
  if (!tok[i] && (!l[i] || is_space(l[i])))
    return i;
  return 0;
}

static int	recog_separator(char *l, int *i)
{
  if (l[*i] != ':')
    return 0;
  ++(*i);
  if (l[*i] != ':')
    return 0;
  ++(*i);
  return 1;
}

static int	recognize_function(char *l)
{
  int		i = 0;

  while (l[i] && !is_space(l[i]) && l[i] != ':')
    ++i;
  if (!recog_separator(l, &i))
    return 0;
  ++i;
  while (l[i] && !is_space(l[i]) && l[i] != '(')
    ++i;
  if (l[i] != '(')
    return 0;
  ++i;
  while (l[i] && l[i] != ')')
    {
      while (l[i] && l[i] != ')' && l[i] != ',')
	++i;
      if (l[i] != ')')
	++i;
      skip_space(l, &i);
    }
  if (l[i] == ')')
    return ++i;
  return 0;
}

static int	recognize_ident(char *l)
{
  int		i = 0;

  while (l[i] && !is_space(l[i]))
    ++i;
  return i;
}

int		recognize_type(char *l)
{
  int		i = 0;

  if (l[i] != '(')
    return 0;
  i++;
  while (l[i] && l[i] != ')')
    ++i;
  if (l[i] != ')')
    return 0;
  return ++i;
}

int		lexer(char *s, int *pos)
{
  int		tok = 0;
  int		res = 0;

  while (tokens[tok])
    {
      if ((res = recognize(s + *pos, tokens[tok])))
	{
	  *pos += res;
	  return tok + 1;
	}
      ++tok;
    }
  if ((res = recognize_type(s + *pos)))
    {
      *pos += res;
      return TYPE;
    }
  if ((res = recognize_function(s + *pos)))
    {
      *pos += res;
      return FUNCTION;
    }
  if ((res = recognize_ident(s + *pos)))
    {
      *pos += res;
      return IDENT;
    }
  return NOTRECOGNIZED;
}

int		cmp_rule(char *s, int r)
{
  int		i = 0;
  int		pos = 0;

  while (s[pos] && i < 5)
    {
      skip_space(s, &pos);
      if (lexer(s, &pos) != grammar[r][i])
	return 0;
      ++i;
    }
  skip_space(s, &pos);
  return !s[pos] && (i >= 5 || grammar[r][i] == EOG);
}

void	parse_line(char *s, struct s_context *context)
{
  int	i = 0;
  int	r = -1;

  while (i < N_GRAM_RULES && r < 0)
    if (cmp_rule(s, i++))
      r = i;
  if (r == -1)
    {
      context->errno = 1;
      context->errparam = NULL;
      context->errparam2 = NULL;
    }
  else if (r == 1)
    libs(context);
  else if (r == 2)
    open_lib(s, context);
  else if (r == 3)
    close_lib(s, context);
  else if (r == 4)
    exit_program(context);
  else if (r == 5)
    call_function(s, context);
  else if (r == 6)
    call_function(s, context);
}
