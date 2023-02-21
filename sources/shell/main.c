/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/21 11:37:08 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler(int signal)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

int	main(int argc, char **argv, char **envp)
{
	t_msl	ms;

	(void) argv;
	if (argc != 1)
		return (ft_putendl_fd("Error\nMinishell doesn't take any parameters.", \
		2), 0);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		ms.input = readline("\033[1;36mminishell \033[1;34m$> \033[0m");
		add_history(ms.input);
		if (ms.input == 0)
			return (printf("exit\n"), free(ms.input), rl_clear_history(), 0);
		read_prompt(&ms, envp);
	}
	return (0);
}	
