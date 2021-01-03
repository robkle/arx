#ifndef ARX_H
# define ARX_H

#include "libft/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define INVOP 1
#define VTGFB 2
#define OPEXP 3
#define INVBA 4
#define INVNU 5

typedef struct	s_st
{
	char		*op;
	char		*type;
	struct s_st	*prev;
	struct s_st	*next;
}				t_st;

typedef enum	e_pr
{
	SU,
	UNPR,
	MDM, //multiplication, division, modulo
	AS, //addition subtraction
	RO, //relational operator
	EO, //equality operator
	LA, //logical AND
	LO,	//logical OR
	INVALID
}				t_pr;

char	**g_iv;

/*
** base.c
*/
int		ft_base(t_st *infix, t_st *begin);

/* 
** calc.c 
*/
int		ft_calc(t_st *postfix);

/* 
** checker.c 
*/
t_st	*ft_infix_checker(t_st *infix);
void	ft_print_error(int error, t_st *infix, t_st *expr);

/* 
** checker_op.c 
*/
void	ft_operand(t_st **infix);

/* 
** extolst.c 
*/
int		ft_operator(char c);
t_st	*ft_extolst(char *exp);

/*
** intvar.c
*/
void	ft_intvar(t_st *stack, char *op);

/* 
** plusminus.c 
*/
void	ft_plusminus(t_st **infix);
t_st	*ft_skip_space(t_st *link, const int move);

/* 
** postfix.c 
*/
char	*ft_postfix(char *exp);
int		ft_operator_str(char *op);
t_st	*ft_itop_lst(t_st *infix);

/* 
** utils.c 
*/
void	ft_modify_link(t_st *infix, char *op, char *type);
void	ft_pop_stack(t_st **stack);
void	ft_push_lst(t_st **infix, char *op, char *type);
void	ft_push_stack(t_st **stack, char *op, char *type);
t_st	*ft_last_link(t_st *lst);

#endif 
