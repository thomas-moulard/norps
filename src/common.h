/*
** common.h for norps in /u/a1/moular_t/rendu/moular_t-norps/src
**
** Made by thomas moulard
** Login   <moular_t@epita.fr>
**
** Started on  Tue Oct 18 16:57:23 2005 thomas moulard
** Last update Sun Oct 23 09:16:46 2005 thomas moulard
*/

#ifndef COMMON_H_
# define COMMON_H_

# define IDENT			0
# define TYPE			100
# define FUNCTION		101

# define TOK_OPEN		1
# define TOK_AS			2
# define TOK_CLOSE		3
# define TOK_EXIT		4
# define TOK_LEAKS		5
# define TOK_ON			6
# define TOK_OFF		7
# define TOK_LIBS		8
# define TOK_COLON		9
# define TOK_SEMICOLON		10

# define NOTRECOGNIZED		-1
# define EOG			-2

# define N_GRAM_RULES		7

# define NO_ERROR		0
# define SYNTAX_ERROR		1
# define OBJ_NF_ERROR		2
# define UNDEF_ALIAS_ERROR	3
# define UNDEF_SYMBOL_ERROR	4
# define ALIAS_DEFINED_ERROR	51
# define LIB_AL_OPEN_ERROR	52
# define OTHER_ERROR		6

struct			s_llib
{
  char			*alias;
  char			*lib;
  void			*handle;
  struct s_llib		*next;
};

struct			s_lvar
{
  char			*var;
  struct s_llib		*next;
};

struct			s_context
{
  struct s_llib		*f_lib;
  struct s_lvar		*f_var;
  unsigned		errno;
  char			*errparam;
  char			*errparam2;
};

union			u_arg
{
  char			*s;
  int			i;
  long			l;
};

typedef long (*t_func)();


char	*getline(int fd);

int	recognize_type(char *l);
void	parse_line(char *s, struct s_context *context);

void	open_lib(char *str, struct s_context *context);

void	close_lib(char *s, struct s_context *context);

void	exit_program(struct s_context *context);

void	libs(struct s_context *context);

void	call_function(char *s, struct s_context *context);

void	print_error(struct s_context *context);
void	set_error(int n, char *p1, char *p2, struct s_context *context);

int	is_space(char c);
char	*get_arg(char *str, int n);
int	my_strcmp(char *s1, char *s2);
void	my_printnbr(int n, int fd);
void	my_printnbr_hexa(int n, int fd);

char	*get_alias(char *l);
char	*get_fct(char *l);
char	*get_params(char *l, int n);

#endif /* !COMMON_H_ */
