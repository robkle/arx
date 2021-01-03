#include "arx.h"

static char	*ft_calculate(int left, int right, char *op)
{
	int	res;

	res = 0;
	if (ft_strequ(op, "+"))
		res = left + right;
	else if (ft_strequ(op, "-"))
		res = left - right;
	else if (ft_strequ(op, "*"))
		res = left * right;
	else if (ft_strequ(op, "/"))
		res = left / right;
	else if (ft_strequ(op, "%"))
		res = left % right;
	else if (ft_strequ(op, "<"))
		res = left < right;
	else if (ft_strequ(op, ">"))
		res = left > right;
	else if (ft_strequ(op, "<="))
		res = left <= right;
	else if (ft_strequ(op, ">="))
		res = left >= right;
	else if (ft_strequ(op, "=="))
		res = left == right;
	else if (ft_strequ(op, "!="))
		res = left != right;
	else if (ft_strequ(op, "&&"))
		res = left && right;
	else if (ft_strequ(op, "||"))
		res = left || right;
	return (ft_itoa(res));
}

int	ft_calc(t_st *postfix)
{
	t_st	*stack;
	int		top;

	stack = NULL;
	while (postfix)
	{
		if (!ft_strequ(postfix->type, "operator"))
			ft_push_stack(&stack, postfix->op, postfix->type);
		else if (ft_strequ(postfix->op, "u+") || ft_strequ(postfix->op, "u-"))
		{
			if (ft_strequ(postfix->op, "u-"))
				stack->op = ft_itoa(-1 * (ft_atoi(stack->op)));
		}
		else if(ft_strequ(postfix->op, "p++") || ft_strequ(postfix->op, "p--") \
		|| ft_strequ(postfix->op, "s++") || ft_strequ(postfix->op, "s--"))
			ft_intvar(stack, postfix->op);
		else
		{
			if (ft_strequ(stack->type, "intvar"))
				ft_intvar(stack, NULL);
			top = ft_atoi(stack->op);
			ft_pop_stack(&stack);
			if (ft_strequ(stack->type, "intvar"))
				ft_intvar(stack, NULL);
			ft_modify_link(stack, \
			ft_calculate(ft_atoi(stack->op), top, postfix->op), "integer");
		}
		postfix = postfix->next;
	}
	if (ft_strequ(stack->type, "intvar"))
		ft_intvar(stack, NULL);
	top = ft_atoi(stack->op);
	free(stack->op);
	free(stack);
	return (top);
}
