/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/02/15 10:22:44 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		ms.input = readline("\033[1;36mminishell \033[1;34m$> \033[0m");
		add_history(ms.input);
		if (ms.input == 0)
			return (printf("exit\n"), free(ms.input), rl_clear_history(), 0);
		read_prompt(&ms, envp);
		execution(&ms, ms.input, envp);
	}
	return (0);
}	
