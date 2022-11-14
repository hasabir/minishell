/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 04:49:43 by namine            #+#    #+#             */
/*   Updated: 2022/11/14 16:30:52 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

void	ft_pwd(t_list *list_command)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		ft_putstr_fd(pwd, list_command->data->output_file);
		ft_putstr_fd("\n", list_command->data->output_file);
		g_global.exit_status = 0;
	}
	else
		ft_exit_status(list_command, "No such file or directory", 0, 1);
	free(pwd);
}
