/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 16:13:53 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/28 16:46:38 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	size_t	a1;
	size_t	a2;
	size_t	i;
	size_t	j;

	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	if (!s1 && !s2)
		return (NULL);
	a1 = ft_strlen((char *)s1);
	a2 = ft_strlen((char *)s2);
	p = (char *)malloc((a1 + a2 + 1) * sizeof(char));
	if (!p)
		return (0);
	i = -1;
	while (++i < a1)
		p[i] = s1[i];
	j = -1;
	while (++j < a2)
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}
