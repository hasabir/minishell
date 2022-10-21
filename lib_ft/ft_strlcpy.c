/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:01:49 by hasabir           #+#    #+#             */
/*   Updated: 2021/11/22 18:19:06 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int		n;
	size_t	i;

	n = ft_strlen((char *)src);
	i = 0;
	if (!dstsize)
		return (n);
	while (src[i] && i < (dstsize - 1))
	{
		dst[i] = (char)src[i];
		i++;
	}
	dst[i] = '\0';
	return (n);
}
