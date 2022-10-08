/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hasabir <hasabir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 14:25:57 by hasabir           #+#    #+#             */
/*   Updated: 2022/10/08 11:25:04 by hasabir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char *input;
	t_list	*list_command;

	(void)ac;
	(void)av;
	(void)env;
	while(1)
	{
		input = readline("➜ \033[93m\033[01m\033[05mPetit_shell$ \033[00m");
		add_history(input);
		list_command = NULL;
		input = lexical_analysis(input);
		if (input && *input)
			list_command = parsing(input, list_command);
		// system("leaks minishell");
	}
	return 0;
}