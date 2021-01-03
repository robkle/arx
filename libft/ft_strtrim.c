/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rklein <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 14:18:12 by rklein            #+#    #+#             */
/*   Updated: 2019/10/30 16:20:18 by rklein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	char	*tst;
	int		i;
	int		j;
	int		k;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] == ' ' || s[i] == '\n' || s[i] == '\t'))
		i++;
	j = 0;
	while (s[j])
		j++;
	j--;
	while (j >= i && (s[j] == ' ' || s[j] == '\n' || s[j] == '\t'))
		j--;
	k = j - i + 1;
	tst = (char*)malloc(sizeof(*tst) * k + 1);
	if (!tst)
		return (NULL);
	j = 0;
	while (j < k)
		tst[j++] = s[i++];
	tst[j] = '\0';
	return (tst);
}
