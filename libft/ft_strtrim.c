/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:06:47 by hasabir           #+#    #+#             */
/*   Updated: 2021/11/22 18:23:48 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	st;
	size_t	en;

	i = 0;
	if (!s1 && !set)
		return (NULL);
	if (!s1)
		return ((char *)ft_calloc(1, sizeof (char)));
	if (!set)
		return (ft_strdup(s1));
	while (s1[i] && ft_strchr(set, s1[i]) != 0)
		i++;
	if (i == ft_strlen(s1))
		return (ft_calloc(1, sizeof(char)));
	if (s1[i] == 0)
		return (0);
	st = i;
	i = ft_strlen((char *)s1) - 1;
	while (i > 0 && ft_strchr(set, s1[i]) != 0)
		i--;
	en = i;
	return (ft_substr(s1, st, en - st + 1));
}
