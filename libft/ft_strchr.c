/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 10:50:50 by hasabir           #+#    #+#             */
/*   Updated: 2021/11/22 17:54:23 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*ss;

	ss = (unsigned char *)s;
	while (*ss)
	{
		if (*ss == (unsigned char)c)
		{
			return ((char *)ss);
		}
		ss++;
	}
	if (c == 0)
		return ((char *)ss);
	return (0);
}
