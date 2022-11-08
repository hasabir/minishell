/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 18:15:21 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/16 12:09:55 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char	*s1)
{
	char	*p;
	int		len;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1) + 1;
	p = (char *)malloc(len * sizeof (char));
	if (!p)
		return (0);
	ft_strlcpy(p, (char *)s1, len);
	return (p);
}
