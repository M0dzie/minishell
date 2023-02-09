/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdisapin <mehdisapin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/08 21:09:29 by mehdisapin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void) argv;
	(void) env;
	if (argc != 1)
		return (ft_putendl_fd("Error\nMinishell doesn't take any parameters.", \
		2), 0);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		input = readline("\033[1;36mminishell \033[1;34m$> \033[0m");
		add_history(input);
		if (input == 0)
			return (printf("exit\n"), free(input), rl_clear_history(), 0);
		parsing_input(input);
		read_prompt(input, env);
	}
	return (0);
}	
