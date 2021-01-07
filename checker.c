#include "arx.h"
#include <stdio.h>

static int	ft_operand_check(t_st *infix, t_st *begin)
{
	t_st	*tmp;
	tmp = infix->prev;
	while (tmp)
	{
		if (ft_strequ(tmp->type, "hash") || ft_strequ(tmp->type, "hexoct") \
		|| ft_strequ(tmp->type, "integer") || ft_strequ(tmp->type, "intvar") \
		|| ft_strequ(tmp->type, "intvar") || ft_strequ(tmp->type, "clbr") || \
		tmp->op[0] == 's')
		{
			ft_print_error(SNERR, infix, begin);
			return (0);
		}
		if (ft_strequ(tmp->type, "operator") && tmp->op[0] != '(' && \
		tmp->op[0] != 'u' && tmp->op[0] != 'p')
			break;
		tmp = tmp->prev;
	}
	return (1);
}

static int	ft_pref_suf_check(t_st *infix, t_st *begin)
{
	t_st	*tmp;
	
	tmp = ft_skip_space(infix->prev, 0);
	if (infix->op[0] == 'p' && tmp)
	{
		if (!ft_strequ(tmp->type, "operator"))
		{
			ft_print_error(SNERR, infix, begin);
			return (0);
		}
	}
	/*tmp = ft_skip_space(infix->next, 1);
	if (infix->op[0] == 's' && tmp)
	{
		if (!ft_strequ(tmp->type, "operator"))
		{
			ft_print_error(SNERR, tmp, begin);
			return (0);
		}
	}*/
	return (1);
}

static int	ft_operator_check(t_st *infix, t_st *begin)
{
	t_st	*tmp;

	if (infix->op[0] == 'p'/* || infix->op[0] == 's'*/)
	{
		if (!ft_pref_suf_check(infix, begin))
			return (0);
	}
	else
	{
		tmp = ft_skip_space(infix->prev, 0);
		if ((!tmp || ft_strequ(tmp->type, "operator")) && (tmp->op[0] != 's' \
		&& infix->op[0] != 'p' && infix->op[0] != 'u' && infix->op[0] != '('))	
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
	}
	return (1);
}

static t_st	*ft_error_checker(t_st *infix)
{
	t_st	*begin;

	begin = infix;
	while (infix)
	{
		if (ft_strequ(infix->type, "invop") || ft_strequ(infix->type, "invnum"))
		{
			ft_print_error(ft_strequ(infix->type, "invop") ? INVOP : VTGFB, infix, begin);
			return (NULL);
		}
		if (ft_strequ(infix->type, "hash") || ft_strequ(infix->type, "hexoct"))
		{
			if (!ft_base(infix, begin, 0))
				return (NULL);
		}
		if (ft_strequ(infix->type, "operator"))
		{
			if (!ft_operator_check(infix, begin))
				return (NULL);
		}
		else if (!ft_strequ(infix->type, "clbr") && !ft_strequ(infix->type, "space"))
		{
			if (!ft_operand_check(infix, begin))
				return (NULL);
		}
		infix = infix->next;
	}
	ft_base_calc(begin);
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
