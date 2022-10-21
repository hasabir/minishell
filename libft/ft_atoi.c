/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 19:11:36 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/21 17:55:02 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define L_MAX 9223372036854775807

static int	ft_conv_nbr(const char *str, int n)
{
	unsigned long int	i;
	unsigned long int	nb;

	i = 0;
	nb = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + str[i] - '0';
		if (n == 1 && nb >= L_MAX)
			return (-1);
		else if (n == -1 && nb >= (unsigned long )L_MAX + 1)
			return (0);
		i++;
	}
	return ((int)nb * n);
}

int	ft_atoi(const char *str)
{
	unsigned long int	i;
	int					n;

	i = 0;
	n = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		n = -n;
		i++;
	}
	else if (str[i] == '+' )
		i++;
	return (ft_conv_nbr(str + i, n));
}
