/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:18 by namine            #+#    #+#             */
/*   Updated: 2022/11/11 06:08:34 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#define L_MAX 9223372036854775807

int arg_is_valid(t_list *list_command, char *cmd, char *arg)
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
			error_msg(list_command, cmd, ": numeric argument required\n", arg);
			return (0);
		}
		i++;
	}
	return (1);
}

void ft_exit(t_list *list_command)
{
    if (!list_command->data->arguments && !list_command->data->options && ft_lstsize((t_linked_list *)list_command) == 1)
	{
		write(2, "exit\n", 6);
    	exit(0);
	}
	else if (list_command->data->arguments && list_command->data->arguments[1] == NULL)
	{
		if (arg_is_valid(list_command, list_command->data->cmd, list_command->data->arguments[0]))
		{
			write(2, "exit\n", 6);
			exit(ft_atoi(list_command->data->arguments[0]) % 256);	
		}
		else
			exit(255);
	}
	else if (list_command->data->options && list_command->data->options[1] == NULL)
	{
		if (arg_is_valid(list_command, list_command->data->cmd, list_command->data->options[0]))
		{
			write(2, "exit\n", 6);
			exit(ft_atoi(list_command->data->options[0]) % 256);
		}
		else
			exit(255);
	}
    else if (list_command->data->arguments[1] != NULL || list_command->data->options[1] != NULL)
    {
		if (!arg_is_valid(list_command, list_command->data->cmd, list_command->data->arguments[0]))
			exit(255);
		else
			error_msg(list_command, list_command->data->cmd, ": too many arguments\n", list_command->data->arguments[0]);
	}
}
