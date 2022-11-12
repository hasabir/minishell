/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namine <namine@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 01:42:58 by namine            #+#    #+#             */
/*   Updated: 2022/11/12 17:05:15 by namine           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

int	ft_strcmp(const char	*s1, const char *s2)
{
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;
	size_t			i;

	s1_tmp = (unsigned char *)s1;
	if (!s1_tmp || !*s1_tmp)
		return (-1);
	s2_tmp = (unsigned char *)s2;
	i = 0;
	while (s1_tmp[i] && s2_tmp[i] && s1_tmp[i] == s2_tmp[i])
		i++;
	return (s1_tmp[i] - s2_tmp[i]);
}

int	check_argument_name(char *str)
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

void	error_msg(t_list *list_command, char *cmd, char *msg, char *arg)
{
	if (list_command && ft_lstsize((t_linked_list *)list_command) == 1
		&& !ft_strcmp(cmd, "exit"))
		write(2, "exit\n", 6);
	write(2, "Petit_shell: ", 14);
	if (cmd)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": ", 3);
	}
	if (arg)
	{
		write(2, arg, ft_strlen(arg));
		write(2, ": ", 3);
	}
	if (msg)
	{
		write(2, msg, ft_strlen(msg));
		write(2, "\n", 2);
	}
}

char *search_env_var(t_param *param, char *str)
{
    t_ev *tmp;
    
    tmp = param->env;
    while (tmp)
    {
        if (!ft_strcmp(str, tmp->env_var))
            return(ft_strdup(tmp->value));
        tmp = tmp->next;
    }
    return (NULL);
}
