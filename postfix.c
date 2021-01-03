#include "arx.h"

int	ft_operator_str(char *op)
{
	if (ft_strequ(op, "(") || ft_strequ(op, ")"))
		return (1);
	if (ft_strequ(op, "s++") || ft_strequ(op, "s--"))
		return (1);
	if (ft_strequ(op, "p++") || ft_strequ(op, "p--"))
		return (1);
	if (ft_strequ(op, "u+") || ft_strequ(op, "u-"))
		return (1);
	if (ft_strequ(op, "*") || ft_strequ(op, "/") || ft_strequ(op, "%"))
		return (1);
	if (ft_strequ(op, "+") || ft_strequ(op, "-"))
		return (1);
	if (ft_strequ(op, "<") || ft_strequ(op, ">"))
		return (1);
	if (ft_strequ(op, "<=") || ft_strequ(op, ">="))
		return (1);
	if (ft_strequ(op, "==") || ft_strequ(op, "!="))
		return (1);
	if (ft_strequ(op, "&&") || ft_strequ(op, "||"))
		return (1);
	return (0);
}
	
/**
	prcd (op, '(' ) = FALSE
	prcd ('(', op ) = FALSE,
	prcd(op, ')') = TRUE,  except op = '('
	prcd('(', ')') = FALSE, we should push, however instead of PUSH we will pop
*/
/*static int	ft_prcd(char left, char right)
{
	if (left == '(' || right == '(')
		return (0);
	if (right == ')')
		return (1);
	if (left == '*' || left == '/')
	{
		if (right == '*' ||  right == '/' || right == '+' || right == '-')
			return (1);
		else 
			return (0);
	}
	if (left == '+' || left == '-')
	{
		if (right == '+' || right == '-')
			return (1);
		else 
			return (0);
	}
	return (0);
}*/

static t_pr	ft_pr_assign(char *op)
{
	if (ft_strequ(op, "s++") || ft_strequ(op, "s--"))
		return (SU);
	if (ft_strequ(op, "u+") || ft_strequ(op, "u-") || ft_strequ(op, "p++") || \
	ft_strequ(op, "p--"))
		return (UNPR);
	if (ft_strequ(op, "*") || ft_strequ(op, "/") || ft_strequ(op, "%"))
		return (MDM);
	if (ft_strequ(op, "+") || ft_strequ(op, "-"))
		return (AS);
	if (ft_strequ(op, "<") || ft_strequ(op, ">") || \
	ft_strequ(op, "<=") || ft_strequ(op, ">="))
		return (RO);
	if (ft_strequ(op, "==") || ft_strequ(op, "!="))
		return (EO);
	if (ft_strequ(op, "&&"))
		return (LA);
	if (ft_strequ(op, "||"))
		return (LO);
	return (INVALID);
}

static int	ft_prcd_enum(char *left, char *right)
{
	t_pr	l;
	t_pr	r;

	if (ft_strequ(left, "(") || ft_strequ(right, "("))
		return (0);
	if (ft_strequ(right, ")"))
		return (1);
	l = ft_pr_assign(left);
	r = ft_pr_assign(right);
	if (l == UNPR)
		return (r > l);
	else
		return (r >= l);
}

t_st	*ft_itop_lst(t_st *infix)
{
	t_st	*stack;
	t_st	*postfix;
	
	stack = NULL;
	postfix = NULL;
	while (infix)	
	{
		if (!ft_operator_str(infix->op) && !ft_strequ(infix->type, "space"))
			ft_push_lst(&postfix, infix->op, infix->type);
		else if (!ft_strequ(infix->type, "space"))
		{
			if (!stack)
				ft_push_stack(&stack, infix->op, infix->type);
			else
			{
				while (stack && ft_prcd_enum(stack->op, infix->op))
				{
					ft_push_lst(&postfix, stack->op, stack->type);
					ft_pop_stack(&stack);
				}
				if (ft_strequ(infix->op,")"))
					ft_pop_stack(&stack);
				else
					ft_push_stack(&stack, infix->op, infix->type);
			}
		}
		infix = infix->next;
	}
	while (stack)
	{
		ft_push_lst(&postfix, stack->op, stack->type);
		ft_pop_stack(&stack);
	}
	return (postfix);
}
