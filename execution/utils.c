/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:42:58 by namine            #+#    #+#             */
/*   Updated: 2022/11/10 05:20:17 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int		ft_strcmp(const char	*s1, const char *s2)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*ss;

	s = (unsigned char *)s1;
	if (!s || !*s)
		return (-1);
	ss = (unsigned char *)s2;
	i = 0;
	while (s[i] && ss[i] && s[i] == ss[i])
		i++;
	return (s[i] - ss[i]);
}

int		check_argument(char *str) 
{
    if (!ft_isalpha(*str) && (*str != '_'))
		return (0);
	str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && (*str != '_'))
			return (0);
		str++;
	}
	return (1);
}

void	error_msg(t_list *list_command, char *msg, int arg_index)
{
	write(2, "Petit_shell: ", 14);
	write(2, list_command->data->cmd, ft_strlen(list_command->data->cmd));
	write(2, ": ", 2);
	write(2, list_command->data->arguments[arg_index], ft_strlen(list_command->data->arguments[arg_index]));
	write(2, msg, 26);
}
