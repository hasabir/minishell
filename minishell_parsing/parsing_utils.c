/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 17:51:50 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/08 15:02:51 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*set_options(char *option)
{
	int i;

	i = 0;
	// set_oprigin("")
	return (option);
}

char	*ft_single_quote(char *cmd)
{
	int		i;
	char	**stock;
	
	stock = ft_split(cmd, '\'');
	free(cmd);
	cmd = NULL;
	i = -1;
	while (stock[++i])
		cmd = ft_strjoin(cmd, stock[i]);
	i = -1;
	while (stock[++i])
		free (stock[i]);
	free(stock);
	return (cmd);
}

char	*ft_double_quote(char *cmd)
{
	int		i;
	char	**stock;
	
	stock = ft_split(cmd, '"');	
	free(cmd);
	cmd = NULL;
	i = -1;
	while (stock[++i])
		cmd = ft_strjoin(cmd, stock[i]);
	i = -1;
	while (stock[++i])
		free (stock[i]);
	free(stock);
	return (cmd);
} signe          

char	*set_command(char *cmd)
{
	cmd = ft_single_quote(cmd);
	cmd = ft_double_quote(cmd);
	set_origin(&cmd);
	return (cmd);
}