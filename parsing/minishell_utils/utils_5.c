/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 21:04:56 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/14 19:27:41 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing.h"

void	handle_signals(int sig)
{
	(void)sig;
	write (1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

char	*new_arg(char *stock, char *arg, int flag)
{
	char	*tmp;

	tmp = ft_strdup(arg);
	free(arg);
	arg = ft_strjoin(tmp, stock);
	if (!flag)
		free(stock);
	free(tmp);
	return (arg);
}
