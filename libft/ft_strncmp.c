/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:51:59 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/23 18:00:36 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char	*s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*ss;

	if (n == 0)
		return (0);
	s = (unsigned char *)s1;
	if (!s || !*s)
		return (-1);
	ss = (unsigned char *)s2;
	i = 0;
	while (s[i] && ss[i] && s[i] == ss[i] && i < n - 1)
		i++;
	return (s[i] - ss[i]);
}
