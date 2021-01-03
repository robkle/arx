#include "arx.h"
#include <stdio.h>

static void	ft_print_arx_token(t_st *lst)
{
	while (lst)
	{
		if (ft_strequ(lst->type, "operator") && \
		(lst->op[0] == 'p' || lst->op[0] == 's' || lst->op[0] == 'u'))
			ft_putstr(&lst->op[1]);
		else
			ft_putstr(lst->op);
		lst = lst->next;
	}
}

void	ft_print_error(int error, t_st *infix, t_st *expr)
{
	write(1, "arx: ", 5);
	ft_print_arx_token(expr);
	if (error == INVOP)
		write(1, ": syntax error: invalid arithmetic operator ", 44);
	if (error == VTGFB)
		write(1, ": value too great for base ", 27);
	if (error == OPEXP)
		write(1, ": syntax error: operand expected ", 34);
	if (error == INVBA)
		write(1, ": invalid arithmetic base ", 26);
	if (error == INVNU)
		write(1, ": invalid number ", 17); 
	write(1, "(error token is \"", 17);
	ft_print_arx_token(infix);
	write(1, "\")\n", 3);
}

static int	ft_operator_check(t_st *infix, t_st *begin)
{
	t_st	*tmp;

	tmp = ft_skip_space(infix->prev, 0);

	if ((!tmp || ft_strequ(tmp->type, "operator")) && \
	(infix->op[0] != 'p' && infix->op[0] != 'u' && infix->op[0] != '('))	
	{
		ft_print_error(OPEXP, infix, begin);
		return (0);
	}
	tmp = ft_skip_space(infix->next, 1);	
	if (!tmp && infix->op[0] != 's')
	{
		ft_print_error(OPEXP, infix, begin);
		return (0);
	}
	return (1);
}

static t_st	*ft_error_checker(t_st *infix)
{
	t_st	*begin;

	begin = infix;
	while (infix)
	{
		if (ft_strequ(infix->type, "invop"))
		{
			ft_print_error(INVOP, infix, begin);
			return (NULL);
		}
		if (ft_strequ(infix->type, "invnum"))
		{
			ft_print_error(VTGFB, infix, begin);
			return (NULL);
		}
		if (ft_strequ(infix->type, "hash") || ft_strequ(infix->type, "hexoct"))
		{
			if (!ft_base(infix, begin))
				return (NULL);
		}
		if (ft_strequ(infix->type, "operator"))
		{
			if (!ft_operator_check(infix, begin))
				return (NULL);
		}
		infix = infix->next;
	}
	return (begin);
}

t_st	*ft_infix_checker(t_st *infix)
{
	t_st	*begin;

	begin = infix;
	while (infix)
	{
		if (ft_isalnum(infix->op[0]) || infix->op[0] == '_' || \
		infix->op[0] == '#' || infix->op[0] == '@')
			infix->type = ft_strdup("operand");
		else if (infix->op[0] == '+' || infix->op[0] == '-')
			infix->type = ft_strdup("plusminus");
		else if (infix->op[0] == ')')
			infix->type = ft_strdup("clbr");
		else if (ft_operator_str(infix->op))
			infix->type = ft_strdup("operator");
		else if (infix->op[0] == ' ' || infix->op[0] == '\t')
			infix->type = ft_strdup("space");
		else
			infix->type = ft_strdup("invop");
		infix = infix->next;
	}
	ft_operand(&begin);
	ft_plusminus(&begin);
	return (ft_error_checker(begin));
}
