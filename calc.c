/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:59:30 by rklein            #+#    #+#             */
/*   Updated: 2021/03/02 14:59:33 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arx.h"

static char	*ft_divmod(int left, int right, char *op)
{
	int	res;

	if (right == 0)
	{
		write(1, "\narx: division by 0\n", 21);
		return (NULL);
	}
	res = 0;
	if (ft_strequ(op, "/"))
		res = left / right;
	else if (ft_strequ(op, "%"))
		res = left % right;
	return (ft_itoa(res));
}

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
	else if (ft_strequ(op, "/") || ft_strequ(op, "%"))
		return (ft_divmod(left, right, op));
	else if (op[0] == '<')
		res = op[1] == '=' ? left <= right : left < right;
	else if (op[0] == '>')
		res = op[1] == '=' ? left >= right : left > right;
	else if (op[1] == '=')
		res = op[0] == '=' ? left == right : left != right;
	else if (ft_strequ(op, "&&"))
		res = left && right;
	else if (ft_strequ(op, "||"))
		res = left || right;
	return (ft_itoa(res));
}

static int	ft_calc_pop(t_st **stack, char *op)
{
	int		top;
	char	*tmp;

	if (ft_strequ((*stack)->type, "intvar"))
		ft_intvar(*stack, NULL);
	top = ft_atoi((*stack)->op);
	ft_pop_stack(stack);
	if (ft_strequ((*stack)->type, "intvar"))
		ft_intvar(*stack, NULL);
	if (!(tmp = ft_calculate(ft_atoi((*stack)->op), top, op)))
		return (0);
	ft_modify_link(*stack, tmp, "integer");
	free(tmp);
	return (1);
}

static char	*ft_calc_free(t_st **stack, char *res)
{
	ft_free_lst(stack);
	return (res);
}

char		*ft_calc(t_st *postfix)
{
	t_st		*stack;
	long long	top;

	stack = NULL;
	while (postfix)
	{
		if (!ft_strequ(postfix->type, "operator"))
			ft_push_stack(&stack, postfix->op, postfix->type);
		else if (ft_strequ(postfix->op, "u+") || ft_strequ(postfix->op, "u-"))
			stack->op = ft_strequ(postfix->op, "u-") ? \
			ft_itoa(-1 * (ft_atoi(stack->op))) : stack->op;
		else if (ft_strequ(postfix->op, "p++") || \
		ft_strequ(postfix->op, "p--") || ft_strequ(postfix->op, "s++") || \
		ft_strequ(postfix->op, "s--"))
			ft_intvar(stack, postfix->op);
		else if (!ft_calc_pop(&stack, postfix->op))
			return (ft_calc_free(&stack, NULL));
		postfix = postfix->next;
	}
	if (ft_strequ(stack->type, "intvar"))
		ft_intvar(stack, NULL);
	top = ft_atoi(stack->op);
	return (ft_calc_free(&stack, ft_itoa(top)));
}

/*static char	*ft_divmod(int left, int right, char  *op)
{
	int	res;

	if (right == 0)
	{
		write(1, "\narx: division by 0\n", 21);
		return (NULL);
	}
	res = 0;
	if (ft_strequ(op, "/"))
		res = left / right;
	else if (ft_strequ(op, "%"))
		res = left % right;
	return (ft_itoa(res));
}

static char	*ft_calculate(int left, int right, char *op)
{
	int		res;

	res = 0;
	if (ft_strequ(op, "+"))
		res = left + right;
	else if (ft_strequ(op, "-"))
		res = left - right;
	else if (ft_strequ(op, "*"))
		res = left * right;
	else if (ft_strequ(op, "/") || ft_strequ(op, "%"))
		return (ft_divmod(left, right, op));
	else if (op[0] == '<')
		res = op[1] == '=' ? left <= right : left < right;
	else if (op[0] == '>')
		res = op[1] == '=' ? left >= right : left > right;
	else if (op[1] == '=')
		res = op[0] == '=' ? left == right : left != right;
	else if (ft_strequ(op, "&&"))
		res = left && right;
	else if (ft_strequ(op, "||"))
		res = left || right;
	return (ft_itoa(res));
}

static void	ft_calc_pop(t_st **stack, char *op)
{
	int	top;

	if (ft_strequ((*stack)->type, "intvar"))
		ft_intvar(*stack, NULL);
	top = ft_atoi((*stack)->op);
	ft_pop_stack(stack);
	if (ft_strequ((*stack)->type, "intvar"))
		ft_intvar(*stack, NULL);
	ft_modify_link(*stack, \
	ft_calculate(ft_atoi((*stack)->op), top, op), "integer");
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
			ft_calc_pop(&stack, postfix->op);
		postfix = postfix->next;
	}
	if (ft_strequ(stack->type, "intvar"))
		ft_intvar(stack, NULL);
	top = ft_atoi(stack->op);
	ft_free_lst(&stack);
	return (top);
}*/
