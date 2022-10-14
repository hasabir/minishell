/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:35:06 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/14 18:02:59 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	take_out_files(t_list *list_command, char *matrix_command_line)
// {
// 	int	i;

// 	if (!search(matrix_command_line, '>'))
// 		return ;
// 	i = -1;
// 	while (matrix_command_line[++i])
// 	{
// 		if (matrix_command_line[i] == '>')
// 		{
// 			if (matrix_command_line[i + 1] == '>')
// 			{
// 				matrix_command_line[i] = DOUBLE_GREAT;
// 				matrix_command_line[i] = DOUBLE_GREAT;
// 			}
// 		}
// 	}
// }

char	*expand(char *arg, char **env)
{
	int		i;
	char	**stock;
	char	*tmp;
	char	*env_value;
	
	i = -1;
	stock = ft_split(arg, '$');
	while (stock[++i])
	{
		tmp = stock[i];
		env_value = search_env(env, stock[i], &tmp);
		if (env_value)
		{
			free(stock[i]);
			if (!ft_isalnum(tmp[0]))
				stock[i] = ft_strjoin(env_value, tmp);
			else
				stock[i] = ft_strdup(tmp);
		}
	}
	free(arg);
	arg = NULL;
	i = -1;
	while (stock[++i])
	{
		free(arg);
		arg = ft_strjoin(arg, stock[i]);
	}
	ft_free(stock);
	return (arg);
}


char	*ft_double_quote(char *cmd, char **env)
{
	int		i;
	char	**stock;

	stock = ft_split(cmd, '"');	
	free(cmd);
	cmd = NULL;
	i = -1;
	while (stock[++i])
	{
		if (search(stock[i], '$') != 0)
			stock[i] = expand(stock[i], env);
		cmd = ft_strjoin(cmd, stock[i]);
	}
	i = -1;
	while (stock[++i])
		free (stock[i]);
	free(stock);
	return (cmd);
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