/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:18 by namine            #+#    #+#             */
/*   Updated: 2022/11/09 00:25:04 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#define L_MAX 9223372036854775807

void error_msg(t_list *list_command, char *cmd, char *arg, int flag)
{
	if (ft_lstsize((t_linked_list *)list_command) == 1)
		write(2, "exit\n", 6);
	write(2, "Petit_shell: ", 14);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 3);
	write(2, arg, ft_strlen(arg));
	if (flag)
		write(2, ": numeric argument required\n", 29);
	if (!flag)
		write(2, ": too many arguments\n", 22);
}

int arg_is_valid(t_list *list_command, char *cmd, char *arg)
{
	unsigned long int	nbr;
	int					sign;
	int					i;

	i = 0;
	sign = 0;
	if (arg[i] == '-' || arg[i] == '+')
	{
		sign = 1;
		i++;
	}
	nbr = 0;
	while (arg[i] && (arg[i] >= '0' && arg[i] <= '9'))
	{
		nbr = nbr * 10 + (arg[i] - 48);
		if ((sign == 0 && nbr > (unsigned long)L_MAX) || (sign && nbr > (unsigned long )L_MAX + 1))
		{
			error_msg(list_command, cmd, arg, 1);
			return (0);
		}
		i++;
	}
	if (arg[i] != '\0')
	{
		error_msg(list_command, cmd, arg, 1);
		return (0);
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
    else if (list_command->data->arguments[1] != NULL)
    {
		if (!arg_is_valid(list_command, list_command->data->cmd, list_command->data->arguments[0]))
			exit(255);
		else
			error_msg(list_command, list_command->data->cmd, list_command->data->arguments[0], 0);
	}
}
