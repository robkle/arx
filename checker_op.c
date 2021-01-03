#include "arx.h"

static int	ft_inval(char *op)
{
	if (!ft_isalpha(*op) && *op != '_')
		return (0);
	while (*op)
	{
		if (!ft_isalnum(*op) && *op != '_')
			return (0);
		op++;
	}
	return (1);
}

static int	ft_integer(char *op)
{
	while (*op)
	{
		if (!ft_isdigit(*op))
			return (0);
		op++;
	}
	return (1);
}

static int	ft_hexoct(char *op)
{
	if (op[0] == '0' && (ft_isdigit(op[1]) || op[1] == 'x') && \
	(ft_isalnum(op[2]) || !op[2]))
			return (1);
	return (0);
}

static int	ft_hash(char *op)
{
	while (*op)
	{
		if (*op == '#')
			return (1);
		op++;
	}
	return (0);
}

void	ft_operand(t_st **infix)
{
	t_st	*begin;

	begin = *infix;
	while (*infix)
	{
		if (ft_strequ((*infix)->type, "operand"))
		{
			if (ft_hash((*infix)->op))
				ft_modify_link(*infix, NULL, "hash"); 
			else if (ft_hexoct((*infix)->op))
				ft_modify_link(*infix, NULL, "hexoct"); 
			else if (ft_integer((*infix)->op))
				ft_modify_link(*infix, NULL, "integer"); 
			else if (ft_inval((*infix)->op))
				ft_modify_link(*infix, NULL, "intvar"); 
			else
				ft_modify_link(*infix, NULL, "invnum");
		}
		*infix = (*infix)->next;
	}
	*infix = begin;
}
