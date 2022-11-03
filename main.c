/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:57 by hasabir           #+#    #+#             */
/*   Updated: 2022/11/03 17:59:58 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*input;
	t_list	*list_command;

	(void)ac;
	(void)av;
	while(1)
	{
		input = readline("➜ \033[93m\033[01m\033[05mPetit_shell$ \033[00m");
		if (input == NULL) // CTRL+D -> EOF
			exit(1);
		if (*input)
			add_history(input);
		input = lexical_analysis(input);
		if (input && *input)
		{
			list_command = creat_list_of_command_2();
			// parsing(input, &list_command, env);
			if (parsing(input, &list_command, env))
				print_list_command(list_command);
		}
		if (input && *input)
			free_list(list_command);
		free(input);
		// system("leaks minishell");
	}

	return 0;
}
