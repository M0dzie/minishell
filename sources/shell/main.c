/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/13 16:25:27 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_msl	ms;

	(void) argv;
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
		read_prompt(input, envp, &ms);
	}
	return (0);
}	
