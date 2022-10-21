/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:13:54 by hasabir           #+#    #+#             */
/*   Updated: 2021/11/22 18:22:44 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int				i;
	unsigned char	*ss;

	ss = (unsigned char *)s;
	i = 0;
	while (ss[i])
		i++;
	while (i >= 0)
	{
		if (ss[i] == (unsigned char)c)
			return ((char *)ss + i);
		i--;
	}
	return (0);
}
