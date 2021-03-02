/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infix_format.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <rklein@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 12:25:19 by rklein            #+#    #+#             */
/*   Updated: 2021/03/02 15:00:37 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arx.h"

static void	ft_free_link(t_st *link)
{
	free(link->op);
	free(link->type);
	free(link);
}

static void	ft_link_merging(t_st *infix)
{
	t_st	*tmp;
	char	*merge;
	char	*tstr;

	merge = ft_strjoin(infix->op, infix->next->op);
	tstr = infix->op;
	infix->op = merge;
	free(tstr);
	tmp = infix->next;
	infix->next = infix->next->next;
	if (infix->next->next)
		infix->next->prev = infix;
	ft_free_link(tmp);
}

void	ft_link_merge(t_st **infix)
{
	t_st	*begin;

	begin = *infix;
	while (*infix && (*infix)->next)
	{
		if ((ft_strequ((*infix)->type, "operand") || \
		ft_strequ((*infix)->type, "plusminus")) && \
		ft_strequ((*infix)->type, (*infix)->next->type))
		{
			ft_link_merging(*infix);
			*infix = begin;
		}
		else
			*infix = (*infix)->next;
	}
	*infix = begin;
}
