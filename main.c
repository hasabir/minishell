/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:57 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/09 13:23:03 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/execution.h"

void	initialize_env(t_param *param, char **env)
{
	char	**ptr;
	t_ev	*tmp;
	int		i;
	
	param->env = malloc(sizeof(t_ev));
	if (!param->env)
		return ;
	tmp = param->env;
	i = 0;
	while (env[i])
	{
		ptr = ft_split(env[i], '=');
		tmp->env_var = ft_strdup(ptr[0]);
		tmp->value = ft_strdup(ptr[1]);
		ft_free(ptr);
		tmp->next = malloc(sizeof(t_ev));
		if (env[i + 1])
			tmp = tmp->next;
		else
			free(tmp->next);
		i++;
	}
	tmp->next = NULL;
}

void	initialize_export(t_param *param, char **env)
{
	char	**ptr;
	t_ev	*tmp;
	int		i;

	param->export = malloc(sizeof(t_ev));
	if (!param->export)
		return ;
	tmp = param->export;
	i = 0;
	while (env[i])
	{
		ptr = ft_split(env[i], '=');
		tmp->env_var = ft_strdup(ptr[0]);
		tmp->value = ft_strdup(ptr[1]);
		ft_free(ptr);
		tmp->next = malloc(sizeof(t_ev));
		if (env[i + 1])
			tmp = tmp->next;
		else
			free(tmp->next);
		i++;
	}
	tmp->next = NULL;
}

char	**convert_to_arr(t_param *param)
{
	char	**env_arr;
	t_ev	*tmp;
	char	*s1;
	char	*s2;
	int		i;
	
	if (!param)
		return (NULL);
	tmp = param->env;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_arr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	tmp = param->env;
	while (tmp)
	{
		s1 = ft_strjoin(tmp->env_var, "=");
		s2 = ft_strjoin(s1, tmp->value);
		free(s1);
		env_arr[i] = ft_strdup(s2);
		free(s2);
		tmp = tmp->next;
		i++;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

void	free_list(t_list *list_command)
{
	while (list_command)
	{
		if (list_command->data->cmd)
			free(list_command->data->cmd);
		if (list_command->data->arguments)
			ft_free(list_command->data->arguments);
		if (list_command->data->options)
			ft_free(list_command->data->options);
		free (list_command->data);
		free(list_command);
		list_command = list_command->next;
	}
	free(list_command);
	list_command = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_list	*list_command;
	char	**ptr_env;
	t_param	*param;
	char	*input;

	(void)ac;
	(void)av;
	param = malloc(sizeof(t_param));
	initialize_env(param, env);
	initialize_export(param, env);
	while(1)
	{
		input = readline("Petit_shell$ ");
		if (input == NULL) // CTRL+D -> EOF
			exit(1);
		if (input && *input)
			add_history(input);
		input = lexical_analysis(input);
		if (input && *input)
		{
			ptr_env = convert_to_arr(param);
			list_command = creat_list_of_command_2();
			parsing(input, &list_command, ptr_env);
			// if (parsing(input, &list_command, ptr_env))
			// 	print_list_command(list_command);
			execution(list_command, ptr_env, param);
			ft_free(ptr_env);
		}
		if (input && *input)
			free_list(list_command);
		free(input);
		input = NULL;
		// system("leaks minishell");
	}
	return (0);
}
