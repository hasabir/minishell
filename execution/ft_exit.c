/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:18 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 22:47:15 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#define L_MAX 9223372036854775807

int	valid_arg(char *arg)
{
	unsigned long int	nbr;
	int					sign;
	int					i;

	sign = 0;
	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		if (arg[i] == '-')
			sign = 1;
		i++;
	}
	nbr = 0;
	while (arg[i])
	{
		nbr = nbr * 10 + (arg[i] - 48);
		if ((sign == 0 && nbr > (unsigned long)L_MAX) || !ft_isdigit(arg[i])
			|| (sign && nbr > (unsigned long )L_MAX + 1))
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int	args_len(t_list	*list_command)
{
	int	len;
	int	i;

	len = 0;
	i = -1;
	if (list_command->data->options)
	{
		while (list_command->data->options[++i])
			len++;
	}
	i = -1;
	if (list_command->data->arguments)
	{
		while (list_command->data->arguments[++i])
			len++;
	}
	return (len);
}

void	many_args(t_list *list_command)
{
	char	*arg;

	arg = list_command->data->arguments[0];
	if (((valid_arg(arg))) || ((list_command->data->options)))
		ft_exit_status(list_command, "too many arguments", 0, 1);
	else if ((!valid_arg(arg)))
	{
		ft_exit_status(list_command, "numeric argument required",
			list_command->data->arguments[0], 255);
		exit(g_global.exit_status);
	}
}

void	one_arg(t_list *list_command)
{
	char	*arg;

	arg = NULL;
	if (list_command->data->arguments)
		arg = list_command->data->arguments[0];
	else if (list_command->data->options)
		arg = list_command->data->options[0];
	if (!valid_arg(arg))
	{
		ft_exit_status(list_command, "numeric argument required",
			arg, 255);
		exit(g_global.exit_status);
	}
	if (valid_arg(arg))
	{
		g_global.exit_status = ft_atoi(arg) % 256;
		exit(g_global.exit_status);
	}
}

void	ft_exit(t_list *list_command, int print)
{
	int	len;

	len = args_len(list_command);
	if (print)
		write(2, "exit\n", 6);
	if (!list_command->data->arguments && !list_command->data->options)
		exit(g_global.exit_status);
	if (len == 1)
		one_arg(list_command);
	else
		many_args(list_command);
}
