/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:57 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/05 22:55:00 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/execution.h"

void	initialize_env(t_param **param, char **env)
{
	char	**ptr;
	t_ev	*tmp;
	int		i;

	(*param)->env = malloc(sizeof(t_ev));
	tmp = (*param)->env;
	i = 0;
	while (env[i])
	{
		ptr = ft_split(env[i], '=');
		tmp->env_var = ft_strdup(ptr[0]);
		tmp->value = ft_strdup(ptr[1]);
		// ft_free(ptr);
		tmp->next = malloc(sizeof(t_ev));
		if (env[i + 1])
			tmp = tmp->next;
		i++;
	}
	tmp->next = NULL;
}

char	**convert_to_arr(t_ev *node)
{
	char	**env_arr;
	t_ev	*tmp;
	char	*s1;
	char	*s2;
	int i;
	
	tmp = node;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	env_arr = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (node)
	{
		s1 = ft_strjoin(node->env_var, "=");
		s2 = ft_strjoin(s1, node->value);
		env_arr[i] = ft_strdup(s2);
		node = node->next;
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
	initialize_env(&param, env);
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
			list_command = creat_list_of_command_2();
			ptr_env = convert_to_arr(param->env); // CHECK POSITION IN THE WHILE
			parsing(input, &list_command, env);
			// if (parsing(input, &list_command, env_ptr))
				// print_list_command(list_command);
			execution(list_command, ptr_env, param);
		}
		if (input && *input)
			free_list(list_command);
		if (input)
			free(input);
		// system("leaks minishell");
	}
	return (0);
}
