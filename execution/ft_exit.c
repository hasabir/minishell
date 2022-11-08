/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 16:37:18 by namine            #+#    #+#             */
/*   Updated: 2022/11/08 11:34:24 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#define L_MAX 9223372036854775807

void error_msg(char *cmd, char *arg, int flag)
{
	if (flag == -1)
		return ;
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

int arg_is_valid(char *cmd, char *arg, int flag)
{
	unsigned long int	nbr;
	int					sign;

	(void)flag;
	sign = 1;
	if (*cmd == '-' || *cmd == '+')
		cmd++;
	nbr = 0;
	while (*cmd && (*cmd >= '0' && *cmd <= '9'))
	{
		nbr = nbr * 10 + (*cmd - 48);
		// if (nbr > L_MAX)
		// {
		// 	error_msg(cmd, arg, flag);
		// 	return (0);
		// }
		// if (nbr > (unsigned long )L_MAX + 1)
		// {
		// 	error_msg(cmd, arg, flag);
		// 	return (0);
		// }
		cmd++;
	}
	if (*cmd != '\0')
	{
		error_msg(cmd, arg, 1);
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
		if (arg_is_valid(list_command->data->cmd, list_command->data->arguments[0], -1))
		{
			
			write(2, "exit\n", 6);
			exit(ft_atoi(list_command->data->arguments[0]) % 256);
		}
		else
		{
			error_msg(list_command->data->cmd, list_command->data->arguments[0], 1);
			exit(255);
		}
	}
	// else if (list_command->data->options && list_command->data->options[1] == NULL)
	// {
	// 	if (arg_is_valid(list_command->data->options[0]))
	// 	{
	// 		write(2, "exit\n", 6);
	// 		exit(ft_atoi(list_command->data->options[0]) + 256);
	// 	}
	// 	else
	// 	{
	// 		error_msg(list_command->data->cmd, list_command->data->options[0], 1);
	// 		exit(255);
	// 	}
	// }
    // else if (list_command->data->arguments[1] != NULL)
    // {
	// 	if (arg_is_valid(list_command->data->arguments[0]))
	// 	{
	// 		if (ft_lstsize((t_linked_list *)list_command) == 1)
	// 			write(2, "exit\n", 6);
	// 		write(2, "Petit_shell: ", 14);
	// 		write(2, list_command->data->cmd, ft_strlen(list_command->data->cmd));
	// 		write(2, ": too many arguments\n", 22);
	// 	}
	// 	else
	// 	{
	// 		if (ft_lstsize((t_linked_list *)list_command) == 1)
	// 			write(2, "exit\n", 6);
	// 		write(2, "Petit_shell: ", 14);
	// 		write(2, list_command->data->cmd, ft_strlen(list_command->data->cmd));
	// 		write(2, ": ", 3);
	// 		write(2, list_command->data->arguments[0], ft_strlen(list_command->data->arguments[0]));
	// 		write(2, ": numeric argument required\n", 29);
	// 		exit(255);
	// 	}
    // }
}
