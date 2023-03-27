/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thmeyer < thmeyer@student.42lyon.fr >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:38:17 by thmeyer           #+#    #+#             */
/*   Updated: 2023/03/27 10:10:37 by thmeyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	g_signal;

void	free_global(t_msl *ms)
{
	if (ms->input)
		free(ms->input);
	if (ms->tokens)
		ft_arrfree(ms->tokens);
	free(ms);
}

int	main(int argc, char **argv, char **envp)
{
	t_msl		ms;

	(void) argv;
	if (argc != 1)
		return (ft_putendl_fd("Error\nMinishell doesn't take any parameters.", \
		2), 0);
	init_env(&ms, envp);
	ms.status = 0;
	g_signal = 0;
	while (1)
	{
		input_signal();
		ms.input = readline("\033[1;36mminishell \033[1;34m$> \033[0m");
		add_history(ms.input);
		if (ms.input == 0)
			return (printf("exit\n"), free(ms.input), rl_clear_history(), 0);
		read_prompt(&ms, envp);
	}
	return (0);
}	
