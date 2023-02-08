/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer <thmeyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/08 09:52:43 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_prompt(char *input, char **env)
{
	if (ms_strcmp(input, "pwd"))
		print_pwd();
	else if (ms_strcmp(input, "env"))
		print_env(env);
	else if (ms_strcmp(input, "echo"))
		printf("%s\n", input + 5);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void) argv;
	(void) env;
	if (argc != 1)
		return (ft_putendl_fd("Error\nminishell doesn't take any parameters.", \
		2), 0);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[1;36mminishell \033[1;34m$> \033[0m");
		add_history(input);
		parsing_input(input);
		read_prompt(input, env);
	}
	return (0);
}	

	// pid = fork();
	// if (pid < 0)
	// 	return (ft_putendl_fd("Error\nNo child process was created.", 2), 0);