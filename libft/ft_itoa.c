/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 08:46:37 by hasabir           #+#    #+#             */
/*   Updated: 2021/11/23 17:37:48 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	i;

	if (n < 0)
		n = -n;
	i = 1;
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	ft_convnbr(int nb)
{
	char	p;

	if (nb >= 10)
		ft_convnbr(nb / 10);
	p = nb % 10 + '0';
	return (p);
}

static char	*ft_isnegative(char *str, int n)
{
	int	i;

	if (n >= 0)
		return (str);
	i = ft_strlen(str) + 1;
	while (--i > 0)
		str[i] = str[i - 1];
	str[i] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		nb;
	int		nbr;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	nbr = n;
	nb = ft_intlen(n);
	if (n < 0)
	{
		n = -nbr;
		p = (char *)ft_calloc(nb + 2, sizeof (char));
	}
	else
		p = (char *)ft_calloc(nb + 1, sizeof (char));
	if (!p)
		return (0);
	while (--nb >= 0)
	{
		p[nb] = ft_convnbr(n);
		if (n >= 10)
			n = n / 10;
	}
	p = ft_isnegative(p, nbr);
	return (p);
}
