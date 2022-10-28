/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:57 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/28 13:06:56 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		add_history(input);
		input = lexical_analysis(input);
		if (input && *input)
		{
			list_command = creat_list_of_command_2();
			parsing(input, &list_command, env);
		}
		print_list_command(list_command);
		free(input);
		// system("leaks minishell");
	}

	return 0;
}