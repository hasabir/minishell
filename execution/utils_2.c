/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:36:57 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 23:28:13 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	fork_failed(char *arg, char *msg, int exit_code)
{
	ft_putstr_fd("Petit_shell : ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" : ", 2);
	ft_putendl_fd(msg, 2);
	g_global.exit_status = exit_code;
	return (0);
}

int	ft_exit_status(t_list *list_command,
	char *msg, char *arg, int exit_code)
{
	error_msg(list_command, list_command->data->cmd, msg, arg);
	g_global.exit_status = exit_code;
	return (0);
}

void	malloc_failed(void)
{
	g_global.exit_status = 1;
	exit(EXIT_FAILURE);
}
