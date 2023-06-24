/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:57 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/15 03:43:11 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution/execution.h"

void	free_list(t_list *list_command)
{
	t_list	*tmp;

	while (list_command)
	{
		tmp = list_command;
		if (list_command->data->cmd)
			free(list_command->data->cmd);
		if (list_command->data->arguments)
			ft_free(list_command->data->arguments);
		if (list_command->data->options)
			ft_free(list_command->data->options);
		free (list_command->data);
		list_command = list_command->next;
		free(tmp);
	}
	free(list_command);
	list_command = NULL;
}

void	initialize_main(char **env, t_param **param, int ac, char **av)
{
	(void)ac;
	(void)av;
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
	g_global.exit_status = 0;
	*param = malloc(sizeof(t_param));
	if (!*param)
		malloc_failed();
	initialize_env(*param, env, -1);
	initialize_export(*param, env, -1);
}

void	initialize_input(char **input)
{
	if (*input == NULL)
	{
		write(1, "exit\n", 6);
		exit (g_global.exit_status);
	}
	if (*input && **input)
	{
		add_history(*input);
		*input = lexical_analysis(*input);
	}
	if (*input)
		g_global.pipe = 0;
}

int	main(int ac, char **av, char **env)
{
	t_list	*list_command;
	char	**ptr_env;
	t_param	*param;
	char	*input;

	initialize_main(env, &param, ac, av);
	while (1)
	{
		g_global.is_heredoc = 0;
		input = readline("Petit_shell$ ");
		initialize_input(&input);
		if (input)
		{
			ptr_env = convert_to_arr(param);
			list_command = creat_list_of_command();
			if (parsing(input, &list_command, ptr_env) && input[0])
				execution(list_command, param);
			ft_free(ptr_env);
		}
		if (input)
			free_list(list_command);
		free(input);
		input = NULL;
	}
	return (0);
}
