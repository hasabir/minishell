/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:51:50 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/07 17:51:54 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_single_quote(char *cmd)
{
	int		i;
	char	**stock;
	
	stock = ft_split(cmd, '\'');
	cmd = NULL;
	i = -1;
	while (stock[++i])
		cmd = ft_strjoin(cmd, stock[i]);
	i = -1;
	while (stock[++i])
		free (stock[i]);
	return (cmd);
}

char	*ft_double_quote(char *cmd)
{
	int		i;
	char	**stock;
	
	stock = ft_split(cmd, '"');	
	cmd = NULL;
	i = -1;
	while(stock[++i])printf("stock[%d] = %s\n", i, stock[i]);
	i = -1;
	while (stock[++i])
		cmd = ft_strjoin(cmd, stock[i]);
	i = -1;
	while (stock[++i])
		free (stock[i]);
	return (cmd);
}

char	*set_command(char *cmd)
{
	if (which_type_quote(cmd) == 0)
		return (cmd);
	else if (which_type_quote(cmd) == 1)
		return (ft_single_quote(cmd));
	else if (which_type_quote(cmd) == 2)
		return (ft_double_quote(cmd));
	return (NULL);
}