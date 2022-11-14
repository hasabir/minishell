/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 11:36:57 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 15:11:14 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

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
