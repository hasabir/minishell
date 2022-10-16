/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:35:06 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/16 18:37:02 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"





// char	*expand(char *arg, char **env)
// {
// 	int		i;
// 	char	**stock;
// 	char	*tmp;
// 	char	*env_value;
	
// 	i = -1;
// 	printf("arg = %s\n", arg);
// 	stock = ft_split(arg, '$');
// 	while (stock[++i])
// 	{
// 		tmp = stock[i];
// 		env_value = search_env(env, stock[i], &tmp);
// 		if (env_value && !ft_isalnum(tmp[0]))
// 			{ printf("tmp = %s\n", tmp);
// 			stock[i] = ft_strjoin(env_value, tmp);}
// 		else
// 		{
// 			printf("I AM HEAR\n");
// 			if (!ft_isalnum(tmp[0]))
// 				stock[i] = ft_strdup(tmp);}
// 	}
// 	// free(arg);
// 	// arg = NULL;
// 	i = -1;
// 	while (stock[++i])
// 	{
// 		if (i == 0)
// 			arg = stock[i];
// 		else
// 		arg = ft_strjoin(arg, stock[i]);
// 		// free(arg);
// 	}
// 	// ft_free(stock);
// 	return (arg);
// }


int	check_space(char *arg)
{
	int	i;

	i = 0;
	while(arg[i] != '$')
		i++;
	i++;
	if (!arg[i])
		return (1);
	return (0);
}


//handle in lexi

char	*expand(char *arg, char **env)
{
	int		i;
	int		j;
	char	**stock;
	char	*tmp;
	char	*env_value;
	
	i = -1;
	if (check_space(arg))
		return (arg);
	
	stock = ft_split(arg, '$');
	while (stock[++i])
		printf("\nstock[i] = '%s'\n", stock[i]);
	
	i = -1;
	while (stock[++i])
	{
		tmp = stock[i];
		env_value = search_env(env, stock[i], &tmp);
		// free(stock[i]);
		if (env_value && !ft_isalnum(*tmp))
		{
			// if (!ft_isalnum(*tmp))
				stock[i] = ft_strjoin(env_value, tmp);
		}
		else
		{
			printf("******%d*****\n", i);
			j = 0;
			while (*tmp && ft_isalnum(*tmp))
				tmp++;
			stock[i] = ft_strdup(tmp);
		}
	}
	// free(arg);
	// arg = NULL;
	i = -1;
	while (stock[++i])
	{
		// free(arg);
		if (i == 0)
			arg = stock[i];
		else
			arg = ft_strjoin(arg, stock[i]);
			// ft_strlcat(arg, stock[i], ft_strlen(stock[i]));
	}
	// ft_free(stock);
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

	if (!cmd || !*cmd)
		return (cmd);
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