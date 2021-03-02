/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 14:59:11 by rklein            #+#    #+#             */
/*   Updated: 2021/03/02 15:05:51 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arx.h"

void	ft_free_lst(t_st **lst)
{
	t_st *tmp;
	while (*lst)
	{
		tmp = (*lst)->next;
		free((*lst)->op);
		free((*lst)->type);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int		ft_brackets(char *exp)
{
	char	stack[1024];
	int		i;

	ft_bzero(stack, 1024);
	i = 0;
	while (*exp)
	{
		if (*exp == '(')
			stack[i++] = *exp;
		else if (*exp == ')')
		{
			if (i > 0 && stack[i - 1] == '(')
				stack[--i] = '\0';
			else
				return (0);
		}
		exp++;
	}
	if (stack[0])
		return (0);
	return (1);
}

char	*read_exp(void)
{
	char	line[1024];
	int		count;
	char	buf;

	count = 0;
	read(0, &buf, 1);
	while (1)
	{
		if (buf == '\n')
			break ;
		line[count++] = buf;
		read(0, &buf, 1);
	}
	if (count == 0)
		return (NULL);
	line[count] = '\0';
	return (ft_strdup(line));
}

/*
** Creates an array of random variables for testing purposes
*/
static void	ft_intvar_tmp(void)
{
	g_iv = (char**)malloc(sizeof(char*) * 4);
	g_iv[0] = ft_strdup("var1=3");
	g_iv[1] = ft_strdup("var2=4");
	g_iv[2] = ft_strdup("var3=5");
	g_iv[3] = NULL;
}

static void	ft_print_exp(t_st *infix, t_st *postfix)
{
	ft_putstr("infix: ");
	while (infix)
	{
		ft_putstr(infix->op);
		write(1, " ", 1);
		infix = infix->next;
	}
	ft_putstr("\npostfix: ");
	while (postfix)
	{
		ft_putstr(postfix->op);
		write(1, " ", 1);
		postfix = postfix->next;
	}
}

int	main(void)
{
	char	*exp;
	t_st	*infix;
	t_st	*postfix;
	char	*res;

	ft_intvar_tmp();
	infix = NULL;
	postfix = NULL;
	while (1)
	{
		if ((exp = read_exp()))
		{
			if (exp[0] == 'q' && !exp[1])
				exit(EXIT_SUCCESS);
			if (ft_brackets(exp))
			{
				if ((infix = ft_extolst(exp)))
				{
					ft_itop_lst(infix, &postfix);
					ft_print_exp(infix, postfix);
					if((res = ft_calc(postfix)))
						printf("\nresult: %d\n", ft_atoi(res));
				}
			}
			else
				write(1, "Bracket error\n", 14);
		}
		free(exp);
		ft_free_lst(&infix);
		ft_free_lst(&postfix);
	}
	return (0);
}
