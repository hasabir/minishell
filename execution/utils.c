/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:42:58 by namine            #+#    #+#             */
/*   Updated: 2022/11/09 01:43:24 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_strcmp(const char	*s1, const char *s2)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*ss;

	s = (unsigned char *)s1;
	if (!s || !*s)
		return (-1);
	ss = (unsigned char *)s2;
	i = 0;
	while (s[i] && ss[i] && s[i] == ss[i])
		i++;
	return (s[i] - ss[i]);
}
