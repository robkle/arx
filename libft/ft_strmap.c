/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 16:22:15 by rklein            #+#    #+#             */
/*   Updated: 2019/10/30 14:35:28 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*dst;
	int		i;

	if (s && f)
	{
		dst = (char*)malloc(sizeof(*dst) * ft_strlen((char*)s) + 1);
		if (!dst)
			return (NULL);
		i = 0;
		while (s[i])
		{
			dst[i] = f(s[i]);
			i++;
		}
		dst[i] = '\0';
		return (dst);
	}
	return (NULL);
}
