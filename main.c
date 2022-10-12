/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:57 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/10 19:03:23 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char *input;
	t_list	*list_command;

	(void)ac;
	(void)av;
	while(1)
	{
		input = readline("➜ \033[93m\033[01m\033[05mPetit_shell$ \033[00m");
		add_history(input);
		list_command = NULL;
		input = lexical_analysis(input);
		if (input && *input)
			list_command = parsing(input, list_command, env);
		// system("leaks minishell");
	}
	return 0;
}