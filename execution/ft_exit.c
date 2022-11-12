/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:18 by namine            #+#    #+#             */
/*   Updated: 2022/11/11 21:08:33 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#define L_MAX 9223372036854775807

int	arg_is_valid(char *arg)
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

int args_len(t_list	*list_command)
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

void many_args(t_list *list_command, int len)
{
	if ((len  > 1 && (list_command->data->arguments && arg_is_valid(list_command->data->arguments[0]))) ||
		(len  > 1 && (list_command->data->options)))
		error_msg(list_command, list_command->data->cmd, "too many arguments\n", NULL);
	else if (len  > 1 && (list_command->data->arguments && !arg_is_valid(list_command->data->arguments[0]))) 
	{
		error_msg(list_command, list_command->data->cmd, "numeric argument required\n", list_command->data->arguments[0]);
		exit(255);
	}
}

void one_arg(t_list *list_command, int len)
{
	if (len == 1 && (list_command->data->arguments && !arg_is_valid(list_command->data->arguments[0])))
	{
		error_msg(list_command, list_command->data->cmd, "numeric argument required\n", list_command->data->arguments[0]);
		exit(255);
	}
	if ((len == 1 && (list_command->data->arguments && arg_is_valid(list_command->data->arguments[0]))) ||
		(len == 1 && (list_command->data->options)))
	{
		write(2, "exit\n", 6);
    	exit(0);
	}
}

void ft_exit(t_list *list_command)
{
	int	len;
	
	len = args_len(list_command);
    if (!list_command->data->arguments && !list_command->data->options)
	{
		write(2, "exit\n", 6);
    	exit(0);
	}
	one_arg(list_command, len);
	many_args(list_command, len);
}
