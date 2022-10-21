/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:33:16 by hasabir           #+#    #+#             */
/*   Updated: 2021/11/23 19:18:11 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t destsize)
{
	size_t	n;
	size_t	i;
	size_t	j;

	n = ft_strlen(src);
	if (!dst && !destsize)
		return (n);
	i = ft_strlen(dst);
	if (i <= destsize)
		n += i;
	else
		n += destsize;
	j = 0;
	if (i < destsize)
	{
		while (j + 1 < destsize - i && src[j])
		{
			dst[i + j] = src[j];
			j++;
		}
		dst[i + j] = '\0';
	}
	return (n);
}
