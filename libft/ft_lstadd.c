/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 09:40:44 by rklein            #+#    #+#             */
/*   Updated: 2019/10/28 09:40:48 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd(t_list **alst, t_list *nlst)
{
	if (nlst)
	{
		if (*alst)
			nlst->next = *alst;
		*alst = nlst;
	}
}